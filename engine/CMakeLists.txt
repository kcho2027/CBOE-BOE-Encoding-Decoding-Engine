add_library(cboe_core
    src/Serializer.cpp
    src/Deserializer.cpp
    src/FramingEngine.cpp
)

target_include_directories(cboe_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)