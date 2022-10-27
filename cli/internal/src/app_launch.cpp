#include "rtp_connect_tools/analyser/cli/app_launch.h"

#include <boost/predef.h>
#include <spdlog/spdlog.h>

#include <filesystem>
#include <fstream>
#include <iostream>

#include "app_options_parser.h"
#include "rtp_connect_tools/analyser/analyse.h"
#include "rtp_connect_tools/analyser/cli/reporter_cli.h"
#include "rtp_connect_tools/analyser/machine_profile.h"
#include "rtp_connect_tools/core/parser.h"

namespace rtp::connect::tools::analyser::cli {

namespace core = rtp::connect::tools::core;
namespace analyser = rtp::connect::tools::analyser;

///
/// List all the machine profiles in a directory.
///
/// Machine profile filenames are prefixed with machine_
///
/// \param dir directory path
/// \return A list of machine profiles.
auto ListMachineProfiles(const std::filesystem::path& dir)
    -> std::vector<MachineProfile>;

/// Get the default data directory is located [OS dependent].
///
/// Supported OS: Windows
/// \return Data directory path
auto DataDirectory() -> std::string;

auto AppLaunch(const std::string& app_name, int argc, char** argv) -> int {
  auto app_options = ParseAppOptions(app_name, argc, argv);

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
      ListMachineProfiles((std::filesystem::path{app_options.data_directory}));
  // Read the RTP file
  auto rtp = core::ParseRtpFile(app_options.input_file);
  // Create a reporter
  auto reporter = ReporterCli(&rtp);
  std::ofstream output_stream;
  // Open a file stream to report the analysis
  try {
    if (!app_options.output_file.empty()) {
      output_stream.open(app_options.output_file);
      if (!output_stream.is_open()) {
        spdlog::error("Failed to open {}", app_options.output_file);
        return EXIT_FAILURE;
      }
      reporter.Stream(output_stream);
    }
  } catch (const std::exception& ex) {
    spdlog::error(ex.what());
    return EXIT_FAILURE;
  }

  auto rv = LaunchAnalysis(rtp, profiles, reporter);

  // Close the file stream if needed
  try {
    if (!app_options.output_file.empty()) {
      output_stream.close();
      reporter.Stream(std::cout);
      if (output_stream.is_open()) {
        spdlog::error("Failed to close {}", app_options.output_file);
        return EXIT_FAILURE;
      }
    }
  } catch (const std::exception& ex) {
    spdlog::error(ex.what());
    return EXIT_FAILURE;
  }
  return rv;
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

auto ListMachineProfiles(const std::filesystem::path& dir)
    -> std::vector<analyser::MachineProfile> {
  std::vector<analyser::MachineProfile> profiles;
  for (const auto& dir_entry : std::filesystem::directory_iterator{dir}) {
    if (!dir_entry.is_regular_file()) {
      continue;
    }
    const auto& path = dir_entry.path();
    const auto filename = path.filename();
    if (!filename.string().starts_with("machine_")) {
      continue;
    }
    analyser::MachineProfile profile;
    if (analyser::ReadMachineProfile(profile, dir_entry.path().string()) == 0) {
      profiles.push_back(profile);
    }
  }
  return profiles;
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