set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
set(CMAKE_CXX_STANDARD 20)
add_library(
    System
    drawSystem.cpp
    InputSystem.cpp
    KeyboardEventSystem.cpp
    execSystem.cpp
    gameSystem.cpp
    blinkSystem.cpp
    clocksSystem.cpp
    MouseEventSystem.cpp
    serverSystem.cpp
)

add_subdirectory(Controllable)
add_subdirectory(GameEntity)
add_subdirectory(Executor)
add_subdirectory(Button)

target_link_libraries(System GameEntity)
target_link_libraries(System Controllable)
target_link_libraries(System Executor)
target_link_libraries(System Button)

target_include_directories(System PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    "${CMAKE_SOURCE_DIR}/Protocol"
    "${CMAKE_SOURCE_DIR}/ECS"
    "${CMAKE_SOURCE_DIR}/Component"
    "${CMAKE_SOURCE_DIR}/AEngine"
    "${CMAKE_SOURCE_DIR}/Utils"
    "${CMAKE_CURRENT_SOURCE_DIR}/Controllable"
    "${CMAKE_CURRENT_SOURCE_DIR}/Button"
    "${CMAKE_CURRENT_SOURCE_DIR}/Executor"
    "${CMAKE_CURRENT_SOURCE_DIR}/GameEntity"
)
set_property(TARGET System PROPERTY POSITION_INDEPENDENT_CODE ON)