set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
set(CMAKE_CXX_STANDARD 20)
add_library(
    ServerSystem
    execSystem.cpp
    gameSystem.cpp
    clocksSystem.cpp
    progressSystem.cpp
)

add_subdirectory(Controllable)
add_subdirectory(Executor)
add_subdirectory(GameEntity)

target_link_libraries(ServerSystem ServerControllable)
target_link_libraries(ServerSystem ServerExecutor)
target_link_libraries(ServerSystem ServerGameEntity)

target_include_directories(ServerSystem PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    "${CMAKE_SOURCE_DIR}/SFMLEngine"
    "${CMAKE_CURRENT_SOURCE_DIR}/../ECS"
    "${CMAKE_CURRENT_SOURCE_DIR}/../Component"
    "${CMAKE_SOURCE_DIR}/AEngine"
    "${CMAKE_CURRENT_SOURCE_DIR}/Controllable"
    "${CMAKE_CURRENT_SOURCE_DIR}/Executor"
    "${CMAKE_SOURCE_DIR}"
)
set_property(TARGET ServerSystem PROPERTY POSITION_INDEPENDENT_CODE ON)