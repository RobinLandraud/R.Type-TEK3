set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
set(CMAKE_CXX_STANDARD 20)
add_library(
    GameEntity
    gameEntity.cpp
)

target_include_directories(GameEntity PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    "${CMAKE_SOURCE_DIR}/ECS"
    "${CMAKE_SOURCE_DIR}/Component"
    "${CMAKE_SOURCE_DIR}/AEngine"
    "${CMAKE_SOURCE_DIR}/System/Button"
    "${CMAKE_SOURCE_DIR}/System/Executor"
    "${CMAKE_SOURCE_DIR}/System/Controllable"
    "${CMAKE_SOURCE_DIR}/Utils"
    "${CMAKE_SOURCE_DIR}/Protocol"
)
set_property(TARGET GameEntity PROPERTY POSITION_INDEPENDENT_CODE ON)