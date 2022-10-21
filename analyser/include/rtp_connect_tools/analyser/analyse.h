#ifndef RTP_CONNECT_TOOLS_ANALYSER_ANALYSE_H
#define RTP_CONNECT_TOOLS_ANALYSER_ANALYSE_H

#include <vector>

#include "rtp_connect_tools/core/rtp.h"
#include "rtp_connect_tools/analyser/machine_profile.h"
#include "rtp_connect_tools/analyser/reporter.h"

namespace rtp::connect::tools::analyser {

/// Perform a set of tests on the Rtp in function of the machine profiles.
/// \param rtp Model for an RTP Connect file
/// \param profiles list of machine profiles
/// \param reporter Report errors to the users
/// \return
///   - 0:  no errors where detected
///   - 1:  unable to find matching machine profile for treatment field
///   - 2:  number of leaves doesn't match between two leaf banks or the number
///   of expected_ leaves.
///   - 3:  minimum distance between two opposing leaves is less than the
///   distance described in the machine profile
[[maybe_unused]] auto Analyse(const rtp::connect::tools::core::Rtp& rtp,
             const std::vector<MachineProfile>& profiles, Reporter& reporter)
    -> int32_t;

}  // namespace rtp::connect::tools::analyser

#endif  // RTP_CONNECT_TOOLS_ANALYSER_ANALYSE_H
