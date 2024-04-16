set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
set(CMAKE_CXX_STANDARD 20)
add_library(
    Utils
    utils.cpp
)

target_include_directories(Utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    "${CMAKE_SOURCE_DIR}/Protocol"
)
set_property(TARGET Utils PROPERTY POSITION_INDEPENDENT_CODE ON)