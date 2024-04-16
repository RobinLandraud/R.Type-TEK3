set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
add_library(
    Window
    SFMLWindowEngine.cpp
)

target_include_directories(Window PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    "${CMAKE_SOURCE_DIR}/AEngine"
)
set_property(TARGET Window PROPERTY POSITION_INDEPENDENT_CODE ON)