#include "rtp_connect_tools/analyser/ui/model_view_reporter.h"

#include <fmt/format.h>

#include "rtp_connect_tools/analyser/ui/minimum_leaf_distance.h"
#include "rtp_connect_tools/analyser/ui/mlc_count.h"
#include "rtp_connect_tools/core/rtp.h"

namespace rtp::connect::tools::analyser::ui {
void ModelViewReporter::NumberOfLeaves(
    const core::Field& field, const core::ControlPoint& control_point) {
  MlcCount mlc_count{};
  mlc_count.SetFieldId(field.field_id);
  mlc_count.SetFieldName(field.field_name);
  mlc_count.SetControlPointNumber(control_point.control_pt_number);
  mlc_count.SetValue(control_point.mlc_a.size());
  mlc_count.SetExpected(control_point.mlc_leaves);
  model_.Add(std::move(mlc_count));
}
void ModelViewReporter::MinimumLeafDistance(
    const core::Field& field, const core::ControlPoint& control_point,
    std::size_t leaf_index, double min_distance) {
  const auto mlc_a_size = control_point.mlc_a.size();
  const auto mlc_b_size = control_point.mlc_b.size();
  if (mlc_a_size != mlc_b_size) {
    model_.AddError(
        fmt::format("mlc_a and mlc_b don't have the same size [{} <-> {}]",
                    mlc_a_size, mlc_b_size));
  }
  if (leaf_index >= mlc_a_size) {
    model_.AddError(
        fmt::format("leaf_index [{}] is out of bound, mlc_a has a size of {}",
                    leaf_index, mlc_a_size));
  }

  const auto& leaf_a = control_point.mlc_a.at(leaf_index);
  const auto& leaf_b = control_point.mlc_b.at(leaf_index);

  class MinimumLeafDistance mld;
  mld.SetFieldId(field.field_id);
  mld.SetFieldName(field.field_name);
  mld.SetControlPointNumber(control_point.control_pt_number);
  mld.SetLeafA(leaf_a);
  mld.SetLeafB(leaf_b);
  mld.SetMinDistance(min_distance);
  model_.Add(mld);
}

[[maybe_unused]] void ModelViewReporter::Clear() { model_.Clear(); }
[[maybe_unused]] auto ModelViewReporter::Data() -> ModelView& { return model_; }
[[maybe_unused]] [[nodiscard]] auto ModelViewReporter::Data() const -> const ModelView& { return model_; }

}  // namespace rtp::connect::tools::analyser::ui
