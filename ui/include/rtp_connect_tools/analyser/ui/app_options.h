#ifndef RTP_CONNECT_TOOLS_ANALYSER_INCLUDE_RTP_CONNECT_ANALYSER_UI_APP_OPTIONS_H
#define RTP_CONNECT_TOOLS_ANALYSER_INCLUDE_RTP_CONNECT_ANALYSER_UI_APP_OPTIONS_H

#include <ostream>
#include <string>

namespace rtp::connect::tools::analyser::ui {

class AppOptions {
 public:
  // Directory in which RTP files are monitored.
  std::string monitor_directory{};
  // Directory with application configuration files
  std::string config_dir{};
  // Verbose output
  bool verbose{false};
};

auto operator<<(std::ostream& os, const AppOptions& options) -> std::ostream&;

}  // namespace rtp::connect::tools::analyser::ui

#endif  // RTP_CONNECT_TOOLS_ANALYSER_INCLUDE_RTP_CONNECT_ANALYSER_UI_APP_OPTIONS_H
