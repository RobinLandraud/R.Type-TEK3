set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
set(CMAKE_CXX_STANDARD 20)
add_library(
    Core
    Core.cpp
)

target_include_directories(Core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
"${CMAKE_SOURCE_DIR}/ECS"
"${CMAKE_SOURCE_DIR}/AEngine"
"${CMAKE_SOURCE_DIR}/IEngine"
"${CMAKE_SOURCE_DIR}/SFMLEngine/Audio"
"${CMAKE_SOURCE_DIR}/SFMLEngine/Event"
"${CMAKE_SOURCE_DIR}/SFMLEngine/Graphics"
"${CMAKE_SOURCE_DIR}/SFMLEngine/Window"
"${CMAKE_SOURCE_DIR}/SFMLEngine"
"${CMAKE_SOURCE_DIR}/Component"
"${CMAKE_SOURCE_DIR}/System/Controllable"
"${CMAKE_SOURCE_DIR}/System/Button"
"${CMAKE_SOURCE_DIR}/System/Executor"
"${CMAKE_SOURCE_DIR}/System/GameEntity"
"${CMAKE_SOURCE_DIR}/System"
"${CMAKE_SOURCE_DIR}/Utils"
"${CMAKE_SOURCE_DIR}/Protocol"
"${CMAKE_SOURCE_DIR}/Script"
)
set_property(TARGET AEngine PROPERTY POSITION_INDEPENDENT_CODE ON)