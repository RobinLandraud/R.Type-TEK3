set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
set(CMAKE_CXX_STANDARD 20)
add_library(
    ServerControllable
    move.cpp
)

target_include_directories(ServerControllable PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    "${CMAKE_CURRENT_SOURCE_DIR}/../../ECS"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../AEngine"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../Component"
)
set_property(TARGET ServerControllable PROPERTY POSITION_INDEPENDENT_CODE ON)