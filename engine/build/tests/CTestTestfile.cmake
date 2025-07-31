# CMake generated Testfile for 
# Source directory: /Users/Ronald/Documents/GitHub/CBOE-BOE-Encoding-Decoding-Engine/tests
# Build directory: /Users/Ronald/Documents/GitHub/CBOE-BOE-Encoding-Decoding-Engine/engine/build/tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(SerializerTests "/Users/Ronald/Documents/GitHub/CBOE-BOE-Encoding-Decoding-Engine/engine/build/tests/cboe_tests" "--gtest_filter=SerializerTests*")
set_tests_properties(SerializerTests PROPERTIES  _BACKTRACE_TRIPLES "/Users/Ronald/Documents/GitHub/CBOE-BOE-Encoding-Decoding-Engine/tests/CMakeLists.txt;25;add_test;/Users/Ronald/Documents/GitHub/CBOE-BOE-Encoding-Decoding-Engine/tests/CMakeLists.txt;0;")
add_test(FramingEngineTests "/Users/Ronald/Documents/GitHub/CBOE-BOE-Encoding-Decoding-Engine/engine/build/tests/cboe_tests" "--gtest_filter=FramingEngineTests*")
set_tests_properties(FramingEngineTests PROPERTIES  _BACKTRACE_TRIPLES "/Users/Ronald/Documents/GitHub/CBOE-BOE-Encoding-Decoding-Engine/tests/CMakeLists.txt;26;add_test;/Users/Ronald/Documents/GitHub/CBOE-BOE-Encoding-Decoding-Engine/tests/CMakeLists.txt;0;")
add_test(AllTests "/Users/Ronald/Documents/GitHub/CBOE-BOE-Encoding-Decoding-Engine/engine/build/tests/cboe_tests")
set_tests_properties(AllTests PROPERTIES  _BACKTRACE_TRIPLES "/Users/Ronald/Documents/GitHub/CBOE-BOE-Encoding-Decoding-Engine/tests/CMakeLists.txt;27;add_test;/Users/Ronald/Documents/GitHub/CBOE-BOE-Encoding-Decoding-Engine/tests/CMakeLists.txt;0;")
add_test(Benchmarks "/Users/Ronald/Documents/GitHub/CBOE-BOE-Encoding-Decoding-Engine/engine/build/tests/cboe_benchmarks")
set_tests_properties(Benchmarks PROPERTIES  _BACKTRACE_TRIPLES "/Users/Ronald/Documents/GitHub/CBOE-BOE-Encoding-Decoding-Engine/tests/CMakeLists.txt;51;add_test;/Users/Ronald/Documents/GitHub/CBOE-BOE-Encoding-Decoding-Engine/tests/CMakeLists.txt;0;")
