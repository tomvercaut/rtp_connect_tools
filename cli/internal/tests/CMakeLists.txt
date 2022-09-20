find_package(Catch2 3 REQUIRED)

add_catch2_test(
        APP_NAME rtp_connect_tools_analyser_cli_internal_tests
        CXX_STANDARD 20
        APP_DEPENDENCIES
            rtp-connect-tools::analyser_cli_internal
        APP_PRIVATE_SOURCES
            src/main.cpp
        APP_PRIVATE_LIBRARIES
            rtp-connect-tools::analyser_cli_internal
            Catch2::Catch2
)
