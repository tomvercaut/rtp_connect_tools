#include "rtp_connect_tools/analyser/ui/default_controller.h"

#include <spdlog/spdlog.h>

#include <chrono>
#include <experimental/map>
#include <filesystem>

#include "rtp_connect_tools/analyser/analyse.h"
#include "rtp_connect_tools/analyser/ui/model_view_reporter.h"
#include "rtp_connect_tools/core/parser.h"
#include "rtp_connect_tools/core/rtp.h"

namespace rtp::connect::tools::analyser::ui {

void monitor_directory_path(std::stop_token token,
                            const std::filesystem::path monitor_path,
                            const std::vector<MachineProfile> machine_profiles,
                            DefaultController* controller,
                            std::size_t timeout_ms);

void update_view(std::stop_token token, DefaultController* controller);

DefaultController::~DefaultController() {
  view_ = nullptr;  // Shouldn't call DetachView because it's a virtual function
  // Stop the monitoring thread (if running)
  StopMonitorThread();
}

void DefaultController::SetView(AppView* view) {
  DetachView();
  view_ = view;
}

void DefaultController::DetachView() { view_ = nullptr; }

void DefaultController::SetMonitoringPath(const std::filesystem::path& path) {
  StopMonitor();
  monitor_path_ = {path};
  if (monitor_path_.has_value()) {
    spdlog::info("Monitoring: {}", monitor_path_.value().string());
  } else {
    spdlog::warn("No monitoring path set.");
  }
}

auto DefaultController::GetMonitorPath() const
    -> std::optional<std::filesystem::path> {
  return monitor_path_;
}

auto DefaultController::IsMonitoring() const -> bool {
  return monitor_thread_.joinable();
}

void DefaultController::StartMonitor() {
  StopMonitor();
  StartUpdateViewThread();
  StartMonitorThread();
}

void DefaultController::StopMonitor() {
  SPDLOG_DEBUG("StopMonitor called");
  StopMonitorThread();
  StopUpdateViewThread();
  SPDLOG_DEBUG("StopMonitor finished");
}

void DefaultController::SetConfigurationPath(
    const std::filesystem::path& config_path) {
  config_path_.reset();
  machine_profiles_.clear();
  spdlog::trace("Setting the configuration path.");
  config_path_ = std::optional<std::filesystem::path>{config_path};
  LoadConfiguration();
}

void DefaultController::LoadConfiguration() {
  spdlog::trace("Loading the configuration.");
  if (!config_path_.has_value()) {
    spdlog::warn(
        "Unable to load configuration because the configuration path has not "
        "been set.");
  }
  machine_profiles_ = ListMachineProfiles(config_path_.value(), "machine_");
}

void DefaultController::Update(
    std::map<std::filesystem::path, ModelView> data) {
  SPDLOG_DEBUG("Updating the model view data");
  {
    const std::lock_guard<std::mutex> lock(data_mtx_);
    data_.clear();
    for (const auto& [key, value] : data) {
      const auto filename = key.filename().wstring();
      data_.insert({filename, value});
    }
    data_changed_ = true;
  }
  Notify();
}

auto DefaultController::GetFileNames() -> std::vector<std::wstring> {
  std::vector<std::wstring> vec;
  {
    const std::lock_guard<std::mutex> lock(data_mtx_);
    for (auto it = data_.cbegin(); it != data_.cend(); it++) {
      vec.push_back(it->first);
    }
  }
  return vec;
}

auto DefaultController::GetModel(const std::wstring& filename)
    -> std::optional<ModelView> {
  const std::lock_guard<std::mutex> lock(data_mtx_);
  if (data_.contains(filename)) {
    return {data_.at(filename)};
  }
  return {};
}

void DefaultController::StartMonitorThread() {
  monitor_thread_ =
      std::move(std::jthread(monitor_directory_path, monitor_path_.value(),
                             machine_profiles_, this, 1000));
}

void DefaultController::StopMonitorThread() {
  if (!monitor_thread_.joinable()) {
    return;
  }
  spdlog::debug("Stopping monitoring thread ...");
  monitor_thread_.request_stop();
  monitor_thread_.join();
  spdlog::debug("Monitoring thread stopped");
}

void DefaultController::StartUpdateViewThread() {
  spdlog::debug("Starting the update view thread");
  update_view_thread_ = std::move(std::jthread(update_view, this));
  spdlog::debug("Started the update view thread");
}

void DefaultController::StopUpdateViewThread() {
  if (!update_view_thread_.joinable()) {
    return;
  }
  spdlog::debug("Stopping the update view thread");
  auto done = update_view_thread_.request_stop();
  while (!done) {
    done = update_view_thread_.request_stop();
  }
  spdlog::trace("update_view_thread_.request_stop(): {} |--| {}", update_view_thread_.request_stop(), done);
//  spdlog::debug("Notifying the update_view_cv_ condition_variable");
//  update_view_cv_.notify_all();
//  spdlog::debug(
//      "Notified the update_view_cv_ condition_variable and waiting for the "
//      "join of the update_view_thread_");
  update_view_thread_.join();
  spdlog::debug("Update view thread stopped");
}

auto list_rtp_files(const std::filesystem::path& path)
    -> std::vector<std::filesystem::path> {
  namespace fs = std::filesystem;
  std::vector<fs::path> files;
  const fs::path expected_extension{".RTP"};
  const fs::directory_iterator dir_iter{path};
  std::ranges::for_each(dir_iter, [&](const fs::directory_entry& entry) {
    if (!entry.is_regular_file()) {
      return;
    }
    const auto& path = entry.path();
    if (!path.has_extension() || !path.has_filename()) {
      return;
    }
    const auto& extension = path.extension();
    if (expected_extension == extension) {
      files.push_back(path);
    }
  });
  return files;
}

void DefaultController::Notify() { update_view_cv_.notify_all(); }

auto DefaultController::HasDataChanged() const -> bool {
  return data_changed_;
}

auto DefaultController::View() -> AppView* {
  return view_;
}

void monitor_directory_path(std::stop_token token,
                            const std::filesystem::path monitor_path,
                            const std::vector<MachineProfile> machine_profiles,
                            DefaultController* controller,
                            std::size_t timeout_ms) {
  namespace core = rtp::connect::tools::core;
  namespace an = rtp::connect::tools::analyser;
  ModelViewReporter reporter;
  std::map<std::filesystem::path, ModelView> data;
  while (!token.stop_requested()) {
    spdlog::trace("Monitoring: {}", monitor_path.string());
    auto tmp_files = list_rtp_files(monitor_path);
    for (const auto& path : tmp_files) {
      try {
        const auto rtp = core::ParseRtpFile(path.string());
        reporter.Clear();
        an::Analyse(rtp, machine_profiles, reporter);
        data.insert({path, reporter.Data()});
      } catch (const std::exception& e) {
        spdlog::error("{}", e.what());
      }
    }
    controller->Update(data);
    // Need to update the controller but this has to happen in a separate
    // thread. Otherwise the whole chain of function calls in the controller
    // will be linked to the monitor thread.
    //    try {
    //      std::thread t([=]() {
    //        SPDLOG_TRACE(
    //            "Launching a separate detached thread to update the
    //            controller.");
    //        try {
    //          controller->Update(data);
    //        } catch (std::exception& e) {
    //          SPDLOG_ERROR("Exception caught while updating the controller:
    //          {}",
    //                       e.what());
    //        }
    //      });
    //      t.detach();
    //    } catch (std::exception& ex) {
    //      SPDLOG_ERROR("Exception caught while launching a detached thread:
    //      {}",
    //                   ex.what());
    //    }
    std::this_thread::sleep_for(std::chrono::milliseconds(timeout_ms));
  }
  spdlog::trace("Stopping the RTP monitor");
}

void update_view(std::stop_token token, DefaultController* controller) {
  spdlog::trace("update_view function starts");
  while(!token.stop_requested()) {
    if (controller->HasDataChanged() && controller->View() != nullptr) {
      controller->View()->UpdateData();
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }
  spdlog::trace("update_view function ends");
}

}  // namespace rtp::connect::tools::analyser::ui
