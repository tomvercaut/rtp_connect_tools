include(../cmake/versions.cmake)

#find_package(Boost ${RTP_CONNECT_TOOLS_DEP_BOOST_VERSION} EXACT COMPONENTS program_options system)
find_package(CLI11 ${RTP_CONNECT_TOOLS_DEP_CLI11_VERSION} EXACT REQUIRED)
find_package(fmt ${RTP_CONNECT_TOOLS_DEP_FMT_VERSION} EXACT REQUIRED)
find_package(spdlog ${RTP_CONNECT_TOOLS_DEP_SPDLOG_VERSION} EXACT REQUIRED)
find_package(tomlplusplus ${RTP_CONNECT_TOOLS_DEP_TOMLPLUSPLUS_VERSION} EXACT REQUIRED)
find_package(wxWidgets ${RTP_CONNECT_TOOLS_DEP_WX_WIDGETS_VERSION} REQUIRED COMPONENTS core base)

include(${wxWidgets_USE_FILE})

add_app(
        APP_NAME rtp_connect_tools_analyser_ui
        APP_CMAKE_NAMESPACE rtp-connect-tools
        CXX_STANDARD 20
        APP_OUTPUT_NAME rtp_analyser_ui
        APP_VERSION ${PROJECT_VERSION}
        APP_PRIVATE_INCLUDE_DIR
            rtp_connect_tools/analyser/ui
        APP_PRIVATE_SOURCES
            src/app.cpp
            src/app_frame.cpp
            src/app_options.cpp
            src/app_options_parser.cpp
            src/default_controller.cpp
            src/main.cpp
            src/minimum_leaf_distance.cpp
            src/mlc_count.cpp
            src/model_view.cpp
            src/model_view_reporter.cpp
        # APP_PUBLIC_SOURCES
        # APP_PUBLIC_LIBRARIES
        APP_PRIVATE_LIBRARIES
            rtp-connect-tools::core
            rtp-connect-tools::analyser
#            Boost::headers
#            Boost::program_options
#            Boost::system
            spdlog::spdlog
            fmt::fmt
            tomlplusplus::tomlplusplus
            ${wxWidgets_LIBRARIES}
        # APP_DEPENDENCIES
)
if (WIN32)
    # https://windows-hexerror.linestarve.com/q/so61860910-how-do-i-compile-a-wxwidgets-hello-world-app-with-clion-and-the-msvc-compiler-toolchain-without-erro
    set_target_properties(rtp_connect_tools_analyser_ui PROPERTIES LINK_FLAGS /SUBSYSTEM:WINDOWS)
endif ()