set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
set(CMAKE_CXX_STANDARD 20)
add_library(
    Server
    Server.cpp
)

target_include_directories(Server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    "${CMAKE_SOURCE_DIR}/Protocol"
    "${CMAKE_SOURCE_DIR}/Lobby"
    "${CMAKE_SOURCE_DIR}/Utils"
    "${CMAKE_SOURCE_DIR}/Game"
    "${CMAKE_SOURCE_DIR}"
    "${CMAKE_SOURCE_DIR}/AEngine" 
    "${CMAKE_SOURCE_DIR}/SFMLEngine"
    "${CMAKE_SOURCE_DIR}/Game/Component"
    "${CMAKE_SOURCE_DIR}/Game/ECS"
    "${CMAKE_SOURCE_DIR}/Game/System"
    "${CMAKE_SOURCE_DIR}/Game/System/Controllable"
)
set_property(TARGET Server PROPERTY POSITION_INDEPENDENT_CODE ON)