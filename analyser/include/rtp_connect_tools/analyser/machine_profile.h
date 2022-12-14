#ifndef RTP_CONNECT_TOOLS_ANALYSER_MACHINE_PROFILE_H
#define RTP_CONNECT_TOOLS_ANALYSER_MACHINE_PROFILE_H

#include <string>
#include <vector>

namespace rtp::connect::tools::analyser {

/// Profile describing the characteristics of a machine.
class MachineProfile {
 public:
  /// Multi Leaf Collimator parameters
  class Mlc {
   public:
    uint16_t number_of_leaves{0};
    double min_leaf_distance{0.0};
  };
  std::string name;
  std::vector<std::string> name_aliases;
  Mlc mlc;
};

/// Read a machine profile
/// \param profile the resulting machine profile
/// \param filename name of the file
/// \return
///   - 0: OK
///   - >0: an error was detected
[[maybe_unused]] auto ReadMachineProfile(MachineProfile& profile, const std::string& filename)
    -> int;
/// Parse a machine profile.
///
/// \param profile the resulting machine profile
/// \param text text in TOML format
/// \return
///   - 0: OK
///   - >0: an error was detected
auto ParseMachineProfile(MachineProfile& profile, const std::string& text)
    -> int;
}  // namespace rtp::connect::tools::analyser

#endif  // RTP_CONNECT_TOOLS_ANALYSER_MACHINE_PROFILE_H
