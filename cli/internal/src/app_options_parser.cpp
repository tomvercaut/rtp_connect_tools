#include "app_options_parser.h"

#include <boost/program_options.hpp>
#include <iostream>


namespace po = boost::program_options;

namespace rtp::connect::tools::analyser::cli {

auto Usage(const po::options_description& desc, const std::string& app_name) -> std::string {
  std::stringstream ss{""};
  ss << "Usage: ";
  ss << app_name;
  ss << " [options]\n";
  ss << desc;
  return ss.str();
}

void MissingRequiredArgument(const std::string& app_name, const po::options_description& desc,
                             const std::string& argument) {
  std::cerr << "Required input argument missing: " << argument << "\n\n";
  const auto usage = Usage(desc, app_name);
  std::cerr << usage << std::endl;
  exit(1);
}

auto ParseAppOptions(const std::string& app_name, int argc, char** argv) -> AppOptions {
  po::options_description options{"Options"};
  options.add_options()("help,h", "Print application usage and help message")(
      "input,i", po::value<std::string>(), "RTP input file")(
      "output,o", po::value<std::string>(), "output file")(
      "data-dir", po::value<std::string>(),
      "data directory in which the machine profiles are stored");

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
    ao.input_file = vm["input"].as<std::string>();
  } else {
    MissingRequiredArgument(app_name, options, "input");
  }
  if (vm.contains("output")) {
    ao.output_file = vm["output"].as<std::string>();
  } else {
    MissingRequiredArgument(app_name, options, "output");
  }
  if (vm.contains("data-dir")) {
    ao.data_directory = vm["data-dir"].as<std::string>();
  }
  return ao;
}
}  // namespace rtp::connect::tools::analyser::cli
