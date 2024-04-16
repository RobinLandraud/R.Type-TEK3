set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
set(CMAKE_CXX_STANDARD 20)
add_library(
    Event
    SFMLEventEngine.cpp
)

target_include_directories(Event PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    "${CMAKE_SOURCE_DIR}/AEngine"
)
set_property(TARGET Event PROPERTY POSITION_INDEPENDENT_CODE ON)