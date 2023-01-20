#include <catch2/catch_test_macros.hpp>

#include <rtp_connect_tools/core/string/split.h>

#include <string>
#include <string_view>

namespace str = rtp::connect::tools::core::string;

TEST_CASE("SplitEmpty") {
  const std::string_view s{""};
  const std::string_view delim{" "};

  const auto vec = str::Split(s, delim);
  REQUIRE(vec.size() == 1);
  auto check = std::string_view{} == vec[0];
  REQUIRE(check);
}

TEST_CASE("SplitNoMatchDelim") {
  const std::string_view s{"abc"};
  const std::string_view delim{" "};

  const auto vec = str::Split(s, delim);
  REQUIRE(vec.size() == 1);
  auto check = std::string_view{"abc"} == vec[0];
  REQUIRE(check);
}

TEST_CASE("SplitOneMatchDelim") {
  const std::string_view s{"abc def"};
  const std::string_view delim{" "};

  const auto vec = str::Split(s, delim);
  REQUIRE(vec.size() == 2);
  auto check = std::string_view{"abc"} == vec[0];
  REQUIRE(check);
  check = std::string_view{"def"} == vec[1];
  REQUIRE(check);
}

TEST_CASE("SplitTwoMatchDelim") {
  const std::string_view s{"abc def ghi"};
  const std::string_view delim{" "};

  const auto vec = str::Split(s, delim);
  REQUIRE(vec.size() == 3);
  auto check = std::string_view{"abc"} == vec[0];
  REQUIRE(check);
  check = std::string_view{"def"} == vec[1];
  REQUIRE(check);
  check = std::string_view{"ghi"} == vec[2];
  REQUIRE(check);
}


TEST_CASE("SplitStringOneMatchDelim") {
  const std::string s{"abc def"};
  const std::string delim{" "};

  const auto vec = str::Split(s, delim);
  REQUIRE(vec.size() == 2);
  auto check = std::string_view{"abc"} == vec[0];
  REQUIRE(check);
  check = std::string_view{"def"} == vec[1];
  REQUIRE(check);
}

TEST_CASE("SplitPrefixSuffix") {
  const std::string s{" abc "};
  const std::string delim{" "};

  const auto vec = str::Split(s, delim);
  REQUIRE(vec.size() == 3);
  auto check = std::string_view{""} == vec[0];
  REQUIRE(check);
  check = std::string_view{"abc"} == vec[1];
  REQUIRE(check);
  check = std::string_view{""} == vec[2];
  REQUIRE(check);
}
