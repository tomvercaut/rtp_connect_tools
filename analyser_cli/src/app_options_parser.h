#ifndef RTP_CONNECT_TOOLS_ANALYSER_CLI_APP_OPTIONS_PARSER_H
#define RTP_CONNECT_TOOLS_ANALYSER_CLI_APP_OPTIONS_PARSER_H

#include "app_options.h"

namespace rtp::connect::tools::analyser::cli {
auto ParseAppOptions(const std::string& app_name, int argc, char** argv)
    -> AppOptions;
} // namespace rtp::connect::tools::analyser::cli

#endif  // RTP_CONNECT_TOOLS_ANALYSER_CLI_APP_OPTIONS_PARSER_H
