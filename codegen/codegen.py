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


def get_cpp_type(field_type, length):
    """Convert YAML field type to C++ type"""
    type_mapping = {
        'binary': f'uint8_t[{length}]',
        'alphanumeric': f'char[{length}]',
        'text': f'char[{length}]',
        'datetime': 'uint64_t',  # 8-byte timestamp
        'uint8': 'uint8_t',
        'uint16': 'uint16_t',
        'uint32': 'uint32_t',
        'uint64': 'uint64_t'
    }

    if field_type in type_mapping:
        return type_mapping[field_type]
    elif field_type.startswith('uint'):
        return field_type
    else:
        return f'char[{length}]'  # Default to char array


def emit_message_struct(out, msg):
    """Emit C++ struct for each message"""
    out.write(f"// Generated struct for {msg['name']}\n")
    out.write(f"struct {msg['name']} {{\n")

    # Track used field names to avoid duplicates
    used_field_names = set()

    # Emit all fields
    for field in msg.get('fields', []):
        field_name = field['name']
        field_type = field['type']
        field_length = field['length']
        field_desc = field.get('description', '')

        cpp_type = get_cpp_type(field_type, field_length)
        snake_name = camel_to_snake(field_name)

        # Ensure unique field names
        original_name = snake_name
        counter = 1
        while snake_name in used_field_names:
            snake_name = f"{original_name}_{counter}"
            counter += 1
        used_field_names.add(snake_name)

        # Fix array syntax - move brackets after the name
        if '[' in cpp_type:
            base_type = cpp_type.split('[')[0]
            array_size = cpp_type.split('[')[1].split(']')[0]
            out.write(
                f"    {base_type} {snake_name}[{array_size}]; // {field_desc}\n")
        else:
            out.write(f"    {cpp_type} {snake_name}; // {field_desc}\n")

    # Emit repeating groups if present
    if 'repeatingGroup' in msg:
        out.write(f"    // Repeating group fields\n")
        for field in msg['repeatingGroup']:
            field_name = field['name']
            field_type = field['type']
            field_length = field['length']
            field_desc = field.get('description', '')

            cpp_type = get_cpp_type(field_type, field_length)
            snake_name = camel_to_snake(field_name)

            # Ensure unique field names for repeating groups
            original_name = snake_name
            counter = 1
            while snake_name in used_field_names:
                snake_name = f"{original_name}_{counter}"
                counter += 1
            used_field_names.add(snake_name)

            # Fix array syntax - move brackets after the name
            if '[' in cpp_type:
                base_type = cpp_type.split('[')[0]
                array_size = cpp_type.split('[')[1].split(']')[0]
                out.write(
                    f"    {base_type} {snake_name}[{array_size}]; // {field_desc}\n")
            else:
                out.write(f"    {cpp_type} {snake_name}; // {field_desc}\n")

    out.write("};\n\n")


def emit_serializer_decl(out, msg):
    """Emit serializer declaration"""
    name = msg["name"]
    out.write(f"std::vector<uint8_t> serialize{name}(const {name}& m);\n")


def emit_deserializer_decl(out, msg):
    """Emit deserializer declaration"""
    name = msg["name"]
    snake = camel_to_snake(name)
    out.write(f"{name} parse_{snake}(const uint8_t* data, size_t len);\n")


def emit_serializer_def(out, msg):
    """Emit serializer implementation"""
    name = msg['name']
    snake = camel_to_snake(name)

    out.write(
        f"#include \"cboe/Serializer.h\"\n#include <vector>\n#include \"util.h\"\n\n")
    out.write(
        f"std::vector<uint8_t> cboe::serialize{name}(const cboe::{name}& m) {{\n")
    out.write("    std::vector<uint8_t> buf;\n")
    out.write("    // Add framing header\n")
    out.write("    uint8_t start_bytes[] = {0xBA, 0xBA};\n")
    out.write("    buf.insert(buf.end(), start_bytes, start_bytes + 2);\n")
    out.write("    // Message length will be calculated later\n")
    out.write("    buf.resize(buf.size() + 2);\n")
    out.write(f"    buf.push_back(0x{msg['type']:02X}); // MessageType\n")
    out.write("    buf.push_back(0); // MatchingUnit\n")
    out.write("    // SequenceNumber placeholder\n")
    out.write("    for (int i = 0; i < 4; ++i) buf.push_back(0);\n\n")

    # Emit field serialization
    for field in msg.get('fields', []):
        field_name = field['name']
        field_type = field['type']
        field_length = field['length']
        snake_name = camel_to_snake(field_name)

        if field_name in ['StartOfMessage', 'MessageLength', 'MessageType', 'MatchingUnit', 'SequenceNumber']:
            continue  # Skip header fields as they're handled above

        if field_type == 'binary':
            out.write(
                f"    append_bytes(buf, m.{snake_name}, {field_length});\n")
        elif field_type in ['alphanumeric', 'text']:
            out.write(
                f"    append_bytes(buf, m.{snake_name}, {field_length});\n")
        elif field_type == 'datetime':
            out.write(f"    append_uint(buf, m.{snake_name}, 8);\n")
        else:
            out.write(
                f"    append_bytes(buf, m.{snake_name}, {field_length});\n")

    # Handle repeating groups
    if 'repeatingGroup' in msg:
        out.write("    // Serialize repeating group fields\n")
        for field in msg['repeatingGroup']:
            field_name = field['name']
            field_type = field['type']
            field_length = field['length']
            snake_name = camel_to_snake(field_name)

            if field_type == 'binary':
                out.write(
                    f"    append_bytes(buf, m.{snake_name}, {field_length});\n")
            elif field_type in ['alphanumeric', 'text']:
                out.write(
                    f"    append_bytes(buf, m.{snake_name}, {field_length});\n")
            elif field_type == 'datetime':
                out.write(f"    append_uint(buf, m.{snake_name}, 8);\n")
            else:
                out.write(
                    f"    append_bytes(buf, m.{snake_name}, {field_length});\n")

    out.write("    // Update message length\n")
    out.write("    uint16_t msg_len = buf.size() - 2; // Exclude StartOfMessage\n")
    out.write("    buf[2] = (msg_len >> 8) & 0xFF;\n")
    out.write("    buf[3] = msg_len & 0xFF;\n")
    out.write("    return buf;\n}\n\n")


