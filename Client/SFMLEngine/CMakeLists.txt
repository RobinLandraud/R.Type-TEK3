set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
set(CMAKE_CXX_STANDARD 20)
add_library(
    SFMLEngine
    SFMLEngine.cpp
    SFMLSocket.cpp
)

add_subdirectory(Graphics)
add_subdirectory(Audio)
add_subdirectory(Event)
add_subdirectory(Window)

target_link_libraries(SFMLEngine Graphics)
target_link_libraries(SFMLEngine Audio)
target_link_libraries(SFMLEngine Event)
target_link_libraries(SFMLEngine Window)

target_include_directories(SFMLEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    "${CMAKE_SOURCE_DIR}/AEngine"
)
set_property(TARGET SFMLEngine PROPERTY POSITION_INDEPENDENT_CODE ON)