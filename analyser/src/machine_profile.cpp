#include "rtp_connect_tools/analyser/machine_profile.h"

#include <spdlog/spdlog.h>
#include <toml++/toml.h>

namespace rtp::connect::tools::analyser {
auto InternalParseMachineProfile(MachineProfile& profile, toml::table& config)
    -> int {
  if (config["general"].type() != toml::node_type::table) {
    spdlog::error("general section missing from TOML configuration.");
    return 2;
  }
  auto general = config["general"];
  if (!general["name"]) {
    spdlog::error("name property is missing in the general section.");
    return 3;
  }
  // Get the name of the machine
  profile.name = general["name"].value<std::string>().value_or("");
  if (profile.name.empty()) {
    spdlog::error("name property is empty in the general section.");
    return 4;
  }
  if (toml::array* arr = general["name_aliases"].as_array(); arr != nullptr) {
    arr->for_each([&](auto&& el) {
      if constexpr ((toml::is_string<decltype(el)>)) {
        std::string alias = *el;
        profile.name_aliases.push_back(alias);
      }
    });
  }

  // Get the MLC parameters
  if (config["mlc"].type() != toml::node_type::table) {
    spdlog::error("mlc section missing from TOML configuration.");
    return 5;
  }
  auto mlc = config["mlc"];
  profile.mlc.number_of_leaves =
      mlc["number_of_leaves"].as_integer()->value_or(0);
  profile.mlc.min_leaf_distance =
      mlc["min_leaf_distance"].as_floating_point()->value_or(
          std::numeric_limits<double>::max());
  return 0;
}

[[maybe_unused]] auto ReadMachineProfile(MachineProfile& profile, const std::string& filename)
    -> int {
  toml::table config;
  try {
    config = toml::parse_file(filename);
  } catch (const toml::parse_error& err) {
    spdlog::error("Error while parsing TOML file: {}\n{}", filename,
                  err.what());
    return 1;
  }
  return InternalParseMachineProfile(profile, config);
}

auto ParseMachineProfile(MachineProfile& profile, const std::string& text)
    -> int {
  toml::table config;
  try {
    config = toml::parse(text);
  } catch (const toml::parse_error& err) {
    spdlog::error("Error while parsing TOML text: {}\n{}", text, err.what());
    return 1;
  }
  return InternalParseMachineProfile(profile, config);
}

}  // namespace rtp::connect::tools::analyser