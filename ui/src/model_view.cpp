#include "rtp_connect_tools/analyser/ui/model_view.h"

namespace rtp::connect::tools::analyser::ui {

[[maybe_unused]] auto ModelView::GetPath() const
    -> const std::filesystem::path& {
  return path_;
}
[[maybe_unused]] void ModelView::SetPath(const std::filesystem::path& path) {
  path_ = path;
}
[[maybe_unused]] void ModelView::Add(const class MlcCount& mlc_count) {
  mlc_counts_.push_back(mlc_count);
}
[[maybe_unused]] void ModelView::Add(class MlcCount&& mlc_count) {
  mlc_counts_.push_back(std::move(mlc_count));
}
[[maybe_unused]] void ModelView::ClearMlcCount() { mlc_counts_.clear(); }
[[maybe_unused]] void ModelView::Add(const class MinimumLeafDistance& min_dist) {
  min_leaf_dist_.push_back(min_dist);
}
[[maybe_unused]] void ModelView::Add(class MinimumLeafDistance&& min_dist) {
  min_leaf_dist_.push_back(std::move(min_dist));
}
[[maybe_unused]] void ModelView::ClearMinimumLeafDistances() {
  min_leaf_dist_.clear();
}

[[maybe_unused]] void ModelView::AddError(const std::string& msg) {
  errors_.push_back(msg);
}
void ModelView::AddError(std::string&& msg) {
  errors_.push_back(std::move(msg));
}
[[maybe_unused]] void ModelView::ClearErrors() { errors_.clear(); }
[[maybe_unused]] void ModelView::Clear() {
  path_.clear();
  mlc_counts_.clear();
  min_leaf_dist_.clear();
  errors_.clear();
}

void InsertIfNotExist(std::vector<int>& vec, int value) {
  if (std::find(vec.cbegin(), vec.cend(), value) == vec.cend()) {
    vec.push_back(value);
  }
}

void InsertIfNotExist(std::vector<std::string>& vec, const std::string& value) {
  if (std::find(vec.cbegin(), vec.cend(), value) == vec.cend()) {
    vec.push_back(value);
  }
}

auto ModelView::GetFieldIds() const -> std::vector<std::string> {
  std::vector<std::string> vid;
  std::for_each(mlc_counts_.cbegin(), mlc_counts_.cend(),
                [&](const auto& mlc_count) {
                  InsertIfNotExist(vid, mlc_count.GetFieldId());
                });
  std::for_each(
      min_leaf_dist_.cbegin(), min_leaf_dist_.cend(),
      [&](const auto& mld) { InsertIfNotExist(vid, mld.GetFieldId()); });
  return vid;
}

auto ModelView::GetControlPointNumbers(const std::string& field_id) const
    -> std::vector<int> {
  std::vector<int> v;
  std::for_each(mlc_counts_.cbegin(), mlc_counts_.cend(), [&](const auto& mlc_count){
    InsertIfNotExist(v,mlc_count.GetControlPointNumber());
  });
  return v;
}

auto ModelView::MlcCount(const std::string& field_id,
                         uint32_t control_point_number) const
    -> std::optional<class MlcCount> {
  for (const auto& mlc_count : mlc_counts_) {
    if (mlc_count.GetFieldId() == field_id && mlc_count.GetControlPointNumber() == control_point_number) {
      return {mlc_count};
    }
  }
  return {};
}
auto ModelView::MinimumLeafDistance(const std::string& field_id,
                                    uint32_t control_point_number) const
    -> std::optional<class MinimumLeafDistance> {
 for (const auto& mld : min_leaf_dist_) {
    if (mld.GetFieldId() == field_id && mld.GetControlPointNumber() == control_point_number) {
      return {mld};
    }
  }
  return {};
}

//auto ModelView::MlcCounts(const std::string& field_id) const
//    -> std::vector<MlcCount> {
//  std::vector<MlcCount> vmc;
//  std::for_each(mlc_counts_.cbegin(), mlc_counts_.cend(),
//                [&](const auto& mlc_count) {
//                  if (mlc_count.GetFieldId() == field_id) {
//                    vmc.push_back(mlc_count);
//                  }
//                });
//  std::sort(vmc.begin(), vmc.end(), [](const auto& a, const auto& b) {
//    return a.GetControlPointNumber() < b.GetControlPointNumber();
//  });
//  return vmc;
//}
//auto ModelView::MinimumLeafDistances(const std::string& field_id) const
//    -> std::vector<MinimumLeafDistance> {
//  std::vector<MinimumLeafDistance> vmld;
//  std::for_each(min_leaf_dist_.cbegin(), min_leaf_dist_.cend(),
//                [&](const auto& mld) {
//                  if (mld.GetFieldId() == field_id) {
//                    vmld.push_back(mld);
//                  }
//                });
//  std::sort(vmld.begin(), vmld.end(), [](const auto& a, const auto& b) {
//    return a.GetControlPointNumber() < b.GetControlPointNumber();
//  });
//  return vmld;
//}
}  // namespace rtp::connect::tools::analyser::ui
