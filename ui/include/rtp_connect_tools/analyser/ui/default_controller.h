#ifndef RTP_CONNECT_TOOLS_UI_INCLUDE_RTP_CONNECT_TOOLS_ANALYSER_UI_DEFAULT_CONTROLLER_H
#define RTP_CONNECT_TOOLS_UI_INCLUDE_RTP_CONNECT_TOOLS_ANALYSER_UI_DEFAULT_CONTROLLER_H

#include <future>
#include <optional>
#include <condition_variable>

#include "model_view.h"
#include "rtp_connect_tools/analyser/machine_profile.h"
#include "rtp_connect_tools/analyser/ui/controller.h"
#include "rtp_connect_tools/analyser/ui/view.h"

namespace rtp::connect::tools::analyser::ui {
class [[maybe_unused]] DefaultController : public Controller {
 public:
  DefaultController() = default;
  DefaultController(const DefaultController&) = delete;
  DefaultController(DefaultController&&) = delete;
  ~DefaultController() override;
  auto operator=(const DefaultController&) -> DefaultController& = delete;
  auto operator=(DefaultController&&) -> DefaultController& = delete;

  void SetView(AppView* view) override;
  void DetachView() override;

  /// Set the directory path to monitor.
  ///
  /// Calling the function starts an asynchronous monitor thread.
  ///
  /// \param path directory path
  void SetMonitoringPath(const std::filesystem::path& path) override;

  [[nodiscard]] auto GetMonitorPath() const
      -> std::optional<std::filesystem::path> override;

  [[nodiscard]] auto IsMonitoring() const -> bool override;

  void StartMonitor() override;

  void StopMonitor() override;

  void SetConfigurationPath(const std::filesystem::path& config_path) override;

  void LoadConfiguration() override;

  void Update(std::map<std::filesystem::path, ModelView> data) override;

  [[nodiscard]] auto GetFileNames() -> std::vector<std::wstring> override;

  [[nodiscard]] auto GetModel(const std::wstring& filename) -> std::optional<ModelView> override;

  void Notify();

  [[nodiscard]] auto HasDataChanged() const -> bool;
  [[nodiscard]] auto View() -> AppView*;

 private:
  /// Start monitoring a directory in a separate thread.
  void StartMonitorThread();
  /// Stop the monitoring in a separate thread.
  void StopMonitorThread();

  // Start the thread for updating the view
  void StartUpdateViewThread();
  void StopUpdateViewThread();

  AppView* view_{nullptr};

  std::optional<std::filesystem::path> config_path_{};
  std::optional<std::filesystem::path> monitor_path_{};
  std::jthread monitor_thread_{};
  std::jthread update_view_thread_{};
  std::condition_variable update_view_cv_{};
  std::vector<std::filesystem::path> files_{};
  std::vector<rtp::connect::tools::analyser::MachineProfile> machine_profiles_{};
  std::unordered_map<std::wstring, ModelView> data_{};
  std::mutex data_mtx_{};
  bool data_changed_{false};
};
}  // namespace rtp::connect::tools::analyser::ui

#endif  // RTP_CONNECT_TOOLS_UI_INCLUDE_RTP_CONNECT_TOOLS_ANALYSER_UI_DEFAULT_CONTROLLER_H
