#ifndef RTP_CONNECT_TOOLS_UI_INCLUDE_RTP_CONNECT_TOOLS_ANALYSER_UI_MODEL_VIEW_REPORTER_H
#define RTP_CONNECT_TOOLS_UI_INCLUDE_RTP_CONNECT_TOOLS_ANALYSER_UI_MODEL_VIEW_REPORTER_H

#include <vector>

#include "rtp_connect_tools/analyser/reporter.h"
#include "rtp_connect_tools/analyser/ui/model_view.h"
#include "rtp_connect_tools/core/rtp.h"

namespace rtp::connect::tools::analyser::ui {

class [[maybe_unused]] ModelViewReporter : public Reporter {
 public:
  void NumberOfLeaves(const core::Field& field,
                      const core::ControlPoint& control_point) override;
  void MinimumLeafDistance(const core::Field& field,
                           const core::ControlPoint& control_point,
                           std::size_t leaf_index,
                           double min_distance) override;

  [[maybe_unused]] void Clear();
  [[maybe_unused]] auto Data() -> ModelView&;
  [[maybe_unused]] [[nodiscard]] auto Data() const -> const ModelView&;

 private:
  ModelView model_;
};

}  // namespace rtp::connect::tools::analyser::ui
#endif  // RTP_CONNECT_TOOLS_UI_INCLUDE_RTP_CONNECT_TOOLS_ANALYSER_UI_MODEL_VIEW_REPORTER_H
