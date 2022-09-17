#ifndef RTP_CONNECT_TOOLS_ANALYSER_CLI_APP_OPTIONS_H
#define RTP_CONNECT_TOOLS_ANALYSER_CLI_APP_OPTIONS_H

#include <ostream>
#include <string>

namespace rtp::connect::tools::analyser::cli {

class AppOptions {
 public:
  std::string input_file{};
  std::string output_file{};
  std::string data_directory{};
};

auto operator<<(std::ostream& os, const AppOptions& options) -> std::ostream&;

}  // namespace rtp::connect::tools::analyser::cli

#endif  // RTP_CONNECT_TOOLS_ANALYSER_CLI_APP_OPTIONS_H
