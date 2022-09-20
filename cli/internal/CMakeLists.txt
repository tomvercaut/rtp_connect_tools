include(../../cmake/versions.cmake)

find_package(Boost ${RTP_CONNECT_TOOLS_DEP_BOOST_VERSION} EXACT COMPONENTS program_options system)
find_package(fmt ${RTP_CONNECT_TOOLS_DEP_FMT_VERSION} EXACT REQUIRED)
find_package(spdlog ${RTP_CONNECT_TOOLS_DEP_SPDLOG_VERSION} EXACT REQUIRED)
find_package(tomlplusplus ${RTP_CONNECT_TOOLS_DEP_TOMLPLUSPLUS_VERSION} EXACT REQUIRED)

add_lib(
        LIB_NAME rtp_connect_tools_analyser_cli_internal
        LIB_CMAKE_NAMESPACE rtp-connect-tools
        CXX_STANDARD 20
        LIB_ALIAS_NAME analyser_cli_internal
        LIB_VERSION ${PROJECT_VERSION}
        LIB_PUBLIC_HEADERS
            include/rtp_connect_tools/analyser/cli/app_launch.h
            include/rtp_connect_tools/analyser/cli/reporter_cli.h
        LIB_PRIVATE_SOURCES
            src/app_launch.cpp
            src/app_options.cpp
            src/app_options.h
            src/app_options_parser.cpp
            src/app_options_parser.h
            src/reporter_cli.cpp
        # LIB_PUBLIC_LIBRARIES
        LIB_PRIVATE_LIBRARIES
            rtp-connect-tools::core
            rtp-connect-tools::analyser
            Boost::headers
            Boost::program_options
            Boost::system
            spdlog::spdlog
            fmt::fmt
            tomlplusplus::tomlplusplus
        # LIB_PRIVATE_HEADERS
)
if (${BUILD_RTP_CONNECT_TOOLS_TESTS})
    add_subdirectory(tests)
endif ()
