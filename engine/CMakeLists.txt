cmake_minimum_required(VERSION 3.16)
project(cboe_core VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O2")

# Find required packages
find_package(GTest REQUIRED)
find_package(benchmark QUIET)

# If benchmark not found via find_package, try manual search
if(NOT benchmark_FOUND)
    find_library(BENCHMARK_LIBRARY NAMES benchmark)
    find_path(BENCHMARK_INCLUDE_DIR NAMES benchmark/benchmark.h)
    if(BENCHMARK_LIBRARY AND BENCHMARK_INCLUDE_DIR)
        set(benchmark_FOUND TRUE)
    endif()
endif()

# Create the main library
add_library(cboe_core
    src/Allocator.cpp
    src/Buffer.cpp
    src/Deserializer.cpp
    src/FramingEngine.cpp
    src/Serializer.cpp
)

# Set library properties
set_target_properties(cboe_core PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER "include/cboe/Allocator.h;include/cboe/Buffer.h;include/cboe/Deserializer.h;include/cboe/FramingEngine.h;include/cboe/Messages.h;include/cboe/Serializer.h;include/cboe/util.h"
)

# Set include directories
target_include_directories(cboe_core
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# Install rules
install(TARGETS cboe_core
    EXPORT cboe_coreTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include
)

install(DIRECTORY include/cboe
    DESTINATION include
    FILES_MATCHING PATTERN "*.h"
)

# Install CMake package configuration
install(EXPORT cboe_coreTargets
    FILE cboe_coreTargets.cmake
    NAMESPACE cboe_core::
    DESTINATION lib/cmake/cboe_core
)

configure_file(cmake/cboe_coreConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/cboe_coreConfig.cmake
    @ONLY
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/cboe_coreConfig.cmake
    DESTINATION lib/cmake/cboe_core
)

# Enable testing
enable_testing()

# Add test and benchmark subdirectories
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/../tests)
    add_subdirectory(../tests ${CMAKE_CURRENT_BINARY_DIR}/tests)
endif()

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/../benchmarks)
    add_subdirectory(../benchmarks ${CMAKE_CURRENT_BINARY_DIR}/benchmarks)
endif()