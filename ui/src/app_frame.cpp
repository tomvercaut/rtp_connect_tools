#include "rtp_connect_tools/analyser/ui/app_frame.h"

#include <spdlog/spdlog.h>

#include <utility>

namespace rtp::connect::tools::analyser::ui {

AppFrame::AppFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {
  auto* menu_file = new wxMenu();

  menu_file->Append(ID_MONITOR_DIR, "&Monitor...\tCtrl+O",
                    "Monitor RTP directory.");
  menu_file->AppendSeparator();
  menu_file->Append(wxID_EXIT);

  auto* menu_help = new wxMenu();
  menu_help->Append(wxID_ABOUT);

  auto* menu_bar = new wxMenuBar();
  menu_bar->Append(menu_file, "&File");
  menu_bar->Append(menu_help, "&Help");

  SetMenuBar(menu_bar);
  CreateStatusBar();
  wxString status(title);
  status.append(" has been started");
  SetStatusText(status);

  // Main panel layout
  auto* panel = new wxPanel(this, wxID_ANY);

  auto* vbox = new wxBoxSizer(wxVERTICAL);
  auto* hbox1 = new wxBoxSizer(wxHORIZONTAL);

  lb_filenames_ =
      new wxListBox(panel, ID_LISTBOX, wxDefaultPosition, wxDefaultSize);

  auto* fgs = new wxFlexGridSizer(1, 2, 5, 5);
  auto* text_errors = new wxStaticText(panel, wxID_ANY, "Errors");
  tf_errors_ = new wxTextCtrl(panel, ID_TEXT_CTRL_ERRORS, "", wxDefaultPosition,
                              wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY);

  fgs->Add(text_errors);
  fgs->Add(tf_errors_, 0, wxEXPAND);
  fgs->AddGrowableCol(1, 1);
  fgs->AddGrowableRow(0, 1);

  hbox1->Add(lb_filenames_, 0, wxBOTTOM | wxEXPAND, 5);
  hbox1->Add(fgs, 1, wxALL | wxEXPAND, 5);
  vbox->Add(hbox1, 1, wxALL | wxEXPAND, 5);

  panel->SetSizer(vbox);

  // Bind events
  Bind(wxEVT_MENU, &AppFrame::OnMonitorMenuItem, this, ID_MONITOR_DIR);
  Bind(wxEVT_MENU, &AppFrame::OnAbout, this, wxID_ABOUT);
  Bind(
      wxEVT_MENU, [&](wxCommandEvent&) { Close(true); }, wxID_EXIT);
  Bind(wxEVT_LISTBOX, &AppFrame::OnListSelect, this, ID_LISTBOX);
  Centre();
}

void AppFrame::SetController(Controller* controller) {
  controller_ = controller;
}

void AppFrame::RemoveController() { controller_ = nullptr; }

void AppFrame::UpdateData() {
  SPDLOG_TRACE("Updating the view data");
  if (controller_ == nullptr) {
    SPDLOG_ERROR("Controller is a nullptr.");
    return;
  }
  if (lb_filenames_ == nullptr) {
    SPDLOG_ERROR("Listbox with filenames is a nullptr.");
    return;
  }
  wxString selection{};
  if (const auto id = lb_filenames_->GetSelection(); id != wxNOT_FOUND) {
    selection = lb_filenames_->GetString(id);
  }
  SPDLOG_TRACE("Current selection: {}", selection.ToStdWstring());
#if 1
  const auto filenames = controller_->GetFileNames();
  lb_filenames_->Clear();
  for (const auto& filename : filenames) {
    SPDLOG_TRACE(" filename: {}", filename);
    lb_filenames_->Append(wxString{filename});
  }
  const auto count = lb_filenames_->GetCount();
  bool trigger_event = true;
  if (selection.IsEmpty()) {
    if (lb_filenames_->GetCount() > 0) {
      lb_filenames_->SetSelection(0);
    }
  } else {
    for (int i{0}; i < count; ++i) {
      if (lb_filenames_->GetString(i) == selection) {
        lb_filenames_->SetSelection(i);
        trigger_event = false;
        break;
      }
    }
  }
  if(trigger_event) {
    SPDLOG_TRACE("Sending selection changed event");
    lb_filenames_->SendSelectionChangedEvent(wxEVT_LISTBOX);
  }
#endif
}

void AppFrame::OnMonitorMenuItem(wxCommandEvent& event) {
  if (controller_ == nullptr) {
    return;
  }
  if (!controller_->IsMonitoring()) {
    auto* dialog = new wxDirDialog(this, "Choose a directory");
    spdlog::trace("Showing \"Choose a directory\" dialog");
    auto response = dialog->ShowModal();
    if (response == wxID_OK) {
      spdlog::trace("Selected OK in the dialog");
      auto wide_str = dialog->GetPath().ToStdWstring();
      auto path = std::filesystem::path(wide_str);
      spdlog::trace("Controller::SetMonitoringPath entering");
      controller_->SetMonitoringPath(path);
      controller_->StartMonitor();
      spdlog::trace("Monitoring directory: " + path.string());
      // wait until the monitor is running to update the view (menu)
      // later in the function
      while (!controller_->IsMonitoring()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
      }
    } else if (response == wxID_CANCEL) {
      spdlog::trace("Selected Cancel in the dialog");
    } else {
      spdlog::trace("Unknown button selected");
    }
  } else {
    controller_->StopMonitor();
  }
  UpdateMonitorMenuItemText();
}

void AppFrame::OnListSelect(wxCommandEvent&) {
  SPDLOG_TRACE("List selection changed, updating text.");
  const wxString nl{"\n"};
  if (controller_ == nullptr || lb_filenames_ == nullptr ||
      tf_errors_ == nullptr) {
    return;
  }
  if (const auto i = lb_filenames_->GetSelection(); i == wxNOT_FOUND) {
    tf_errors_->SetLabelText("");
  } else {
    const auto filename = lb_filenames_->GetString(i);
    auto opt_model = controller_->GetModel(filename.ToStdWstring());
    if (!opt_model.has_value()) {
      tf_errors_->SetLabelText("");
      return;
    }
    const auto& model = opt_model.value();
    const auto& vfids = model.GetFieldIds();
    wxString text;
    for (const auto& field_id : vfids) {
      const auto cp_ids = model.GetControlPointNumbers(field_id);
      for (const auto cp_id : cp_ids) {
        if (const auto opt = model.MlcCount(field_id, cp_id); opt.has_value()) {
          const auto& value = opt.value();
          text.Append("MLC count:");
          text.Append(nl);
          text.Append(std::to_string(value));
          text.Append(nl);
          text.Append(nl);
        }
        if (const auto opt = model.MinimumLeafDistance(field_id, cp_id);
            opt.has_value()) {
          const auto& value = opt.value();
          text.Append("Minimum leaf distance:");
          text.Append(nl);
          text.Append(std::to_string(value));
          text.Append(nl);
          text.Append(nl);
        }
      }
    }
  }
}

void AppFrame::OnAbout(wxCommandEvent& event) {
  wxMessageBox("Well what about that ...", "About", wxOK | wxICON_INFORMATION);
}

void AppFrame::UpdateMonitorMenuItemText() {
  auto* menu_bar = GetMenuBar();
  if (menu_bar == nullptr) {
    return;
  }
  auto* menu_item = menu_bar->FindItem(ID_MONITOR_DIR);
  if (menu_item == nullptr) {
    spdlog::error("Menu item not found by ID [ID_MONITOR_DIR]");
    return;
  }
  const wxString default_text("&Monitor...\tCtrl+O");
  if (controller_ == nullptr) {
    menu_item->SetItemLabel(default_text);
    menu_item->SetHelp("Monitor RTP directory.");
  }
  if (!controller_->IsMonitoring()) {
    menu_item->SetItemLabel(default_text);
    menu_item->SetHelp("Monitor RTP directory.");
  } else {
    menu_item->SetItemLabel("&Stop monitor...\tCtrl+X");
    menu_item->SetHelp("Stop monitoring RTP directory.");
  }
}
}  // namespace rtp::connect::tools::analyser::ui
