cmake_minimum_required(VERSION 3.24)

project(rtp-connect-tools
    LANGUAGES CXX
    VERSION 0.0.1
)

include(cmake/cmake_helpers.cmake)

option(BUILD_RTP_CONNECT_TOOLS_TESTS "Build tests" ON)

add_subdirectory(core)
add_subdirectory(analyser)
add_subdirectory(cli)
add_subdirectory(ui)
