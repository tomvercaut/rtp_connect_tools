#include <catch2/catch_test_macros.hpp>
#include "rtp_connect_tools/analyser/machine_profile.h"

namespace analyser = rtp::connect::tools::analyser;

TEST_CASE("ParseMachineProfile") {
  static constexpr auto  text=R"(
[general]
name = "Machine Name"
name_aliases = ["alias1", "alias2"]

[mlc]
number_of_leaves = 40
min_leaf_distance = 0.5
)";
  analyser::MachineProfile profile;
  REQUIRE(analyser::ParseMachineProfile(profile, text) == 0);
  REQUIRE("Machine Name" == profile.name);
  REQUIRE(2 == profile.name_aliases.size());
  REQUIRE("alias1" == profile.name_aliases[0]);
  REQUIRE("alias2" == profile.name_aliases[1]);
  REQUIRE(40 == profile.mlc.number_of_leaves);
  REQUIRE(0.5 == profile.mlc.min_leaf_distance);
}