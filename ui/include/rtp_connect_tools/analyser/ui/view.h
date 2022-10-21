#ifndef RTP_CONNECT_TOOLS_UI_INCLUDE_RTP_CONNECT_TOOLS_ANALYSER_UI_VIEW_H
#define RTP_CONNECT_TOOLS_UI_INCLUDE_RTP_CONNECT_TOOLS_ANALYSER_UI_VIEW_H

#include <memory>

#include "rtp_connect_tools/analyser/ui/controller.h"

namespace rtp::connect::tools::analyser::ui {
class AppView {
 public:
  virtual ~AppView() = default;
  virtual void SetController(Controller* controller) = 0;
  virtual void RemoveController() = 0;
  virtual void UpdateData() = 0;
};
}  // namespace rtp::connect::tools::analyser::ui

#endif  // RTP_CONNECT_TOOLS_UI_INCLUDE_RTP_CONNECT_TOOLS_ANALYSER_UI_VIEW_H
