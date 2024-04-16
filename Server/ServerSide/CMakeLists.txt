CMAKE_MINIMUM_REQUIRED(VERSION 3.6)
project("r-type_server_engine" VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
#set(CMAKE_CXX_CLANG_TIDY "clang-tidy")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})

add_executable(
    ${PROJECT_NAME}
    main.cpp
)

find_package(Threads)
find_package(SFML 2.5
  REQUIRED
    system window graphics network audio)


add_subdirectory(Server)
add_subdirectory(Lobby)
add_subdirectory(Game)
add_subdirectory(SFMLEngine)
add_subdirectory(AEngine)
add_subdirectory(Utils)
target_link_libraries(${PROJECT_NAME} Server)
target_link_libraries(${PROJECT_NAME} Lobby)
target_link_libraries(${PROJECT_NAME} Game)
target_link_libraries(${PROJECT_NAME} ServerSFMLEngine)
target_link_libraries(${PROJECT_NAME} ServerAEngine)
target_link_libraries(${PROJECT_NAME} ServerUtils)

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-audio sfml-network)
target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(${PROJECT_NAME} ${CMAKE_DL_LIBS})


target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    "${CMAKE_SOURCE_DIR}/Protocol"
    "${CMAKE_SOURCE_DIR}/AEngine" 
    "${CMAKE_SOURCE_DIR}/SFMLEngine"
    "${CMAKE_SOURCE_DIR}/Lobby"
    "${CMAKE_SOURCE_DIR}/Server"
    "${CMAKE_SOURCE_DIR}/Utils" 
    "${CMAKE_SOURCE_DIR}/Game/Component"
    "${CMAKE_SOURCE_DIR}/Game/ECS"
    "${CMAKE_SOURCE_DIR}/Game/System"
    "${CMAKE_SOURCE_DIR}/Game/System/Controllable"
)