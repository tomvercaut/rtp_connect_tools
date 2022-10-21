
#ifndef RTP_CONNECT_TOOLS_UI_INCLUDE_RTP_CONNECT_TOOLS_ANALYSER_UI_MODEL_VIEW_H
#define RTP_CONNECT_TOOLS_UI_INCLUDE_RTP_CONNECT_TOOLS_ANALYSER_UI_MODEL_VIEW_H

#include <filesystem>
#include <string>
#include <vector>

#include "rtp_connect_tools/analyser/ui/minimum_leaf_distance.h"
#include "rtp_connect_tools/analyser/ui/mlc_count.h"

namespace rtp::connect::tools::analyser::ui {

class ModelView {
 public:
  [[maybe_unused]] [[nodiscard]] auto GetPath() const
      -> const std::filesystem::path&;
  [[maybe_unused]] void SetPath(const std::filesystem::path& path);
  [[maybe_unused]] void Add(const MlcCount& mlc_count);
  [[maybe_unused]] void Add(MlcCount&& mlc_count);
  [[maybe_unused]] void ClearMlcCount();

  [[maybe_unused]] void Add(const MinimumLeafDistance& min_dist);
  [[maybe_unused]] void Add(MinimumLeafDistance&& min_dist);
  [[maybe_unused]] void ClearMinimumLeafDistances();

  [[maybe_unused]] void AddError(const std::string& msg);
  void AddError(std::string&& msg);
  [[maybe_unused]] void ClearErrors();

  [[maybe_unused]] void Clear();


  [[nodiscard]] auto GetFieldIds() const -> std::vector<std::string>;
  [[nodiscard]] auto GetControlPointNumbers(const std::string& field_id) const -> std::vector<int>;
  [[nodiscard]] auto MlcCount(const std::string& field_id, uint32_t control_point_number) const -> std::optional<MlcCount>;
  [[nodiscard]] auto MinimumLeafDistance(const std::string& field_id, uint32_t control_point_number) const -> std::optional<class MinimumLeafDistance>;
//  [[nodiscard]] auto MlcCounts(const std::string& field_id) const -> std::vector<MlcCount>;
//  [[nodiscard]] auto MinimumLeafDistances(const std::string& field_id) const -> std::vector<MinimumLeafDistance>;

 private:
  std::filesystem::path path_{};
  std::vector<class MlcCount> mlc_counts_{};
  std::vector<class MinimumLeafDistance> min_leaf_dist_{};
  std::vector<std::string> errors_{};
};

}  // namespace rtp::connect::tools::analyser::ui

#endif  // RTP_CONNECT_TOOLS_UI_INCLUDE_RTP_CONNECT_TOOLS_ANALYSER_UI_MODEL_VIEW_H
