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


def emit_header(out, msg):
    out.write(f"// Message: {msg['name']} (type 0x{msg['type']:02X})\n")
    out.write(f"struct {msg['name']} {{\n")
    for f in msg['fields']:
        out.write(
            f"    {f['type']} {camel_to_snake(f['name'])}; // {f['size']} bytes\n")
    out.write("};\n\n")


def emit_serializer(out, msg):
    name = msg['name']
    func = f"serialize_{camel_to_snake(name)}"
    out.write(f"std::vector<uint8_t> {func}(const {name}& m) {{\n")
    out.write("    std::vector<uint8_t> buf; buf.reserve(/* calc length */);\n")
    out.write("    // Frame header\n")
    out.write("    buf.push_back(0xBA); buf.push_back(0xBA); // sync\n")
    out.write(f"    buf.push_back(0x{msg['type']:02X}); // message type\n")
    for f in msg['fields']:
        sn = camel_to_snake(f['name'])
        if f['type'].startswith('uint'):
            out.write(f"    append_uint(buf, m.{sn}, {f['size']});\n")
        else:
            out.write(f"    append_bytes(buf, m.{sn});\n")
    out.write("    // TODO: checksum/trailer\n")
    out.write("    return buf;\n")
    out.write("}\n\n")


def emit_deserializer(out, msg):
    name = msg['name']
    func = f"parse_{camel_to_snake(name)}"
    out.write(f"{name} {func}(const uint8_t* data, size_t len) {{\n")
    out.write(f"    {name} m; size_t pos = 0;\n")
    out.write("    // skip sync & type header\n")
    out.write("    pos += 3;\n")
    for f in msg['fields']:
        sn = camel_to_snake(f['name'])
        if f['type'].startswith('uint'):
            out.write(
                f"    m.{sn} = read_uint(data + pos, {f['size']}); pos += {f['size']};\n")
        else:
            out.write(
                f"    read_bytes(data + pos, m.{sn}, {f['size']}); pos += {f['size']};\n")
    out.write("    return m;\n")
    out.write("}\n\n")


def main():
    if len(sys.argv) != 3:
        print("Usage: codegen.py spec.yaml out_dir/")
        sys.exit(1)

    spec_file, out_dir = sys.argv[1], sys.argv[2]
    with open(spec_file) as f:
        spec = yaml.safe_load(f)

    os.makedirs(out_dir, exist_ok=True)
    hdr_path = os.path.join(out_dir, 'Messages.h')
    src_path = os.path.join(out_dir, 'Serializer.cpp')

    with open(hdr_path, 'w') as h, open(src_path, 'w') as c:
        # Headers
        h.write('#pragma once\n#include <cstdint>\n#include <array>\n\n')
        c.write('#include "Messages.h"\n#include <vector>\n#include "Util.h"\n\n')

        for msg in spec['messages']:
            emit_header(h, msg)
            emit_serializer(c, msg)
            emit_deserializer(c, msg)

    print(f"Generated: {hdr_path}, {src_path}")


if __name__ == '__main__':
    main()
