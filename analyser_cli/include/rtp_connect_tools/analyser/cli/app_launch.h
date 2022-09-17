#ifndef RTP_CONNECT_TOOLS_ANALYSER_CLI_APP_LAUNCH_H
#define RTP_CONNECT_TOOLS_ANALYSER_CLI_APP_LAUNCH_H

#include <string>

#include "rtp_connect_tools/core/rtp.h"
#include "rtp_connect_tools/analyser/machine_profile.h"
#include "rtp_connect_tools/analyser/reporter.h"

namespace rtp::connect::tools::analyser::cli {
auto AppLaunch(const std::string& app_name, int argc, char** argv) -> int;
auto LaunchAnalysis(const rtp::connect::tools::core::Rtp& rtp,
                   const std::vector<rtp::connect::tools::analyser::MachineProfile>& profiles,
                   rtp::connect::tools::analyser::Reporter& reporter) -> int;
} // namespace rtp::connect::tools::analyser::cli

#endif  // RTP_CONNECT_TOOLS_ANALYSER_CLI_APP_LAUNCH_H
