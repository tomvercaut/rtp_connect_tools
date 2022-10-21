#ifndef RTP_CONNECT_TOOLS_UI_SRC_APP_CPP_APP_FRAME_H
#define RTP_CONNECT_TOOLS_UI_SRC_APP_CPP_APP_FRAME_H

#include <wx/wx.h>

#ifndef WX_PRECOMP
#include <wx/wxprec.h>
#endif

#include "rtp_connect_tools/analyser/ui/app.h"
#include "rtp_connect_tools/analyser/ui/controller.h"
#include "rtp_connect_tools/analyser/ui/default_controller.h"
#include "rtp_connect_tools/analyser/ui/view.h"

namespace rtp::connect::tools::analyser::ui {

///// Definitions

enum {
  ID_MONITOR_DIR = 1,
  ID_LISTBOX,
  ID_TEXT_CTRL_STATUS,
  ID_TEXT_CTRL_ERRORS
};

class AppFrame : public wxFrame, public AppView {
 public:
  explicit AppFrame(const wxString& title);
  ~AppFrame() override = default;

  void SetController(Controller* controller) override;
  void RemoveController() override;
  void UpdateData() override;

 private:
  Controller* controller_{nullptr};
  void OnMonitorMenuItem(wxCommandEvent& event);
  void OnAbout(wxCommandEvent& event);
  void OnListSelect(wxCommandEvent& event);
  /// Update the text of the menu item linked with monitoring of the RTP directory.
  void UpdateMonitorMenuItemText();

  wxListBox* lb_filenames_{nullptr};
  wxTextCtrl* tf_errors_{nullptr};
};

}  // namespace rtp::connect::tools::analyser::ui
#endif  // RTP_CONNECT_TOOLS_UI_SRC_APP_CPP_APP_FRAME_H
