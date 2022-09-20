project(rtp_connect_tools_analyser_cli
        LANGUAGES CXX
        VERSION 0.0.1
        )

add_app(
        APP_NAME rtp_connect_tools_analyser_cli
        APP_CMAKE_NAMESPACE rtp-connect-tools
        CXX_STANDARD 20
        APP_OUTPUT_NAME rtp_analyser_cli
        APP_VERSION ${PROJECT_VERSION}
        APP_PRIVATE_INCLUDE_DIR
            rtp_connect_tools/analyser/cli
        APP_PRIVATE_SOURCES
            src/main.cpp
        # APP_PUBLIC_SOURCES
        # APP_PUBLIC_LIBRARIES
        APP_PRIVATE_LIBRARIES
            rtp-connect-tools::core
            rtp-connect-tools::analyser
            rtp-connect-tools::analyser_cli_internal
        # APP_DEPENDENCIES
)
