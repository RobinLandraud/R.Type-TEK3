set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
set(CMAKE_CXX_STANDARD 20)
add_library(
    ServerGameEntity
    gameEntity.cpp
)

target_include_directories(ServerGameEntity PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    "${CMAKE_SOURCE_DIR}/Game/ECS"
    "${CMAKE_SOURCE_DIR}/Game/Component"
    "${CMAKE_SOURCE_DIR}/Game/System/Executor"
    "${CMAKE_SOURCE_DIR}/Game/System/Controllable"
    "${CMAKE_SOURCE_DIR}/Utils"
    "${CMAKE_SOURCE_DIR}/Protocol"
    "${CMAKE_SOURCE_DIR}/AEngine"
)
set_property(TARGET ServerGameEntity PROPERTY POSITION_INDEPENDENT_CODE ON)