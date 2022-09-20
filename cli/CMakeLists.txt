cmake_minimum_required(VERSION ${CMAKE_VERSION})

project(app
        LANGUAGES CXX
        VERSION 0.0.1
        )

include(cmake/cmake_helpers.cmake)

add_subdirectory(internal)
add_subdirectory(app)
