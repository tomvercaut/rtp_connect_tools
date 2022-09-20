#include "rtp_connect_tools/analyser/cli/app_launch.h"
#include "rtp_connect_tools/analyser/cli/app_name.h"

namespace cli = rtp::connect::tools::analyser::cli;

auto main(int argc, char** argv) -> int {
  return cli::AppLaunch(cli::APP_NAME, argc, argv);
}
