#include "rtp_connect_tools/analyser/ui/mlc_count.h"

#include <spdlog/fmt/bundled/format.h>

namespace rtp::connect::tools::analyser::ui {
auto MlcCount::operator==(const MlcCount& rhs) const -> bool {
  return value_ == rhs.value_ && expected_ == rhs.expected_ &&
         control_point_number_ == rhs.control_point_number_ &&
         field_name_ == rhs.field_name_ && field_id_ == rhs.field_id_;
}
auto MlcCount::operator!=(const MlcCount& rhs) const -> bool {
  return !(rhs == *this);
}
[[maybe_unused]] auto MlcCount::GetValue() const -> uint32_t { return value_; }
[[maybe_unused]] void MlcCount::SetValue(uint32_t value) { value_ = value; }
[[maybe_unused]] auto MlcCount::GetExpected() const -> uint32_t {
  return expected_;
}
[[maybe_unused]] void MlcCount::SetExpected(uint32_t expected) {
  expected_ = expected;
}
[[maybe_unused]] auto MlcCount::GetControlPointNumber() const -> uint32_t {
  return control_point_number_;
}
[[maybe_unused]] void MlcCount::SetControlPointNumber(
    uint32_t control_point_number) {
  control_point_number_ = control_point_number;
}
[[maybe_unused]] auto MlcCount::GetFieldName() const -> const std::string& {
  return field_name_;
}
[[maybe_unused]] void MlcCount::SetFieldName(const std::string& field_name) {
  field_name_ = field_name;
}
[[maybe_unused]] auto MlcCount::GetFieldId() const -> const std::string& {
  return field_id_;
}
[[maybe_unused]] void MlcCount::SetFieldId(const std::string& field_id) {
  field_id_ = field_id;
}
}  // namespace rtp::connect::tools::analyser::ui

namespace std {
auto std::to_string(
    const rtp::connect::tools::analyser::ui::MlcCount& mlc_count) -> std::string {
  return fmt::format(
      "Field ID: {}\n"
      "Field name: {}\n"
      "Control point number: {}\n"
      "Number of leaves: {}\n"
      "Expected number of leaves: {}",
      mlc_count.GetFieldId(), mlc_count.GetFieldName(),
      mlc_count.GetControlPointNumber(), mlc_count.GetValue(),
      mlc_count.GetExpected());
}
}  // namespace std
