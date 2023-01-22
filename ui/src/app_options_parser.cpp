#include "rtp_connect_tools/analyser/ui/app_options_parser.h"

#include <CLI/CLI.hpp>
#include <iostream>

namespace rtp::connect::tools::analyser::ui {

void CliError(const CLI::ParseError& e) {
  std::cerr << "An error was caught while parsing the input arguments.\n\n"
            << "name: " << e.get_name() << "\n"
            << "message: " << e.what() << "\n"
            << "exit code: " << e.get_exit_code() << "\n\n";
  exit(e.get_exit_code());
}

auto ParseAppOptions(const std::string& app_name, int argc, char** argv)
    -> AppOptions {
  CLI::App app(app_name);
  AppOptions ao{};

  app.add_option("-i,--input", ao.monitor_directory,
                 "Directory monitored for RTP files")
      ->option_text("directory")
      ->required(true);
  app.add_option("-c,--config", ao.config_dir,
                 "Directory in which the machine profiles are stored.")
      ->option_text("directory")
      ->required(true);
  app.add_flag(
      "-v,--verbose", ao.verbose,
      "Verbose output to a log file [default: only warning or more severe is "
      "reported. If enabled, trace level reporting is turned on.");

  try {
    app.parse(argc, argv);
  } catch (const CLI::ParseError& e) {
    if (e.get_name() == "CallForHelp") {
      std::cout << app.help() << "\n";
      exit(0);
    } else {
      CliError(e);
    }
  }
  return ao;
}
}  // namespace rtp::connect::tools::analyser::ui
