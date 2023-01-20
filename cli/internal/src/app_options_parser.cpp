#include "app_options_parser.h"

#include <CLI/CLI.hpp>
#include <iostream>

namespace rtp::connect::tools::analyser::cli {

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
  AppOptions ao;

  app.add_option("-i,--input", ao.input_file, "RTP input file")
      ->required(true)
      ->option_text("file");
  //  app.add_option("-o,--output", ao.output_file, "Write results to a file.");
  app.add_option("--data", ao.data_directory,
                 "Data directory in which the machine profiles are stored.")
      ->option_text("directory");

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
}  // namespace rtp::connect::tools::analyser::cli
