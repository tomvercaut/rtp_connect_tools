#ifndef RTP_CONNECT_TOOLS_CORE_INCLUDE_RTP_CONNECT_TOOLS_CORE_STRING_SPLIT_H
#define RTP_CONNECT_TOOLS_CORE_INCLUDE_RTP_CONNECT_TOOLS_CORE_STRING_SPLIT_H

#include <string_view>
#include <vector>

namespace rtp::connect::tools::core::string {
template <class CharType, class Traits = std::char_traits<CharType>>
[[maybe_unused]] auto Split(std::basic_string_view<CharType, Traits> view,
                            std::basic_string_view<CharType, Traits> delimiter)
    -> std::vector<std::basic_string_view<CharType, Traits>> {
  auto end = view.find(delimiter);
  decltype(end) start = 0;
  decltype(end) length = 0;
  const auto n = delimiter.size();
  std::vector<std::basic_string_view<CharType, Traits>> vec;
  while (end != std::string_view::npos) {
    length = end - start;
    vec.push_back(view.substr(start, length));
    start = end + n;
    end = view.find(delimiter, start);
  }
  vec.push_back(view.substr(start));
  return vec;
}

template <class CharType, class Traits = std::char_traits<CharType>>
[[maybe_unused]] auto Split(const std::basic_string<CharType, Traits>& view,
                            const std::basic_string<CharType, Traits>& delimiter)
-> std::vector<std::basic_string_view<CharType, Traits>> {
 return Split(std::string_view{view}, std::string_view{delimiter});
}

}  // namespace rtp::connect::tools::core::string

#endif  // RTP_CONNECT_TOOLS_CORE_INCLUDE_RTP_CONNECT_TOOLS_CORE_STRING_SPLIT_H
