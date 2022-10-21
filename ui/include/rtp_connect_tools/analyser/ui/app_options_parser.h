#ifndef RTP_CONNECT_TOOLS_ANALYSER_UI_INCLUDE_RTP_CONNECT_TOOLS_ANALYSER_UI_APP_OPTIONS_PARSER_H
#define RTP_CONNECT_TOOLS_ANALYSER_UI_INCLUDE_RTP_CONNECT_TOOLS_ANALYSER_UI_APP_OPTIONS_PARSER_H

#include "rtp_connect_tools/analyser/ui/app_options.h"

namespace rtp::connect::tools::analyser::ui {
auto ParseAppOptions(const std::string& app_name, int argc, char** argv)
    -> AppOptions;
}  // namespace rtp::connect::tools::analyser::ui

#endif  // RTP_CONNECT_TOOLS_ANALYSER_UI_INCLUDE_RTP_CONNECT_TOOLS_ANALYSER_UI_APP_OPTIONS_PARSER_H
