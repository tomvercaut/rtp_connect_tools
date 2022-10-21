#include "rtp_connect_tools/analyser/ui/app_options_parser.h"

#include <boost/program_options.hpp>
#include <iostream>

namespace po = boost::program_options;

namespace rtp::connect::tools::analyser::ui {

auto Usage(const po::options_description& desc, const std::string& app_name)
    -> std::string {
  std::stringstream ss{""};
  ss << "Usage: ";
  ss << app_name;
  ss << " [options]\n";
  ss << desc;
  return ss.str();
}

void MissingRequiredArgument(const std::string& app_name,
                             const po::options_description& desc,
                             const std::string& argument) {
  std::cerr << "Required input argument missing: " << argument << "\n\n";
  const auto usage = Usage(desc, app_name);
  std::cerr << usage << std::endl;
  exit(1);
}

auto ParseAppOptions(const std::string& app_name, int argc, char** argv)
    -> AppOptions {
  po::options_description options{"Options"};
  options.add_options()("help,h", "Print application usage and help message")
      ( "input,i", po::value<std::string>(), "Directory to monitor for RTP files")
      ( "config,c", po::value<std::string>(), "Directory where the machine profiles are stored")
      ( "verbose,v", "Verbose output to a log file [default: only warning or more severe is "
      "reported. If enabled, trace level reporting is turned on.");

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, options), vm);
  po::notify(vm);
  if (vm.contains("help")) {
    const auto usage = Usage(options, app_name);
    std::cout << usage << std::endl;
    exit(0);
  }
  AppOptions ao{};
  if (vm.contains("input")) {
    ao.monitor_directory = vm["input"].as<std::string>();
  } else {
    ao.monitor_directory = "";
//    MissingRequiredArgument(app_name, options, "input");
  }
  if (vm.contains("config")) {
    ao.config_dir = vm["config"].as<std::string>();
  } else {
    MissingRequiredArgument(app_name, options, "config");
  }
  if (vm.contains("verbose")) {
    ao.verbose = true;
  } else {
    ao.verbose = false;
  }
  return ao;
}
}  // namespace rtp::connect::tools::analyser::ui
