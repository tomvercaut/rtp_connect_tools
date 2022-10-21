#ifndef RTP_CONNECT_TOOLS_UI_INCLUDE_RTP_CONNECT_TOOLS_ANALYSER_UI_MINIMUM_LEAF_DISTANCE_H
#define RTP_CONNECT_TOOLS_UI_INCLUDE_RTP_CONNECT_TOOLS_ANALYSER_UI_MINIMUM_LEAF_DISTANCE_H

#include <filesystem>
#include <string>
#include <vector>

namespace rtp::connect::tools::analyser::ui {

/// Models the leaf positions and the minimum distance between two opposing
/// leaves in a control point of a treatment field.
class MinimumLeafDistance {
 public:
  auto operator==(const MinimumLeafDistance& rhs) const -> bool;
  auto operator!=(const MinimumLeafDistance& rhs) const -> bool;

  /// Get the position of leaf A.
  /// \return leaf A position
  [[maybe_unused]] [[nodiscard]] auto GetLeafA() const -> double;
  /// Set the position of leaf A.
  /// \param value position of leaf A
  [[maybe_unused]] void SetLeafA(double value);
  /// Get the position of leaf B.
  /// \return leaf B position
  [[maybe_unused]] [[nodiscard]] auto GetLeafB() const -> double;
  /// Set the position of leaf B.
  /// \param value position of leaf B
  [[maybe_unused]] void SetLeafB(double value);
  /// Get the minimum distance between two opposing leaves.
  /// \return Minimum distance between two opposing leaves
  [[maybe_unused]] [[nodiscard]] auto GetMinDistance() const -> double;
  /// Set the minimum distance between two opposing leaves.
  /// \param value minimum distance between two opposing leaves
  [[maybe_unused]] void SetMinDistance(double value);
  /// Get the control point number for which the minimum field distance was
  /// defined.. \return control point number
  [[maybe_unused]] [[nodiscard]] auto GetControlPointNumber() const -> uint32_t;
  /// Set the control point number.
  /// \param value control point number
  [[maybe_unused]] void SetControlPointNumber(uint32_t value);
  /// Get a reference to the name of the field.
  /// \return field name
  [[maybe_unused]] [[nodiscard]] auto GetFieldName() const
      -> const std::string&;
  /// Set the name of the matching field.
  /// \param field_name name of the field
  [[maybe_unused]] void SetFieldName(const std::string& value);
  /// Get a reference to the unique identifier of the field.
  /// \return unique identifier of the field
  [[maybe_unused]] [[nodiscard]] auto GetFieldId() const -> const std::string&;
  /// Set the unique field identifier.
  /// \param field_id unique field identifier
  [[maybe_unused]] void SetFieldId(const std::string& value);

 private:
  // Position of leaf A
  double leaf_a_{0.0};
  // Position of leaf B
  double leaf_b_{0.0};
  // Minimum distance between two opposing leaves
  double min_distance_{0.0};
  // Control point number
  uint32_t control_point_number_{0};
  // Name of the field
  std::string field_name_{};
  // Unique identifier of the field
  std::string field_id_{};
};

}  // namespace rtp::connect::tools::analyser::ui

namespace std {
auto to_string(
    const rtp::connect::tools::analyser::ui::MinimumLeafDistance& mld)
    -> std::string;
} // namespace std
#endif  // RTP_CONNECT_TOOLS_UI_INCLUDE_RTP_CONNECT_TOOLS_ANALYSER_UI_MINIMUM_LEAF_DISTANCE_H
