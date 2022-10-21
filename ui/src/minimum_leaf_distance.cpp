#include "rtp_connect_tools/analyser/ui/minimum_leaf_distance.h"

#include <spdlog/fmt/bundled/format.h>

namespace rtp::connect::tools::analyser::ui {
auto MinimumLeafDistance::operator==(const MinimumLeafDistance& rhs) const
    -> bool {
  return leaf_a_ == rhs.leaf_a_ && leaf_b_ == rhs.leaf_b_ &&
         min_distance_ == rhs.min_distance_ &&
         control_point_number_ == rhs.control_point_number_ &&
         field_name_ == rhs.field_name_ && field_id_ == rhs.field_id_;
}
auto MinimumLeafDistance::operator!=(const MinimumLeafDistance& rhs) const
    -> bool {
  return !(rhs == *this);
}
[[maybe_unused]] auto MinimumLeafDistance::GetLeafA() const -> double {
  return leaf_a_;
}
[[maybe_unused]] void MinimumLeafDistance::SetLeafA(double value) {
  leaf_a_ = value;
}
[[maybe_unused]] auto MinimumLeafDistance::GetLeafB() const -> double {
  return leaf_b_;
}
[[maybe_unused]] void MinimumLeafDistance::SetLeafB(double value) {
  leaf_b_ = value;
}
[[maybe_unused]] auto MinimumLeafDistance::GetMinDistance() const -> double {
  return min_distance_;
}
[[maybe_unused]] void MinimumLeafDistance::SetMinDistance(double value) {
  min_distance_ = value;
}
[[maybe_unused]] auto MinimumLeafDistance::GetControlPointNumber() const
    -> uint32_t {
  return control_point_number_;
}
[[maybe_unused]] void MinimumLeafDistance::SetControlPointNumber(
    uint32_t value) {
  control_point_number_ = value;
}
[[maybe_unused]] auto MinimumLeafDistance::GetFieldName() const
    -> const std::string& {
  return field_name_;
}
[[maybe_unused]] void MinimumLeafDistance::SetFieldName(
    const std::string& value) {
  field_name_ = value;
}
[[maybe_unused]] auto MinimumLeafDistance::GetFieldId() const
    -> const std::string& {
  return field_id_;
}
[[maybe_unused]] void MinimumLeafDistance::SetFieldId(
    const std::string& value) {
  field_id_ = value;
}
}  // namespace rtp::connect::tools::analyser::ui

namespace std {
auto std::to_string(
    const rtp::connect::tools::analyser::ui::MinimumLeafDistance& mld)
    -> std::string {
  return fmt::format(
      "Field ID: {}\n"
      "Field name: {}\n"
      "Control point number: {}\n"
      "Leaf A: {}\n"
      "Leaf B: {}\n"
      "Leaf distance: {}\n"
      "Minimum allowed leaf distance: {}\n",
      mld.GetFieldId(), mld.GetFieldName(), mld.GetControlPointNumber(),
      mld.GetLeafA(), mld.GetLeafB(), mld.GetLeafA() - mld.GetLeafB(),
      mld.GetMinDistance());
}
}  // namespace std