#include "rtp_connect_tools/analyser/ui/app_options.h"

namespace rtp::connect::tools::analyser::ui {

auto operator<<(std::ostream& os, const AppOptions& options) -> std::ostream & {
  os << "AppOptions:\n";
  os << "  monitor directory: " << options.monitor_directory << "\n";
  os << "  machine profile directory: " << options.config_dir << "\n";
  os << "  verbose: " << options.verbose << "\n";
  return os;
}
}