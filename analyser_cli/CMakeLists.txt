include(../cmake/versions.cmake)

find_package(Boost ${RTP_CONNECT_TOOLS_DEP_BOOST_VERSION} EXACT COMPONENTS program_options system)
find_package(fmt ${RTP_CONNECT_TOOLS_DEP_FMT_VERSION} EXACT REQUIRED)
find_package(spdlog ${RTP_CONNECT_TOOLS_DEP_SPDLOG_VERSION} EXACT REQUIRED)
find_package(tomlplusplus ${RTP_CONNECT_TOOLS_DEP_TOMLPLUSPLUS_VERSION} EXACT REQUIRED)

add_lib(
        LIB_NAME rtp_connect_tools_analyser_cli_dep
        LIB_CMAKE_NAMESPACE rtp-connect-tools
        LIB_ALIAS_NAME analyser_cli_dep
        LIB_VERSION ${PROJECT_VERSION}
        LIB_PUBLIC_SOURCES
            include/rtp_connect_tools/analyser/cli/app_launch.h
            include/rtp_connect_tools/analyser/cli/reporter_cli.h
        LIB_PRIVATE_SOURCES
            src/app_launch.cpp
            src/app_options.cpp
            src/app_options.h
            src/app_options_parser.cpp
            src/app_options_parser.h
            src/reporter_cli.cpp
        LIB_VERSION ${rtp_connect_tools_analyser_cli_dep_VERSION}
        LIB_PRIVATE_LIBRARIES
            rtp-connect-tools::core
            rtp-connect-tools::analyser
            Boost::headers
            Boost::program_options
            Boost::system
            spdlog::spdlog
            fmt::fmt
            tomlplusplus::tomlplusplus
)

add_app(
        APP_NAME rtp_connect_tools_analyser_cli
        APP_CMAKE_NAMESPACE rtp-connect-tools
        APP_OUTPUT_NAME rtp_connect_tools_analyser_cli
        APP_VERSION ${PROJECT_VERSION}
        APP_PRIVATE_INCLUDE_DIR
            rtp_connect_tools/analyser/cli
        APP_PRIVATE_SOURCES
            src/main.cpp
        APP_PRIVATE_LIBRARIES
            rtp-connect-tools::core
            rtp-connect-tools::analyser
            rtp-connect-tools::analyser_cli_dep
)
