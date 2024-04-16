set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
set(CMAKE_CXX_STANDARD 20)
add_library(
    AEngine
    AEngine.cpp
    ASocket.cpp
    AEventEngine.cpp
)

target_include_directories(AEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
set_property(TARGET AEngine PROPERTY POSITION_INDEPENDENT_CODE ON)