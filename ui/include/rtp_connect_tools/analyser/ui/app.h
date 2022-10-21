#ifndef RTP_CONNECT_TOOLS_UI_INCLUDE_RTP_CONNECT_TOOLS_ANALYSER_UI_APP_H
#define RTP_CONNECT_TOOLS_UI_INCLUDE_RTP_CONNECT_TOOLS_ANALYSER_UI_APP_H

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <memory>

#include "rtp_connect_tools/analyser/ui/controller.h"
#include "rtp_connect_tools/analyser/ui/view.h"

namespace rtp::connect::tools::analyser::ui {
class App : public wxApp {
 public:
  auto OnInit() -> bool override;
  auto OnExit() -> int override;

 private:
  std::unique_ptr<Controller> controller_;
  auto defaultConfDir() -> std::filesystem::path;
};

}  // namespace rtp::connect::tools::analyser::ui

#endif  // RTP_CONNECT_TOOLS_UI_INCLUDE_RTP_CONNECT_TOOLS_ANALYSER_UI_APP_H