def emit_deserializer_def(out, msg):
    """Emit deserializer implementation"""
    name = msg['name']
    snake = camel_to_snake(name)

    out.write(
        f"#include \"cboe/Deserializer.h\"\n#include \"util.h\"\n#include <vector>\n\n")
    out.write(
        f"cboe::{name} cboe::parse_{snake}(const uint8_t* data, size_t len) {{\n")
    out.write(f"    {name} m;\n")
    out.write("    size_t pos = 0;\n")
    out.write("    // Skip framing header\n")
    out.write("    pos += 2; // StartOfMessage\n")
    out.write("    pos += 2; // MessageLength\n")
    out.write("    pos += 1; // MessageType\n")
    out.write("    pos += 1; // MatchingUnit\n")
    out.write("    pos += 4; // SequenceNumber\n\n")

    # Emit field deserialization
    for field in msg.get('fields', []):
        field_name = field['name']
        field_type = field['type']
        field_length = field['length']
        snake_name = camel_to_snake(field_name)

        if field_name in ['StartOfMessage', 'MessageLength', 'MessageType', 'MatchingUnit', 'SequenceNumber']:
            continue  # Skip header fields as they're handled above

        if field_type == 'binary':
            out.write(
                f"    read_bytes(data + pos, m.{snake_name}, {field_length}); pos += {field_length};\n")
        elif field_type in ['alphanumeric', 'text']:
            out.write(
                f"    read_bytes(data + pos, m.{snake_name}, {field_length}); pos += {field_length};\n")
        elif field_type == 'datetime':
            out.write(
                f"    m.{snake_name} = read_uint(data + pos, 8); pos += 8;\n")
        else:
            out.write(
                f"    read_bytes(data + pos, m.{snake_name}, {field_length}); pos += {field_length};\n")

    # Handle repeating groups
    if 'repeatingGroup' in msg:
        out.write("    // Deserialize repeating group fields\n")
        for field in msg['repeatingGroup']:
            field_name = field['name']
            field_type = field['type']
            field_length = field['length']
            snake_name = camel_to_snake(field_name)

            if field_type == 'binary':
                out.write(
                    f"    read_bytes(data + pos, m.{snake_name}, {field_length}); pos += {field_length};\n")
            elif field_type in ['alphanumeric', 'text']:
                out.write(
                    f"    read_bytes(data + pos, m.{snake_name}, {field_length}); pos += {field_length};\n")
            elif field_type == 'datetime':
                out.write(
                    f"    m.{snake_name} = read_uint(data + pos, 8); pos += 8;\n")
            else:
                out.write(
                    f"    read_bytes(data + pos, m.{snake_name}, {field_length}); pos += {field_length};\n")

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
#include <algorithm>

inline void append_uint(std::vector<uint8_t>& buf, uint64_t v, size_t s) { 
    for(size_t i=0;i<s;++i){ 
        buf.push_back(v & 0xFF); 
        v >>= 8; 
    } 
}
inline void append_bytes(std::vector<uint8_t>& buf, const void* d, size_t s){ 
    buf.insert(buf.end(), (uint8_t*)d, (uint8_t*)d+s); 
}
inline uint64_t read_uint(const uint8_t* d, size_t s){ 
    uint64_t v=0; 
    for(size_t i=0;i<s;++i) v |= (uint64_t(d[i]) << (8*i)); 
    return v; 
}
inline void read_bytes(const uint8_t* d, void* dst, size_t s){ 
    memcpy(dst,d,s); 
}
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
#include <vector>
#include <cstdint>

namespace cboe {

std::vector<uint8_t> FramingEngine::wrapMessage(const std::vector<uint8_t>& body) {
    std::vector<uint8_t> framed;
    // Add sync bytes
    framed.push_back(0xBA);
    framed.push_back(0xBA);
    
    // Add length (excluding sync bytes)
    uint16_t length = body.size();
    framed.push_back((length >> 8) & 0xFF);
    framed.push_back(length & 0xFF);
    
    // Add body
    framed.insert(framed.end(), body.begin(), body.end());
    
    return framed;
}

bool FramingEngine::unwrapMessage(const uint8_t* data, size_t len, std::vector<uint8_t>& out) {
    if (len < 4) return false;
    
    // Check sync bytes
    if (data[0] != 0xBA || data[1] != 0xBA) return false;
    
    // Extract length
    uint16_t msg_len = (data[2] << 8) | data[3];
    
    if (len < 4 + msg_len) return false;
    
    // Copy message body
    out.assign(data + 4, data + 4 + msg_len);
    return true;
}

} // namespace cboe
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
