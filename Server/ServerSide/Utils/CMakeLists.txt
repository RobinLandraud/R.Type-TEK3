set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
set(CMAKE_CXX_STANDARD 20)
add_library(
    ServerUtils
    utils.cpp
)

target_include_directories(ServerUtils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    "${CMAKE_SOURCE_DIR}/Protocol"
)
set_property(TARGET ServerUtils PROPERTY POSITION_INDEPENDENT_CODE ON)