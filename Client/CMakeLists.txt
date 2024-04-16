CMAKE_MINIMUM_REQUIRED(VERSION 3.6)
project("r-type_client_engine" VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
#set(CMAKE_CXX_CLANG_TIDY "clang-tidy")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS_DEBUG "-g3 -ggdb -O0")


set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})

include_directories(../ChaiScript-6.1.0/include)


add_executable(
    ${PROJECT_NAME}
    main.cpp
    )
    
find_package(Threads)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
find_package(sfml 2.5 COMPONENTS system window graphics network audio REQUIRED)

add_subdirectory(Utils)
add_subdirectory(SFMLEngine)
add_subdirectory(AEngine)
add_subdirectory(System)
add_subdirectory(Core)
add_subdirectory(Component)
target_link_libraries(${PROJECT_NAME} SFMLEngine)
target_link_libraries(${PROJECT_NAME} AEngine)
target_link_libraries(${PROJECT_NAME} Core)
target_link_libraries(${PROJECT_NAME} System)
target_link_libraries(${PROJECT_NAME} Utils)

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-audio sfml-network)
target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(${PROJECT_NAME} ${CMAKE_DL_LIBS})


target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    "${CMAKE_SOURCE_DIR}/Protocol"
    "${CMAKE_SOURCE_DIR}/Script"
    "${CMAKE_SOURCE_DIR}/Utils"
    "${CMAKE_SOURCE_DIR}/AEngine"
    "${CMAKE_SOURCE_DIR}/IEngine"
    "${CMAKE_SOURCE_DIR}/SFMLEngine"
    "${CMAKE_SOURCE_DIR}/System"
    "${CMAKE_SOURCE_DIR}/System/Controllable"
    "${CMAKE_SOURCE_DIR}/System/Button"
    "${CMAKE_SOURCE_DIR}/System/Executor"
    "${CMAKE_SOURCE_DIR}/Component"
    "${CMAKE_SOURCE_DIR}/Core"
    "${CMAKE_SOURCE_DIR}/build/_deps/sfml-src/include"
)