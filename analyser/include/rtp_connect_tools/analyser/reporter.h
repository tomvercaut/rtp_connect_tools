#ifndef RTP_CONNECT_TOOLS_ANALYSER_REPORTER_H
#define RTP_CONNECT_TOOLS_ANALYSER_REPORTER_H

#include "rtp_connect_tools/core/rtp.h"

namespace rtp::connect::tools::analyser {

class Reporter {
 public:
  Reporter() = default;
  Reporter(const Reporter&) = default;
  Reporter(Reporter&&) = default;
  auto operator=(const Reporter&) -> Reporter& = default;
  auto operator=(Reporter&&) -> Reporter& = default;
  virtual ~Reporter() = default;
  ///
  /// Report the number of leaves in a multi-leaf collimator, both the expected and effective number.
  /// \param field field definition
  /// \param control_point control point definition
  ///
  [[maybe_unused]] virtual void NumberOfLeaves(
      const rtp::connect::tools::core::Field& field, const rtp::connect::tools::core::ControlPoint& control_point) = 0;
  ///
  /// Report the minimum distance between two leaves in a multi-leaf collimator, both the expected and the effective value_.
  /// \param field_index index to the field
  /// \param control_point_index index to the control point in the field
  /// \param leaf_index index to the leaf pair in the multi-leaf collimator
  /// \param min_distance minimum expected distance (unit equal to the reported position of the leaves)
  ///
  [[maybe_unused]] virtual void MinimumLeafDistance(
      const rtp::connect::tools::core::Field& field, const rtp::connect::tools::core::ControlPoint& control_point,
      std::size_t leaf_index, double min_distance) = 0;
};

}  // namespace rtp::connect::tools::analyser

#endif  // RTP_CONNECT_TOOLS_ANALYSER_REPORTER_H
