#include "app_options.h"

namespace rtp::connect::tools::analyser::cli {

auto operator<<(std::ostream& os, const AppOptions& options) -> std::ostream & {
  os << "AppOptions:\n";
  os << "  input file: " << options.input_file << "\n";
  return os;
}
}