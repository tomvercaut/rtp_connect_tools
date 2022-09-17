include(../../cmake/versions.cmake)

find_package(Catch2 ${RTP_CONNECT_TOOLS_DEP_CATCH2_VERSION} REQUIRED)

add_catch2_test(
        APP_NAME rtp_connect_tools_analyser_tests
        APP_DEPENDENCIES
            rtp-connect-tools::core
            rtp-connect-tools::analyser
        APP_PRIVATE_SOURCES
            src/main.cpp
            src/machine_profile.cpp
        APP_PRIVATE_LIBRARIES
            rtp-connect-tools::core
            rtp-connect-tools::analyser
            spdlog::spdlog
            Catch2::Catch2
)
