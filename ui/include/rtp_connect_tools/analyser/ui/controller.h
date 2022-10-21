#ifndef RTP_CONNECT_TOOLS_UI_INCLUDE_RTP_CONNECT_TOOLS_ANALYSER_UI_CONTROLLER_H
#define RTP_CONNECT_TOOLS_UI_INCLUDE_RTP_CONNECT_TOOLS_ANALYSER_UI_CONTROLLER_H

#include <filesystem>
#include <map>

#include "rtp_connect_tools/analyser/ui/model_view.h"

namespace rtp::connect::tools::analyser::ui {

// Avoid circular dependency
class AppView;

class Controller {
 public:
  virtual ~Controller() = default;

  virtual void SetView(AppView* view) = 0;
  virtual void DetachView() = 0;

  /// Set the directory path on the filesystem to monitor.
  ///
  /// Calling the function stops a running monitor prior to setting the
  /// directory path.
  ///
  /// \param path filesytem directory path
  [[maybe_unused]] virtual void SetMonitoringPath(
      const std::filesystem::path& path) = 0;

  /// Get the directory path that will be monitored.
  /// \return Directory being monitored. If not set, a std::nullopt_t is
  /// returned.
  [[maybe_unused]] [[nodiscard]] virtual auto GetMonitorPath() const
      -> std::optional<std::filesystem::path> = 0;

  /// Check if the controller is monitoring a filesystem.
  ///
  /// \return True if the controller is monitoring a filesystem path.
  [[maybe_unused]] [[nodiscard]] virtual auto IsMonitoring() const -> bool = 0;

  /// Start monitoring the filesystem.
  ///
  /// If a monitor is currently running, it's stopped prior to starting the new
  /// monitor.
  [[maybe_unused]] virtual void StartMonitor() = 0;

  /// Stop monitoring the filesystem.
  [[maybe_unused]] virtual void StopMonitor() = 0;

  /// Set the configuration path which contains configuration data.
  ///
  /// The implementation should also call LoadConfiguration to keep the internal
  /// state valid. \param config_path filesystem path to the configuration
  /// directory
  [[maybe_unused]] virtual void SetConfigurationPath(
      const std::filesystem::path& config_path) = 0;

  /// Load the configuration data.
  [[maybe_unused]] virtual void LoadConfiguration() = 0;

  /// Update the internal view of the model.
  ///
  /// \param data map of the filesystem path and the model linked to that path
  [[maybe_unused]] virtual void Update(std::map<std::filesystem::path, ModelView> data) = 0;

  /// Get a list of all RTP files stored in the controller.
  ///
  /// Implementation must be thread safe.
  [[maybe_unused]] [[nodiscard]] virtual auto GetFileNames() -> std::vector<std::wstring> = 0;

  /// Get the view of the model by the filesystem path.
  ///
  /// Implementation must be thread safe.
  [[maybe_unused]] [[nodiscard]] virtual auto GetModel(const std::wstring& filename) -> std::optional<ModelView> = 0;
};
}  // namespace rtp::connect::tools::analyser::ui

#endif  // RTP_CONNECT_TOOLS_UI_INCLUDE_RTP_CONNECT_TOOLS_ANALYSER_UI_CONTROLLER_H
