#include "rtp_connect_tools/analyser/ui/app.h"

#include <spdlog/pattern_formatter.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/spdlog.h>

#include "rtp_connect_tools/analyser/ui/app_frame.h"
#include "rtp_connect_tools/analyser/ui/app_name.h"
#include "rtp_connect_tools/analyser/ui/app_options.h"
#include "rtp_connect_tools/analyser/ui/default_controller.h"

namespace rtp::connect::tools::analyser::ui {

///// Implementations

auto App::OnInit() -> bool {
  //  auto app_options = ParseAppOptions(APP_NAME, wxApp::argc, wxApp::argv);

  constexpr auto max_size = 1024 * 1024 * 5;  // 5MB
  constexpr auto max_files = 3;               // max 3 files are kept
  //  constexpr auto flush_seconds = 4;           // every 4 seconds, flush
  auto logger =
      spdlog::rotating_logger_mt("logger", "logs/log.txt", max_size, max_files);
  spdlog::set_default_logger(logger);
  spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%n] [%l] [%s:%#] %v");
  //  if (app_options.verbose) {
  spdlog::set_level(spdlog::level::trace);
  //  } else {
  //    spdlog::set_level(spdlog::level::warn);
  //  }
  //  spdlog::flush_every(std::chrono::seconds(flush_seconds));
  spdlog::flush_on(spdlog::level::trace);
  spdlog::info("Application logger configured");

  if (!wxApp::OnInit()) {
    spdlog::error("Application failed to launch: wxApp:OnInit() failed");
    return false;
  }

  controller_ = std::unique_ptr<Controller>{new DefaultController()};
  controller_->SetConfigurationPath(defaultConfDir());
  auto* frame = new AppFrame("RTP Connect analyser");
  controller_->SetView(frame);
  frame->SetController(controller_.get());
  return frame->Show();
}
auto App::OnExit() -> int {
  if (controller_) {
    controller_->DetachView();
  }
  return wxAppBase::OnExit();
}

auto App::defaultConfDir() -> std::filesystem::path {
#if WIN32
  return std::filesystem::path{"C:/ProgramData/rtp-analyser"};
#else
  spdlog::error(
      "Default configuration path is only defined for Windows platforms.");
  return std::filesystem::path{};
#endif
}

//

}  // namespace rtp::connect::tools::analyser::ui
