set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
set(CMAKE_CXX_STANDARD 20)
add_library(
    ServerAEngine
    ASocket.cpp
)


target_include_directories(ServerAEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
set_property(TARGET ServerAEngine PROPERTY POSITION_INDEPENDENT_CODE ON)