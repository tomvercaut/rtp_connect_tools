#ifndef RTP_CONNECT_TOOLS_CORE_PARSER_H
#define RTP_CONNECT_TOOLS_CORE_PARSER_H

#include <optional>
#include <string>
#include <vector>

#include "rtp_connect_tools/core/rtp.h"

namespace rtp::connect::tools::core {
[[maybe_unused]] auto ParseRtpFile(const std::string& filename) -> Rtp;
auto ParseRtpValues(Rtp& rtp, std::vector<std::string>&& values) -> int;

namespace details {

/// Interprets a 32 bit integer in a string.
///
/// If the string is empty, an empty optional is returned. Otherwise the string
/// is interpreted as a 32 bit integer and returned as an optional.
///
/// \param s string to be interpreted
/// \return An empty optional if the string is empty, an optional 32 bit integer
/// otherwise.
auto StrToOptInt32(const std::string& s) -> std::optional<int32_t>;

/// Interprets a double precision floating point in a string.
///
/// If the string is empty, an empty optional is returned. Otherwise the string
/// is interpreted as a double and returned as an optional.
///
/// \param s string to be interpreted
/// \return An empty optional if the string is empty, an optional double
/// otherwise.
auto StrToOptDouble(const std::string& s) -> std::optional<double>;

/// Interpret a rotational direction (CW, CCW) in a string.
///
/// \param s string to be interpreted
/// \return Rotational direction:
///   - CW -> RotationDirection::cw
///   - CCW -> RotationDirection::ccw
///   - none -> RotationDirection::none
auto StrToRotationDirection(const std::string& s) -> RotationDirection;

/// Convert a comma separated values (CSV) line into a vector of string values.
///
/// If a value is quoted, it's expected to be quoted before and after the value.
/// If this is the case, the quotes are removed. Otherwise the quotes are not
/// removed.
///
/// \param line comma separated values line
/// \return vector of unquoted CSV values
auto ParseCsvLine(std::string&& line) -> std::vector<std::string>;

/// Parse the CSV values from a PLAN_DEF line.
///
/// The input CSV values are not quoted and the first value should be equal to
/// PLAN_DEF.
///
/// \param plan_def Plan definition
/// \param values CSV values corresponding to one line with PLAN_DEF data
/// \return Status codes:
///   - 0: OK
///   - 1: expected number of columns mismatch with the number of CSV values
///   - 2: the first value in values (keyword) does not equal PLAN_DEF
auto ParsePlan(Plan& plan_def, std::vector<std::string>&& values) -> int;

/// Parse the CSV values from a EXTENDED_PLAN_DEF line.
///
/// The input CSV values are not quoted and the first value should be equal to
/// EXTENDED_PLAN_DEF.
///
/// \param plan_def Extended plan definition
/// \param values CSV values corresponding to one line with EXTENDED_PLAN_DEF data
/// \return Status codes:
///   - 0: OK
///   - 1: expected number of columns mismatch with the number of CSV values
///   - 2: the first value in values (keyword) does not equal PLAN_EXTENDED_DEF
[[maybe_unused]] auto ParseExtendedPlan(ExtendedPlan& plan_def, std::vector<std::string>&& values) -> int;


/// Parse the CSV values from prescription definition (Rx).
///
/// The input CSV values are not quoted and the first value should be equal to
/// RX_DEF.
///
/// \param rxd prescription definition
/// \param values CSV values corresponding to one line with RX_DEF data
/// \return Status codes:
///   - 0: OK
///   - 1: expected number of columns mismatch with the number of CSV values
///   - 2: the first value in values (keyword) does not equal RX_DEF
auto ParseRx(Rx& rxd, std::vector<std::string>&& values) -> int;

/// Parse the CSV values from site definition (SITE_SETUP_DEF).
///
/// The input CSV values are not quoted and the first value should be equal to
/// SITE_SETUP_DEF.
///
/// \param site_setup site setup definition
/// \param values CSV values corresponding to one line with SITE_SETUP_DEF data
/// \return Status codes:
///   - 0: OK
///   - 1: expected number of columns mismatch with the number of CSV values
///   - 2: the first value in values (keyword) does not equal SITE_SETUP_DEF
auto ParseSiteSetup(SiteSetup& site_setup, std::vector<std::string>&& values)
    -> int;

/// Parse the CSV values from simulation definition (SIM_DEF).
///
/// The input CSV values are not quoted and the first value should be equal to
/// SIM_DEF.
///
/// \param sim simulation definition
/// \param values CSV values corresponding to one line with SIM_DEF data
/// \return Status codes:
///   - 0: OK
///   - 1: expected number of columns mismatch with the number of CSV values
///   - 2: the first value in values (keyword) does not equal SIM_DEF
auto ParseSim(Sim& sim, std::vector<std::string>&& values) -> int;

/// Parse the CSV values from the field definition (FIELD_DEF).
///
/// The input CSV values are not quoted and the first value should be equal to
/// FIELD_DEF.
///
/// \param field field definition
/// \param values CSV values corresponding to one line with FIELD_DEF data
/// \return Status codes:
///   - 0: OK
///   - 1: expected number of columns mismatch with the number of CSV values
///   - 2: the first value in values (keyword) does not equal FIELD_DEF
auto ParseField(Field& field, std::vector<std::string>&& values) -> int;
/// Parse the CSV values from the extended field definition
/// (EXTENDED_FIELD_DEF).
///
/// The input CSV values are not quoted and the first value should be equal to
/// EXTENDED_FIELD_DEF.
///
/// \param field extended field definition
/// \param values CSV values corresponding to one line with EXTENDED_FIELD_DEF
/// data \return Status codes:
///   - 0: OK
///   - 1: expected number of columns mismatch with the number of CSV values
///   - 2: the first value in values (keyword) does not equal EXTENDED_FIELD_DEF
auto ParseExtendedField(ExtendedField& field, std::vector<std::string>&& values)
    -> int;

/// Parse the CSV values from the control point definition (CONTROL_PT_DEF).
///
/// The input CSV values are not quoted and the first value should be equal to
/// CONTROL_PT_DEF.
///
/// \param cp control point
/// \param values CSV values corresponding to one line with CONTROL_PT_DEF data
/// \return Status codes:
///   - 0: OK
///   - 1: expected number of columns mismatch with the number of CSV values
///   - 2: the first value in values (keyword) does not equal CONTROL_PT_DEF
///   - 3: unsupported MU convention
///   - 4: unsupported scale convention
auto ParseControlPoint(ControlPoint& cp, std::vector<std::string>&& values)
    -> int;

}  // namespace details
}  // namespace rtp::connect::tools::core

#endif  // RTP_CONNECT_TOOLS_CORE_PARSER_H
