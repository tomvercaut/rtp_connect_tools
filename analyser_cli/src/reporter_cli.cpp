#include "rtp_connect_tools/analyser/cli/reporter_cli.h"

#include <spdlog/spdlog.h>

#include <cmath>

namespace rtp::connect::tools::analyser::cli {

namespace core = rtp::connect::tools::core;
namespace analyser = rtp::connect::tools::analyser;

ReporterCli::ReporterCli(core::Rtp* rtp) : rtp_{rtp} {}

ReporterCli::~ReporterCli() = default;

[[maybe_unused]] void ReporterCli::Set(core::Rtp* rtp) {
  rtp_ = rtp;
  ClearDisplayedHeader();
}

void ReporterCli::NumberOfLeaves(const core::Field& field,
                                 const core::ControlPoint& control_point) {
  if (HasOutputStream()) {
    if (!DisplayedHeader()) {
      DisplayHeader();
    }
  }
  auto msg =
      fmt::format("[{} - CP {}]: Number of leaf on MLC a {} <-> expected {}\n",
                  field.field_id, control_point.control_pt_number,
                  control_point.mlc_a.size(), control_point.mlc_leaves);

  *stream_ << msg;
  msg =
      fmt::format("[{} - CP {}]: Number of leaf on MLC b {} <-> expected {}\n",
                  field.field_id, control_point.control_pt_number,
                  control_point.mlc_b.size(), control_point.mlc_leaves);
  *stream_ << msg;
}

void ReporterCli::MinimumLeafDistance(
    const core::Field& field, const core::ControlPoint& control_point,
    std::size_t leaf_index, double min_distance) {
  const auto mlc_a_size = control_point.mlc_a.size();
  const auto mlc_b_size = control_point.mlc_b.size();
  if (mlc_a_size != mlc_b_size) {
    throw std::length_error(
        fmt::format("mlc_a and mlc_b don't have the same size [{} <-> {}]",
                    mlc_a_size, mlc_b_size));
  }
  if (leaf_index >= mlc_a_size) {
    throw std::out_of_range(
        fmt::format("leaf_index [{}] is out of bound, mlc_a has a size of {}",
                    leaf_index, mlc_a_size));
  }

  const auto& leaf_a = control_point.mlc_a.at(leaf_index);
  const auto& leaf_b = control_point.mlc_b.at(leaf_index);
  const auto delta = leaf_a - leaf_b;

  const auto msg = fmt::format(
      "[{} - CP {} - mlc {}]: {} <-> {} [delta: {}, min "
      "required: {}]\n",
      field.field_id, control_point.control_pt_number, leaf_index, leaf_a,
      leaf_b, delta, min_distance);
  if (HasOutputStream()) {
    if (!DisplayedHeader()) {
      DisplayHeader();
    }
    *stream_ << msg;
  }
}

void ReporterCli::DisplayHeader() {
  PatientInfo();
  TreatmentInfo();
  display_header_ = true;
}

void ReporterCli::PatientInfo() {
  if (!HasOutputStream()) {
    return;
  }
  if (!HasRtp()) {
    return;
  }

  *stream_ << fmt::format("Patient ID: {}\n", rtp_->plan_def.patient_id);
  *stream_ << fmt::format(
      "Patient name: {} {} {}\n", rtp_->plan_def.patient_first_name,
      rtp_->plan_def.patient_m_initial, rtp_->plan_def.patient_last_name);
}
void ReporterCli::TreatmentInfo() {
  if (!HasOutputStream()) {
    return;
  }
  if (!HasRtp()) {
    return;
  }
  *stream_ << fmt::format("Course ID: {}\n", rtp_->rx_def.course_id);
  *stream_ << fmt::format("Course name: {}\n", rtp_->rx_def.course_name);
  *stream_ << fmt::format("Technique: {}\n", rtp_->rx_def.technique);
  *stream_ << fmt::format("Total dose: {}\n", rtp_->rx_def.total_dose);
  *stream_ << fmt::format("Fraction dose: {}\n", rtp_->rx_def.fraction_dose);
  *stream_ << fmt::format(
      "Fractions: {}\n",
      static_cast<int32_t>(
          std::round(rtp_->rx_def.total_dose / rtp_->rx_def.fraction_dose)));
}

void ReporterCli::ClearDisplayedHeader() { display_header_ = false; }
auto ReporterCli::DisplayedHeader() const -> bool {
  return display_header_ == true;
}
auto ReporterCli::HasRtp() const -> bool { return rtp_ != nullptr; }
auto ReporterCli::HasOutputStream() const -> bool { return stream_ != nullptr; }

}  // namespace rtp::connect::tools::analyser::cli