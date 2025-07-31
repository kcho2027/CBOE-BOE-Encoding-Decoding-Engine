# Test configuration
find_package(GTest REQUIRED)

# Create test executable
add_executable(cboe_tests
    SerializerTests.cpp
    FramingEngineTests.cpp
)

# Link against our library and GTest
target_link_libraries(cboe_tests
    PRIVATE
        cboe_core
        GTest::gtest
        GTest::gtest_main
)

# Include directories
target_include_directories(cboe_tests
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../engine/include
)

# Add tests
add_test(NAME SerializerTests COMMAND cboe_tests --gtest_filter=SerializerTests*)
add_test(NAME FramingEngineTests COMMAND cboe_tests --gtest_filter=FramingEngineTests*)
add_test(NAME AllTests COMMAND cboe_tests)

# Check if Google Benchmark is available
find_package(benchmark QUIET)
if(benchmark_FOUND)
    # Create benchmark executable
    add_executable(cboe_benchmarks
        Benchmark.cpp
    )
    
    # Link against our library and benchmark
    target_link_libraries(cboe_benchmarks
        PRIVATE
            cboe_core
            benchmark::benchmark
    )
    
    # Include directories
    target_include_directories(cboe_benchmarks
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/../engine/include
    )
    
    # Add benchmark test
    add_test(NAME Benchmarks COMMAND cboe_benchmarks)
else()
    message(STATUS "Google Benchmark not found - skipping benchmark tests")
endif() 