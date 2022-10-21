#include "rtp_connect_tools/analyser/cli/app_launch.h"

#include <boost/predef.h>
#include <spdlog/spdlog.h>

#include <filesystem>
#include <iostream>

#include "rtp_connect_tools/analyser/cli/reporter_cli.h"
#include "app_options_parser.h"
#include "rtp_connect_tools/analyser/analyse.h"
#include "rtp_connect_tools/analyser/machine_profile.h"
#include "rtp_connect_tools/core/parser.h"

namespace rtp::connect::tools::analyser::cli {

namespace core = rtp::connect::tools::core;
namespace analyser = rtp::connect::tools::analyser;


/// Get the default data directory is located [OS dependent].
///
/// Supported OS: Windows
/// \return Data directory path
auto DataDirectory() -> std::string;

auto AppLaunch(const std::string& app_name, int argc, char** argv) -> int {
  auto app_options = ParseAppOptions(app_name, argc, argv);
  std::cout << app_options << std::endl;

  // If no data directory was provided, set the default data directory
  if (app_options.data_directory.empty()) {
    app_options.data_directory = DataDirectory();
  }

  if (!std::filesystem::is_regular_file(app_options.input_file)) {
    spdlog::error("Input file [{}] doesn't exist.", app_options.input_file);
    return EXIT_FAILURE;
  }
  if (!std::filesystem::is_directory(app_options.data_directory)) {
    spdlog::error("Data directory [{}] doesn't exist.",
                  app_options.data_directory);
    return EXIT_FAILURE;
  }

  // Read all the machine profiles
  auto profiles =
      analyser::ListMachineProfiles((std::filesystem::path{app_options.data_directory}));
  // Read the RTP file
  auto rtp = core::ParseRtpFile(app_options.input_file);
  // Create a reporter
  auto reporter = ReporterCli(&rtp);
  return LaunchAnalysis(rtp, profiles, reporter);
}

auto LaunchAnalysis(const core::Rtp& rtp,
                         const std::vector<analyser::MachineProfile>& profiles,
                         analyser::Reporter& reporter) -> int {
  try {
    // Analyse
    analyser::Analyse(rtp, profiles, reporter);
  } catch (const std::exception& ex) {
    spdlog::error("Exception caught: {}", ex.what());
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

auto DataDirectory() -> std::string {
#ifdef BOOST_OS_WINDOWS
  return R"(C:/ProgramData/rtp-analyser)";
#else
  static_assert(
      "Machine profile directory is not defined for the current operating "
      "system");
#endif
}

}  // namespace rtp::connect::tools::analyser::cli