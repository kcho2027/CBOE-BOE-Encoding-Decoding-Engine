cmake_minimum_required(VERSION 3.16)
project(CBOE_BOE_Engine VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

# Create the main library
add_library(cboe_core
    src/Serializer.cpp
    src/Deserializer.cpp
    src/FramingEngine.cpp
    src/Buffer.cpp
    src/Allocator.cpp
)

# Set library properties
set_target_properties(cboe_core PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER include/cboe/*.h
)

# Include directories
target_include_directories(cboe_core 
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Compiler-specific settings
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(cboe_core PRIVATE -fPIC)
endif()

# Install rules
install(TARGETS cboe_core
    EXPORT cboe_coreTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include
)

install(DIRECTORY include/cboe/
    DESTINATION include/cboe
    FILES_MATCHING PATTERN "*.h"
)

# Export targets
install(EXPORT cboe_coreTargets
    FILE cboe_coreTargets.cmake
    NAMESPACE cboe::
    DESTINATION lib/cmake/cboe_core
)

# Create config file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/cboe_coreConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cboe_coreConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cboe_coreConfig.cmake"
    INSTALL_DESTINATION lib/cmake/cboe_core
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/cboe_coreConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/cboe_coreConfigVersion.cmake"
    DESTINATION lib/cmake/cboe_core
)

# Enable testing
enable_testing()

# Find GTest if available
find_package(GTest QUIET)
if(GTest_FOUND AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../tests")
    add_subdirectory(../tests ${CMAKE_CURRENT_BINARY_DIR}/tests)
endif()

# Find Google Benchmark if available
find_package(benchmark QUIET)
if(benchmark_FOUND AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../benchmarks")
    add_subdirectory(../benchmarks ${CMAKE_CURRENT_BINARY_DIR}/benchmarks)
endif()