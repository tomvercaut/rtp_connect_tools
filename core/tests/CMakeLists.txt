include(../../cmake/versions.cmake)

find_package(Catch2 ${RTP_CONNECT_TOOLS_DEP_CATCH2_VERSION} REQUIRED)

add_catch2_test(
        APP_NAME rtp_connect_tools_core_tests
        APP_DEPENDENCIES
            rtp-connect-tools::core
        APP_PRIVATE_SOURCES
            src/main.cpp
            src/parser.cpp
            src/split.cpp
        APP_PRIVATE_LIBRARIES
            rtp-connect-tools::core
            spdlog::spdlog
            Catch2::Catch2
)
