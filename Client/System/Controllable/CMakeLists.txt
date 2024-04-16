set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
set(CMAKE_CXX_STANDARD 20)
add_library(
    Controllable
    move.cpp
)

target_include_directories(Controllable PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    "${CMAKE_SOURCE_DIR}/ECS"
    "${CMAKE_SOURCE_DIR}/Component"
    "${CMAKE_SOURCE_DIR}/AEngine"
    "${CMAKE_SOURCE_DIR}/System/Button"
    "${CMAKE_SOURCE_DIR}/System/Executor"
    "${CMAKE_SOURCE_DIR}/System/GameEntity"
    "${CMAKE_SOURCE_DIR}/Utils"
    "${CMAKE_SOURCE_DIR}/Protocol"
)
set_property(TARGET Controllable PROPERTY POSITION_INDEPENDENT_CODE ON)