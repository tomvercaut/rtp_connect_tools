#ifndef RTP_CONNECT_TOOLS_UI_INCLUDE_RTP_CONNECT_TOOLS_ANALYSER_UI_MLC_COUNT_H
#define RTP_CONNECT_TOOLS_UI_INCLUDE_RTP_CONNECT_TOOLS_ANALYSER_UI_MLC_COUNT_H

#include <filesystem>
#include <string>
#include <vector>

namespace rtp::connect::tools::analyser::ui {

/// Models the number of effective and expected leaves in an MLC for a given
/// treatment field.
class MlcCount {
 public:
  auto operator==(const MlcCount& rhs) const -> bool;
  auto operator!=(const MlcCount& rhs) const -> bool;

  /// Get the effective number of leaves.
  /// \return effective number of leaves
  [[maybe_unused]] [[nodiscard]] auto GetValue() const -> uint32_t;
  /// Set the effective number of leaves.
  /// \param value effective number of leaves
  [[maybe_unused]] void SetValue(uint32_t value);
  /// Get the expected number of leaves.
  /// \return expected number of leaves
  [[maybe_unused]] [[nodiscard]] auto GetExpected() const -> uint32_t;
  /// Set the expected number of leaves.
  /// \param expected expected number of leaves
  [[maybe_unused]] void SetExpected(uint32_t expected);
  /// Get the control point number for which the MLC count was determined.
  /// \return matching control point number
  [[maybe_unused]] [[nodiscard]] auto GetControlPointNumber() const -> uint32_t;
  /// Set the control point number for which the MLC count was determined.
  /// \param control_point_number matching control point number
  [[maybe_unused]] void SetControlPointNumber(uint32_t control_point_number);
  /// Get a reference to the name of the field.
  /// \return field name
  [[maybe_unused]] [[nodiscard]] auto GetFieldName() const
      -> const std::string&;
  /// Set the name of the matching field.
  /// \param field_name name of the field
  [[maybe_unused]] void SetFieldName(const std::string& field_name);
  /// Get a reference to the unique identifier of the field.
  /// \return unique identifier of the field
  [[maybe_unused]] [[nodiscard]] auto GetFieldId() const -> const std::string&;
  /// Set the unique field identifier.
  /// \param field_id unique field identifier
  [[maybe_unused]] void SetFieldId(const std::string& field_id);

 private:
  // Effective number of leaves.
  uint32_t value_{0};
  // Expected number of leaves
  uint32_t expected_{0};
  // Control point number
  uint32_t control_point_number_{0};
  // Name of the field
  std::string field_name_;
  // Unique identifier of the field
  std::string field_id_;
};

}  // namespace rtp::connect::tools::analyser::ui

namespace std {
auto to_string(
    const rtp::connect::tools::analyser::ui::MlcCount& mlc_count) -> std::string;
}  // namespace std
#endif  // RTP_CONNECT_TOOLS_UI_INCLUDE_RTP_CONNECT_TOOLS_ANALYSER_UI_MLC_COUNT_H
