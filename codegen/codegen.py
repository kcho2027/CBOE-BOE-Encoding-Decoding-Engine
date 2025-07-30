#!/usr/bin/env python3
"""
codegen.py: Generate C++ BOE modules from a YAML spec.
Usage: python3 codegen.py cboe_spec.yaml output_dir/
"""
import sys
import os
import yaml


def camel_to_snake(name):
    import re
    s1 = re.sub('(.)([A-Z][a-z]+)', r'\1_\2', name)
    return re.sub('([a-z0-9])([A-Z])', r'\1_\2', s1).lower()


def emit_message_struct(out, msg):
    # Emit C++ struct for each message
    out.write(f"// Generated struct for {msg['name']}\n")
    out.write(f"struct {msg['name']} {{\n")
    for f in msg['fields']:
        out.write(
            f"    {f['type']} {camel_to_snake(f['name'])}; // {f['size']} bytes\n")
    out.write("};\n\n")


def emit_serializer_decl(out, msg):
    name = msg["name"]
    out.write(f"std::vector<uint8_t> serialize{name}(const {name}& m);\n")


def emit_deserializer_decl(out, msg):
    name = msg["name"]
    snake = camel_to_snake(name)
    out.write(f"{name} parse_{snake}(const uint8_t* data, size_t len);\n")


def emit_serializer_def(out, msg):
    name = msg['name']
    snake = camel_to_snake(name)
    out.write(
        f"#include \"cboe/Serializer.h\"\n#include <vector>\n#include \"util.h\"\n\n")
    out.write(
        f"std::vector<uint8_t> cboe::serialize{name}(const cboe::{name}& m) {{\n")
    out.write("    std::vector<uint8_t> buf;\n")
    out.write("    // framing, fields...\n")
    for fld in msg['fields']:
        field_snake = camel_to_snake(fld['name'])
        if fld['type'].startswith('uint'):
            out.write(
                f"    append_uint(buf, m.{field_snake}, {fld['size']});\n")
        else:
            out.write(
                f"    append_bytes(buf, m.{field_snake}, {fld['size']});\n")
    out.write("    return buf;\n}\n\n")


def emit_deserializer_def(out, msg):
    name = msg['name']
    snake = camel_to_snake(name)
    out.write(
        f"#include \"cboe/Deserializer.h\"\n#include \"util.h\"\n#include <vector>\n\n")
    out.write(
        f"cboe::{name} cboe::parse_{snake}(const uint8_t* data, size_t len) {{\n")
    out.write(f"    {name} m; size_t pos = 0;\n")
    out.write("    // skip framing header\n    pos += 3;\n")
    for f in msg['fields']:
        sn = camel_to_snake(f['name'])
        if f['type'].startswith('uint'):
            out.write(
                f"    m.{sn} = read_uint(data + pos, {f['size']}); pos += {f['size']};\n")
        else:
            out.write(
                f"    read_bytes(data + pos, m.{sn}, {f['size']}); pos += {f['size']};\n")
    out.write("    return m;\n}\n\n")


def main():
    if len(sys.argv) != 3:
        print("Usage: codegen.py spec.yaml /path/to/engine/")
        sys.exit(1)

    spec_file, engine_root = sys.argv[1], sys.argv[2]
    with open(spec_file) as f:
        spec = yaml.safe_load(f)

    # Setup directories
    inc_dir = os.path.join(engine_root, "include", "cboe")
    src_dir = os.path.join(engine_root, "src")
    os.makedirs(inc_dir, exist_ok=True)
    os.makedirs(src_dir, exist_ok=True)

    # Open output files
    with open(os.path.join(inc_dir, "Messages.h"), "w") as fh_msg, \
            open(os.path.join(inc_dir, "Serializer.h"), "w") as fh_ser_h, \
            open(os.path.join(inc_dir, "Deserializer.h"), "w") as fh_deser_h, \
            open(os.path.join(inc_dir, "util.h"), "w") as fh_util, \
            open(os.path.join(inc_dir, "FramingEngine.h"), "w") as fh_frame_h, \
            open(os.path.join(src_dir, "Serializer.cpp"), "w") as fs_ser, \
            open(os.path.join(src_dir, "Deserializer.cpp"), "w") as fs_deser, \
            open(os.path.join(src_dir, "FramingEngine.cpp"), "w") as fs_frame:

        # Util header
        fh_util.write("""#pragma once
#include <cstdint>
#include <vector>
#include <cstring>

inline void append_uint(std::vector<uint8_t>& buf, uint64_t v, size_t s) { for(size_t i=0;i<s;++i){ buf.push_back(v & 0xFF); v >>= 8; } }
inline void append_bytes(std::vector<uint8_t>& buf, const void* d, size_t s){ buf.insert(buf.end(), (uint8_t*)d, (uint8_t*)d+s); }
inline uint64_t read_uint(const uint8_t* d, size_t s){ uint64_t v=0; for(size_t i=0;i<s;++i) v |= (uint64_t(d[i]) << (8*i)); return v; }
inline void read_bytes(const uint8_t* d, void* dst, size_t s){ memcpy(dst,d,s); }
""")

        # FramingEngine stubs
        fh_frame_h.write("""#pragma once
#include <vector>
#include <cstdint>
namespace cboe {
struct FramingEngine {
    static std::vector<uint8_t> wrapMessage(const std::vector<uint8_t>& body);
    static bool unwrapMessage(const uint8_t* data, size_t len, std::vector<uint8_t>& out);
};
} // namespace cboe
""")
        fs_frame.write("""#include "cboe/FramingEngine.h"
// TODO: implement wrapMessage (sync bytes, length, checksum) and unwrapMessage
""")

        # Headers
        fh_msg.write("""#pragma once
#include <cstdint>
#include <array>

namespace cboe {

""")
        fh_ser_h.write("""#pragma once
#include <vector>
#include "cboe/Messages.h"
#include "util.h"

namespace cboe {

""")
        fh_deser_h.write("""#pragma once
#include "cboe/Messages.h"
#include "util.h"

namespace cboe {

""")

        for msg in spec.get("messages", []):
            emit_message_struct(fh_msg, msg)
            emit_serializer_decl(fh_ser_h, msg)
            emit_deserializer_decl(fh_deser_h, msg)
            emit_serializer_def(fs_ser, msg)
            emit_deserializer_def(fs_deser, msg)

        fh_msg.write("} // namespace cboe\n")
        fh_ser_h.write("} // namespace cboe\n")
        fh_deser_h.write("} // namespace cboe\n")


if __name__ == '__main__':
    main()
