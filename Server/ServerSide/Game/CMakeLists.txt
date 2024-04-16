set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
set(CMAKE_CXX_STANDARD 20)
add_library(
    Game
    Game.cpp
)

add_subdirectory(Component)
add_subdirectory(System)
target_link_libraries(Game ServerSystem)

target_include_directories(Game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    "${CMAKE_CURRENT_SOURCE_DIR}/Component"
    "${CMAKE_CURRENT_SOURCE_DIR}/ECS"
    "${CMAKE_CURRENT_SOURCE_DIR}/System/Controllable"
    "${CMAKE_CURRENT_SOURCE_DIR}/System"
    "${CMAKE_SOURCE_DIR}"
    "${CMAKE_SOURCE_DIR}/AEngine"
    "${CMAKE_SOURCE_DIR}/SFMLEngine"
)
set_property(TARGET Game PROPERTY POSITION_INDEPENDENT_CODE ON)