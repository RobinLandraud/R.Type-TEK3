if (NOT sfml_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        sfml
        GIT_REPOSITORY "https://github.com/SFML/SFML.git"
        GIT_TAG        "2.5.1"
    )
    FetchContent_GetProperties(sfml)
    if(NOT sfml_POPULATED)
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(sfml)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
        add_subdirectory(${sfml_SOURCE_DIR} ${sfml_BINARY_DIR})
    endif()
endif()