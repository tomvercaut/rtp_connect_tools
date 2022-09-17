#include "rtp_connect_tools/analyser/analyse.h"

#include <spdlog/spdlog.h>

namespace rtp::connect::tools::analyser {

namespace core = rtp::connect::tools::core;

///
/// Find a matching machine profile by treatment machine name.
///
/// The name needs to match with either the treatment name in the profile or one
/// of the treatment machine aliases.
///
/// \param treatment_machine_name name o the treatment achine
/// \param profiles list of machine profiled
/// \return Non owning pointer to a machine profile. If no matching profile is
/// found, a nullptr is returned.
auto FindMachineProfile(const std::string& treatment_machine_name,
                        const std::vector<MachineProfile>& profiles)
    -> const MachineProfile*;

[[maybe_unused]] auto Analyse(const core::Rtp& rtp,
             const std::vector<MachineProfile>& profiles, Reporter& reporter)
    -> int32_t {
  const auto* profile =
      FindMachineProfile(rtp.site_setup.treatment_machine, profiles);
  if (profile == nullptr) {
    // no machine profile found ...
    spdlog::error(
        "Unable to find a matching profile for the treatment machine [{}]",
        rtp.site_setup.treatment_machine);
    return 1;
  }

  auto find_field_by_id =
      [&](const std::string& field_id) -> const core::Field& {
    for (const auto& field : rtp.fields) {
      if (field.field_id == field_id) return field;
    }
    throw std::invalid_argument(
        fmt::format("No matching field id found: {}", field_id));
  };

  constexpr double tolerance = 1e-7;
  // Tests
  int32_t rv{0};
  // Number of leaves and minimum leaf distance
  for (const auto& control_point : rtp.control_points) {
    const auto& field = find_field_by_id(control_point.field_id);
    const auto n_leaves = static_cast<std::size_t>(control_point.mlc_leaves);
    if (n_leaves != control_point.mlc_a.size() ||
        n_leaves != control_point.mlc_b.size()) {
      reporter.NumberOfLeaves(field, control_point);
      return 2;  // jump out otherwise the next loop will generate an
                 // out_of-range exception.
    }
    for (std::size_t i{0}; i < n_leaves; ++i) {
      const auto delta =
          std::fabs(control_point.mlc_a.at(i) - control_point.mlc_b.at(i));
      const auto error_delta = std::fabs(delta - profile->mlc.min_leaf_distance);
      if (delta < profile->mlc.min_leaf_distance && error_delta >= tolerance) {
        reporter.MinimumLeafDistance(field, control_point, i,
                                     profile->mlc.min_leaf_distance);
        rv = 3;
      }
    }
  }
  if (rv != 0) return rv;

  return 0;
}

auto FindMachineProfile(const std::string& treatment_machine_name,
                        const std::vector<MachineProfile>& profiles)
    -> const MachineProfile* {
  for (const auto& p : profiles) {
    if (p.name == treatment_machine_name) {
      return &p;
    }
    const auto itr = std::find_if(
        p.name_aliases.cbegin(), p.name_aliases.cend(),
        [&](const auto& name) { return name == treatment_machine_name; });
    if (itr != p.name_aliases.cend()) {
      return &p;
    }
  }
  return nullptr;
}

}  // namespace rtp::connect::tools::analyser