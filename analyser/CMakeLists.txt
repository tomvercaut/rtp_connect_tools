include(../cmake/versions.cmake)

find_package(Boost ${RTP_CONNECT_TOOLS_DEP_BOOST_VERSION} EXACT)
find_package(fmt ${RTP_CONNECT_TOOLS_DEP_FMT_VERSION} EXACT REQUIRED)
find_package(spdlog ${RTP_CONNECT_TOOLS_DEP_SPDLOG_VERSION} EXACT REQUIRED)
find_package(tomlplusplus ${RTP_CONNECT_TOOLS_DEP_TOMLPLUSPLUS_VERSION} EXACT REQUIRED)

add_lib(
        LIB_NAME rtp_connect_tools_analyser
        LIB_CMAKE_NAMESPACE rtp-connect-tools
        LIB_ALIAS_NAME analyser
        LIB_VERSION ${PROJECT_VERSION}
        LIB_PUBLIC_HEADERS
            include/rtp_connect_tools/analyser/analyse.h
            include/rtp_connect_tools/analyser/machine_profile.h
            include/rtp_connect_tools/analyser/reporter.h
        LIB_PRIVATE_SOURCES
            src/analyse.cpp
            src/machine_profile.cpp
        LIB_PRIVATE_LIBRARIES
            rtp-connect-tools::core
            Boost::headers
            spdlog::spdlog
            fmt::fmt
            tomlplusplus::tomlplusplus
)

if (${BUILD_RTP_CONNECT_TOOLS_TESTS})
    add_subdirectory(tests)
endif ()