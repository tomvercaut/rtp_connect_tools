include(../cmake/versions.cmake)

find_package(Boost ${RTP_CONNECT_TOOLS_DEP_BOOST_VERSION} EXACT)
find_package(fmt ${RTP_CONNECT_TOOLS_DEP_FMT_VERSION} EXACT REQUIRED)
find_package(spdlog ${RTP_CONNECT_TOOLS_DEP_SPDLOG_VERSION} EXACT REQUIRED)

add_lib(
        LIB_NAME rtp_connect_tools_core
        LIB_CMAKE_NAMESPACE rtp-connect-tools
        LIB_ALIAS_NAME core
        LIB_VERSION ${PROJECT_VERSION}
        LIB_PUBLIC_HEADERS
            include/rtp_connect_tools/core/parser.h
            include/rtp_connect_tools/core/rtp.h
        LIB_PRIVATE_SOURCES
            src/parser.cpp
        LIB_VERSION ${rtp_connect_tools_core_VERSION}
        LIB_PRIVATE_LIBRARIES
            Boost::headers
            spdlog::spdlog
            fmt::fmt
)

if (${BUILD_RTP_CONNECT_TOOLS_TESTS})
    add_subdirectory(tests)
endif ()
