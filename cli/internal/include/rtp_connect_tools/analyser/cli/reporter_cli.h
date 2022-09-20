#ifndef RTP_CONNECT_TOOLS_ANALYSER_CLI_REPORTER_CLI_H
#define RTP_CONNECT_TOOLS_ANALYSER_CLI_REPORTER_CLI_H

#include <cstdlib>
#include <iostream>

#include "rtp_connect_tools/core/rtp.h"
#include "rtp_connect_tools/analyser/reporter.h"

namespace rtp::connect::tools::analyser::cli {

class [[maybe_unused]] ReporterCli : public Reporter {
 public:
  ReporterCli() = default;
  ReporterCli(const ReporterCli&) = default;
  ReporterCli(ReporterCli&&) = default;
  explicit ReporterCli(rtp::connect::tools::core::Rtp* rtp);
  ~ReporterCli() override;

  auto operator=(const ReporterCli&) -> ReporterCli& = default;
  auto operator=(ReporterCli&&) -> ReporterCli& = default;

  [[maybe_unused]] void Set(rtp::connect::tools::core::Rtp* rtp);

  void NumberOfLeaves(const rtp::connect::tools::core::Field& field,
                      const rtp::connect::tools::core::ControlPoint& control_point) override;
  void MinimumLeafDistance(const rtp::connect::tools::core::Field& field,
                           const rtp::connect::tools::core::ControlPoint& control_points,
                           std::size_t leaf_index,
                           double min_distance) override;

 private:
  void DisplayHeader();
  void PatientInfo();
  void TreatmentInfo();
  [[nodiscard]] auto DisplayedHeader() const -> bool;
  void ClearDisplayedHeader();
  [[nodiscard]] auto HasRtp() const -> bool;
  [[nodiscard]] auto HasOutputStream() const -> bool;

  rtp::connect::tools::core::Rtp* rtp_ = nullptr;
  std::ostream* stream_ = &std::cout;
  bool display_header_ = false;
};

} // namespace rtp::connect::tools::analyser::cli

#endif  // RTP_CONNECT_TOOLS_ANALYSER_CLI_REPORTER_CLI_H
