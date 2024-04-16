set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
set(CMAKE_CXX_STANDARD 20)
add_library(
    Graphics
    SFMLGraphicsEngine.cpp
)

target_include_directories(Graphics PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    "${CMAKE_SOURCE_DIR}/AEngine"
)
set_property(TARGET Graphics PROPERTY POSITION_INDEPENDENT_CODE ON)