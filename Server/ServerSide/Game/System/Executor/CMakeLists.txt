set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
set(CMAKE_CXX_STANDARD 20)
add_library(
    ServerExecutor
    exec.cpp
)

target_include_directories(ServerExecutor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    "${CMAKE_SOURCE_DIR}/Game/ECS"
    "${CMAKE_SOURCE_DIR}/Game/Component"
    "${CMAKE_SOURCE_DIR}/AEngine"
    "${CMAKE_SOURCE_DIR}/Utils"
    "${CMAKE_SOURCE_DIR}/Protocol"
    "${CMAKE_SOURCE_DIR}"
)
set_property(TARGET ServerExecutor PROPERTY POSITION_INDEPENDENT_CODE ON)