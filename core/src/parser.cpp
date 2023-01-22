#include "rtp_connect_tools/core/parser.h"

#include <spdlog/spdlog.h>

#include <fstream>

#include "rtp_connect_tools/core/string/split.h"

namespace rtp::connect::tools::core {

[[maybe_unused]] auto ParseRtpFile(const std::string& filename) -> Rtp {
  std::ifstream input(filename);
  Rtp rtp;
  try {
    if (!input.is_open()) {
      throw std::exception(fmt::format("failed to open: {}", filename).c_str());
    }
    std::string line;
    while (input) {
      std::getline(input, line);
      auto vec = details::ParseCsvLine(std::move(line));
      if (auto return_value = ParseRtpValues(rtp, std::move(vec));
          return_value != 0) {
        throw std::exception(
            fmt::format("Failed to parse RTP value_. Error code: {}",
                        return_value)
                .c_str());
      }
      line = "";
    }
    input.close();
    if (input.is_open()) {
      throw std::exception(
          fmt::format("failed to close: {}", filename).c_str());
    }
  } catch (std::exception& ex) {
    spdlog::error("exception caught while opening: {}\n{}", filename,
                  ex.what());
    exit(1);
  }

  return rtp;
}

auto ParseRtpValues(Rtp& rtp, std::vector<std::string>&& values) -> int {
  if (values.empty()) {
    return 0;
  }
  if (values[0] == "PLAN_DEF") {
    if (auto return_value = details::ParsePlan(rtp.plan_def, std::move(values));
        return_value != 0) {
      return return_value;
    }
  } else if (values[0] == "EXTENDED_PLAN_DEF") {
    // no info gathered
  } else if (values[0] == "RX_DEF") {
    if (auto return_value = details::ParseRx(rtp.rx_def, std::move(values));
        return_value != 0) {
      return return_value;
    }
  } else if (values[0] == "SITE_SETUP_DEF") {
    if (auto return_value =
            details::ParseSiteSetup(rtp.site_setup, std::move(values));
        return_value != 0) {
      return return_value;
    }
  } else if (values[0] == "SIM_DEF") {
    if (auto return_value = details::ParseSim(rtp.sim, std::move(values));
        return_value != 0) {
      return return_value;
    }
  } else if (values[0] == "FIELD_DEF") {
    Field field;
    if (auto return_value = details::ParseField(field, std::move(values));
        return_value != 0) {
      return return_value;
    }
    rtp.fields.push_back(std::move(field));
  } else if (values[0] == "EXTENDED_FIELD_DEF") {
    ExtendedField field;
    if (auto return_value =
            details::ParseExtendedField(field, std::move(values));
        return_value != 0) {
      return return_value;
    }
    rtp.extended_fields.push_back(std::move(field));
  } else if (values[0] == "CONTROL_PT_DEF") {
    ControlPoint cp;
    if (auto return_value = details::ParseControlPoint(cp, std::move(values));
        return_value != 0) {
      return return_value;
    }
    rtp.control_points.push_back(std::move(cp));
  }

  return 0;
}

namespace details {

auto StrToOptInt32(const std::string& s) -> std::optional<int32_t> {
  if (s.empty()) {
    return {};
  }
  int32_t value = std::stoi(s);
  return {value};
}

auto StrToOptDouble(const std::string& s) -> std::optional<double> {
  if (s.empty()) {
    return {};
  }
  double value = std::stod(s);
  return {value};
}

auto StrToRotationDirection(const std::string& s) -> RotationDirection {
  if (s == "CCW") {
    return RotationDirection::ccw;
  } else if (s == "CW") {
    return RotationDirection::cw;
  }
  return RotationDirection::none;
}

auto ParseCsvLine(std::string&& line) -> std::vector<std::string> {
  auto lin = std::move(line);
  constexpr auto delim = std::string_view{","};
  const auto vec = core::string::Split(std::string_view{lin}, delim);
  std::vector<std::string> result;
  result.reserve(vec.size());
  for (auto& value : vec) {
    if (value.starts_with("\"") && value.ends_with("\"")) {
      result.emplace_back(value.substr(1, value.length()-2));
    } else {
      result.emplace_back(value);
    }
  }
  return result;
}

auto ParsePlan(Plan& plan_def, std::vector<std::string>&& values) -> int {
  auto size = values.size();
  auto n_columns = static_cast<int16_t>(PlanColumn::kCrc) + 1;
  if (size != n_columns) {
    spdlog::error("expected_ {} columns in this line [actual={}]", n_columns,
                  size);
    return 1;
  }
  if (values[static_cast<int16_t>(PlanColumn::kKeyword)] != "PLAN_DEF") {
    spdlog::error("expected_ PLAN_DEF as an identifier for the CSV line");
    return 2;
  }

  plan_def.patient_id = values[static_cast<int16_t>(PlanColumn::kPatientId)];
  plan_def.patient_last_name =
      values[static_cast<int16_t>(PlanColumn::kPatientLastName)];
  plan_def.patient_first_name =
      values[static_cast<int16_t>(PlanColumn::kPatientFirstName)];
  plan_def.patient_m_initial =
      values[static_cast<int16_t>(PlanColumn::kPatientMInitial)];
  plan_def.plan_id = values[static_cast<int16_t>(PlanColumn::kPlanId)];
  plan_def.date = values[static_cast<int16_t>(PlanColumn::kDate)];
  plan_def.time = values[static_cast<int16_t>(PlanColumn::kTime)];
  plan_def.course_id = values[static_cast<int16_t>(PlanColumn::kCourseId)];
  plan_def.diagnosis = values[static_cast<int16_t>(PlanColumn::kDiagnosis)];
  plan_def.md_last_name = values[static_cast<int16_t>(PlanColumn::kMDLastName)];
  plan_def.md_first_name =
      values[static_cast<int16_t>(PlanColumn::kMDFirstName)];
  plan_def.md_m_initial = values[static_cast<int16_t>(PlanColumn::kMDMInitial)];
  plan_def.md_approve_last_name =
      values[static_cast<int16_t>(PlanColumn::kMDApproveLName)];
  plan_def.md_approve_first_name =
      values[static_cast<int16_t>(PlanColumn::kMDApproveFName)];
  plan_def.md_approve_m_initial =
      values[static_cast<int16_t>(PlanColumn::kMDApproveMInitial)];
  plan_def.phy_approve_last_name =
      values[static_cast<int16_t>(PlanColumn::kPhyApproveLName)];
  plan_def.phy_approve_first_name =
      values[static_cast<int16_t>(PlanColumn::kPhyApproveFName)];
  plan_def.phy_approve_m_initial =
      values[static_cast<int16_t>(PlanColumn::kPhyApproveMInitial)];
  plan_def.author_last_name =
      values[static_cast<int16_t>(PlanColumn::kAuthorLName)];
  plan_def.author_first_name =
      values[static_cast<int16_t>(PlanColumn::kAuthorFName)];
  plan_def.author_m_initial =
      values[static_cast<int16_t>(PlanColumn::kAuthorMInitial)];
  plan_def.rtp_mfg = values[static_cast<int16_t>(PlanColumn::kRtpMfg)];
  plan_def.rtp_model = values[static_cast<int16_t>(PlanColumn::kRtpModel)];
  plan_def.rtp_version = values[static_cast<int16_t>(PlanColumn::kRtpVersion)];
  plan_def.rtp_if_protocol =
      values[static_cast<int16_t>(PlanColumn::kRtpIfProtocol)];
  plan_def.rtp_if_version =
      values[static_cast<int16_t>(PlanColumn::kRtpIfVersion)];
  plan_def.crc = std::stoi(values[static_cast<int32_t>(PlanColumn::kCrc)]);
  return 0;
}

[[maybe_unused]] auto ParseExtendedPlan(ExtendedPlan& plan_def,
                                        std::vector<std::string>&& values)
    -> int {
  auto size = values.size();
  auto n_columns = static_cast<uint8_t>(ExtendedPlanColumn::kCrc) + 1;
  if (size != n_columns) {
    spdlog::error("expected_ {} columns in this line [actual={}]", n_columns,
                  size);
    return 1;
  }
  if (values[static_cast<uint8_t>(PlanColumn::kKeyword)] != "EXTENDED_PLAN_DEF") {
    spdlog::error("expected_ EXTENDED_PLAN_DEF as an identifier for the CSV line");
    return 2;
  }

  const std::string encoding_prefix = "ENCODING=";
  const std::string fullname_prefix = "FULLNAME=";
  const std::string comments_prefix = "PATIENTCOMMENTS=";

  plan_def.encoding =
      values[static_cast<uint8_t>(ExtendedPlanColumn::kEncoding)];
  if (const auto pos = plan_def.encoding.find(encoding_prefix);
      pos != std::string::npos) {
    plan_def.encoding.erase(pos, encoding_prefix.length());
  }
  plan_def.fullname =
      values[static_cast<uint8_t>(ExtendedPlanColumn::kFullname)];
  if (const auto pos = plan_def.fullname.find(fullname_prefix);
      pos != std::string::npos) {
    plan_def.fullname.erase(pos, fullname_prefix.length());
  }
  plan_def.patient_comments =
      values[static_cast<uint8_t>(ExtendedPlanColumn::kPatientComments)];
  if (const auto pos = plan_def.patient_comments.find(comments_prefix);
      pos != std::string::npos) {
    plan_def.patient_comments.erase(pos, comments_prefix.length());
  }
  return 0;
}

auto ParseRx(Rx& rxd, std::vector<std::string>&& values) -> int {
  auto size = values.size();
  constexpr auto ncol = 13;
  if (size != ncol) {
    spdlog::error("expected_ {} columns in this line [actual={}]", ncol, size);
    return 1;
  }
  if (values[static_cast<int16_t>(RxColumn::kKeyword)] != "RX_DEF") {
    spdlog::error("expected_ RX_DEF as an identifier for the CSV line");
    return 2;
  }

  rxd.course_id = std::stoi(values[static_cast<int32_t>(RxColumn::kCourseId)]);
  rxd.course_name = values[static_cast<int16_t>(RxColumn::kCourseName)];
  rxd.technique = values[static_cast<int16_t>(RxColumn::kTechnique)];
  rxd.modality = values[static_cast<int16_t>(RxColumn::kModality)];
  rxd.dose_spec = values[static_cast<int16_t>(RxColumn::kDoseSpec)];
  rxd.rx_depth = values[static_cast<int16_t>(RxColumn::kRxDepth)];
  rxd.total_dose = std::stod(values[static_cast<int16_t>(RxColumn::kDoseTTL)]);
  rxd.fraction_dose =
      std::stod(values[static_cast<int16_t>(RxColumn::kDoseTx)]);
  rxd.pattern = values[static_cast<int16_t>(RxColumn::kPattern)];
  rxd.rx_note = values[static_cast<int16_t>(RxColumn::kRxNote)];
  rxd.number_of_fields =
      std::stoi(values[static_cast<int32_t>(RxColumn::kNumberOfFields)]);
  rxd.crc = std::stoi(values[static_cast<int32_t>(RxColumn::kCrc)]);
  return 0;
}

auto ParseSiteSetup(SiteSetup& site_setup, std::vector<std::string>&& values)
    -> int {
  auto size = values.size();
  constexpr auto ncol = 25;
  if (size != ncol) {
    spdlog::error("expected_ {} columns in this line [actual={}]", ncol, size);
    return 1;
  }
  if (values[static_cast<int16_t>(SiteSetupColumn::kKeyword)] !=
      "SITE_SETUP_DEF") {
    spdlog::error("expected_ SITE_SETUP_DEF as an identifier for the CSV line");
    return 2;
  }

  site_setup.rx_site_name =
      values[static_cast<int16_t>(SiteSetupColumn::kRxSiteName)];
  site_setup.patient_orientation =
      values[static_cast<int16_t>(SiteSetupColumn::kPatientOrientation)];
  site_setup.treatment_machine =
      values[static_cast<int16_t>(SiteSetupColumn::kTreatmentMachine)];
  site_setup.tolerance_table =
      values[static_cast<int16_t>(SiteSetupColumn::kToleranceTable)];
  site_setup.isocenter_x = StrToOptDouble(
      values[static_cast<int16_t>(SiteSetupColumn::kIsocenterPositionX)]);
  site_setup.isocenter_y = StrToOptDouble(
      values[static_cast<int16_t>(SiteSetupColumn::kIsocenterPositionY)]);
  site_setup.isocenter_z = StrToOptDouble(
      values[static_cast<int16_t>(SiteSetupColumn::kIsocenterPositionZ)]);
  site_setup.structure_set_uid =
      values[static_cast<int16_t>(SiteSetupColumn::kStructureSetUid)];
  site_setup.frame_of_reference_uid =
      values[static_cast<int16_t>(SiteSetupColumn::kFrameOfReferenceUid)];
  site_setup.couch_vertical = StrToOptDouble(
      values[static_cast<int16_t>(SiteSetupColumn::kCouchVertical)]);
  site_setup.couch_lateral = StrToOptDouble(
      values[static_cast<int16_t>(SiteSetupColumn::kCouchLateral)]);

  site_setup.couch_longitudinal = StrToOptDouble(
      values[static_cast<int16_t>(SiteSetupColumn::kCouchLongitudinal)]);
  site_setup.couch_angle = StrToOptDouble(
      values[static_cast<int16_t>(SiteSetupColumn::kCouchAngle)]);
  site_setup.couch_pedestal = StrToOptDouble(
      values[static_cast<int16_t>(SiteSetupColumn::kCouchPedestal)]);
  site_setup.table_top_vert_displacement = StrToOptDouble(
      values[static_cast<int16_t>(SiteSetupColumn::kTableTopVertDisplacement)]);
  site_setup.table_top_long_displacement = StrToOptDouble(
      values[static_cast<int16_t>(SiteSetupColumn::kTableTopLongDisplacement)]);
  site_setup.table_top_lat_displacement = StrToOptDouble(
      values[static_cast<int16_t>(SiteSetupColumn::kTableTopLatDisplacement)]);
  site_setup.mrl_coil_name =
      values[static_cast<int16_t>(SiteSetupColumn::kMrlCoilName)];
  site_setup.mrl_coil_index = StrToOptInt32(
      values[static_cast<int16_t>(SiteSetupColumn::kMrlCoilIndex)]);
  site_setup.couch_reference =
      values[static_cast<int16_t>(SiteSetupColumn::kCouchReference)];
  site_setup.couch_reference_index = StrToOptInt32(
      values[static_cast<int16_t>(SiteSetupColumn::kCouchReferenceIndex)]);
  site_setup.respiratory_motion_compensation_technique =
      values[static_cast<int16_t>(
          SiteSetupColumn::kRespiratoryMotionCompensationTechnique)];
  site_setup.respiratory_signal_source =
      values[static_cast<int16_t>(SiteSetupColumn::kRespiratorySignalSource)];
  site_setup.crc =
      std::stoi(values[static_cast<int16_t>(SiteSetupColumn::kCrc)]);
  return 0;
}

auto ParseSim(Sim& sim, std::vector<std::string>&& values) -> int {
  auto size = values.size();
  constexpr auto n_col = 53;
  if (size != n_col) {
    spdlog::error("expected_ {} columns in this line [actual={}]", n_col, size);
    return 1;
  }
  if (values[static_cast<int16_t>(SimColumn::kKeyword)] != "SIM_DEF") {
    spdlog::error("expected_ SIM_DEF as an identifier for the CSV line");
    return 2;
  }

  sim.rx_site_name = values[static_cast<int16_t>(SimColumn::kRxSiteName)];
  sim.field_name = values[static_cast<int16_t>(SimColumn::kFieldName)];
  sim.field_id = values[static_cast<int16_t>(SimColumn::kFieldId)];
  sim.field_note = values[static_cast<int16_t>(SimColumn::kFieldNote)];
  sim.treatment_machine =
      values[static_cast<int16_t>(SimColumn::kTreatmentMachine)];
  sim.gantry_angle =
      std::stod(values[static_cast<int16_t>(SimColumn::kGantryAngle)]);
  sim.collimator_angle =
      std::stod(values[static_cast<int16_t>(SimColumn::kCollimatorAngle)]);
  sim.field_x_mode = values[static_cast<int16_t>(SimColumn::kFieldXMode)];
  sim.field_x =
      StrToOptDouble(values[static_cast<int16_t>(SimColumn::kFieldX)]);
  sim.collimator_x1 =
      StrToOptDouble(values[static_cast<int16_t>(SimColumn::kCollimatorX1)]);
  sim.collimator_x2 =
      StrToOptDouble(values[static_cast<int16_t>(SimColumn::kCollimatorX2)]);
  sim.field_y_mode = values[static_cast<int16_t>(SimColumn::kFieldYMode)];
  sim.field_y =
      StrToOptDouble(values[static_cast<int16_t>(SimColumn::kFieldY)]);
  sim.collimator_y1 =
      StrToOptDouble(values[static_cast<int16_t>(SimColumn::kCollimatorY1)]);
  sim.collimator_y2 =
      StrToOptDouble(values[static_cast<int16_t>(SimColumn::kCollimatorY2)]);
  sim.couch_vertical =
      StrToOptDouble(values[static_cast<int16_t>(SimColumn::kCouchVertical)]);
  sim.couch_lateral =
      StrToOptDouble(values[static_cast<int16_t>(SimColumn::kCouchLateral)]);
  sim.couch_longitudinal = StrToOptDouble(
      values[static_cast<int16_t>(SimColumn::kCouchLongitudinal)]);
  sim.couch_angle =
      StrToOptDouble(values[static_cast<int16_t>(SimColumn::kCouchAngle)]);
  sim.couch_pedestal =
      StrToOptDouble(values[static_cast<int16_t>(SimColumn::kCouchPedestal)]);
  sim.sad = StrToOptDouble(values[static_cast<int16_t>(SimColumn::kSad)]);
  sim.ap_separation = values[static_cast<int16_t>(SimColumn::kApSeparation)];
  sim.pa_separation = values[static_cast<int16_t>(SimColumn::kPaSeparation)];
  sim.lateral_separation =
      values[static_cast<int16_t>(SimColumn::kLateralSeparation)];
  sim.tangential_separation =
      values[static_cast<int16_t>(SimColumn::kTangentialSeparation)];
  sim.other_label_1 = values[static_cast<int16_t>(SimColumn::kOtherLabel1)];
  sim.ssd_1 = StrToOptDouble(values[static_cast<int16_t>(SimColumn::kSsd1)]);
  sim.sfd_1 = StrToOptDouble(values[static_cast<int16_t>(SimColumn::kSfd1)]);
  sim.other_label_2 = values[static_cast<int16_t>(SimColumn::kOtherLabel2)];
  sim.other_measurement_1 =
      values[static_cast<int16_t>(SimColumn::kOtherMeasurement1)];
  sim.other_measurement_2 =
      values[static_cast<int16_t>(SimColumn::kOtherMeasurement2)];
  sim.other_label_3 = values[static_cast<int16_t>(SimColumn::kOtherLabel3)];
  sim.other_measurement_3 =
      values[static_cast<int16_t>(SimColumn::kOtherMeasurement3)];
  sim.other_measurement_4 =
      values[static_cast<int16_t>(SimColumn::kOtherMeasurement4)];
  sim.other_label_4 = values[static_cast<int16_t>(SimColumn::kOtherLabel4)];
  sim.other_measurement_5 =
      values[static_cast<int16_t>(SimColumn::kOtherMeasurement5)];
  sim.other_measurement_6 =
      values[static_cast<int16_t>(SimColumn::kOtherMeasurement6)];
  sim.blade_x_mode = values[static_cast<int16_t>(SimColumn::kBladeXMode)];
  sim.blade_x =
      StrToOptDouble(values[static_cast<int16_t>(SimColumn::kBladeX)]);
  sim.blade_x1 =
      StrToOptDouble(values[static_cast<int16_t>(SimColumn::kBladeX1)]);
  sim.blade_x2 =
      StrToOptDouble(values[static_cast<int16_t>(SimColumn::kBladeX2)]);
  sim.blade_y_mode = values[static_cast<int16_t>(SimColumn::kBladeYMode)];
  sim.blade_y =
      StrToOptDouble(values[static_cast<int16_t>(SimColumn::kBladeY)]);
  sim.blade_y1 =
      StrToOptDouble(values[static_cast<int16_t>(SimColumn::kBladeY1)]);
  sim.blade_y2 =
      StrToOptDouble(values[static_cast<int16_t>(SimColumn::kBladeY2)]);
  sim.ii_lateral =
      StrToOptDouble(values[static_cast<int16_t>(SimColumn::kIiLateral)]);
  sim.ii_longitudinal =
      StrToOptDouble(values[static_cast<int16_t>(SimColumn::kIiLongitudinal)]);
  sim.ii_vertical =
      StrToOptDouble(values[static_cast<int16_t>(SimColumn::kIiVertical)]);
  sim.kvp = StrToOptDouble(values[static_cast<int16_t>(SimColumn::kKvp)]);
  sim.ma = StrToOptDouble(values[static_cast<int16_t>(SimColumn::kMa)]);
  sim.seconds =
      StrToOptDouble(values[static_cast<int16_t>(SimColumn::kSeconds)]);
  sim.crc = std::stoi(values[static_cast<int16_t>(SimColumn::kCrc)]);
  return 0;
}

auto ParseField(Field& field, std::vector<std::string>&& values) -> int {
  auto size = values.size();
  constexpr auto n_col = 52;
  if (size != n_col) {
    spdlog::error("expected_ {} columns in this line [actual={}]", n_col, size);
    return 1;
  }
  if (values[static_cast<int16_t>(FieldColumn::kKeyword)] != "FIELD_DEF") {
    spdlog::error("expected_ FIELD_DEF as an identifier for the CSV line");
    return 2;
  }
  field.rx_site_name = values[static_cast<int16_t>(FieldColumn::kRxSiteName)];
  field.field_name = values[static_cast<int16_t>(FieldColumn::kFieldName)];
  field.field_id = values[static_cast<int16_t>(FieldColumn::kFieldId)];
  field.field_note = values[static_cast<int16_t>(FieldColumn::kFieldNote)];
  field.field_dose =
      StrToOptDouble(values[static_cast<int16_t>(FieldColumn::kFieldDose)]);
  field.field_monitor_units = StrToOptDouble(
      values[static_cast<int16_t>(FieldColumn::kFieldMonitorUnits)]);
  field.wedge_monitor_units = StrToOptDouble(
      values[static_cast<int16_t>(FieldColumn::kWedgeMonitorUnits)]);
  field.treatment_machine =
      values[static_cast<int16_t>(FieldColumn::kTreatmentMachine)];
  field.treatment_type =
      values[static_cast<int16_t>(FieldColumn::kTreatmentType)];
  field.modality = values[static_cast<int16_t>(FieldColumn::kModality)];
  field.energy =
      StrToOptDouble(values[static_cast<int16_t>(FieldColumn::kEnergy)]);
  field.time = values[static_cast<int16_t>(FieldColumn::kTime)];
  field.dose_rate =
      StrToOptDouble(values[static_cast<int16_t>(FieldColumn::kDoseRate)]);
  field.sad = StrToOptDouble(values[static_cast<int16_t>(FieldColumn::kSad)]);
  field.ssd = StrToOptDouble(values[static_cast<int16_t>(FieldColumn::kSsd)]);
  field.gantry_angle =
      StrToOptDouble(values[static_cast<int16_t>(FieldColumn::kGantryAngle)]);
  field.collimator_angle = StrToOptDouble(
      values[static_cast<int16_t>(FieldColumn::kCollimatorAngle)]);
  field.field_x_mode = values[static_cast<int16_t>(FieldColumn::kFieldXMode)];
  field.field_x =
      StrToOptDouble(values[static_cast<int16_t>(FieldColumn::kFieldX)]);
  field.collimator_x1 =
      StrToOptDouble(values[static_cast<int16_t>(FieldColumn::kCollimatorX1)]);
  field.collimator_x2 =
      StrToOptDouble(values[static_cast<int16_t>(FieldColumn::kCollimatorX2)]);
  field.field_y_mode = values[static_cast<int16_t>(FieldColumn::kFieldYMode)];
  field.field_y =
      StrToOptDouble(values[static_cast<int16_t>(FieldColumn::kFieldY)]);
  field.collimator_y1 =
      StrToOptDouble(values[static_cast<int16_t>(FieldColumn::kCollimatorY1)]);
  field.collimator_y2 =
      StrToOptDouble(values[static_cast<int16_t>(FieldColumn::kCollimatorY2)]);
  field.couch_vertical =
      StrToOptDouble(values[static_cast<int16_t>(FieldColumn::kCouchVertical)]);
  field.couch_lateral =
      StrToOptDouble(values[static_cast<int16_t>(FieldColumn::kCouchLateral)]);
  field.couch_longitudinal = StrToOptDouble(
      values[static_cast<int16_t>(FieldColumn::kCouchLongitudinal)]);
  field.couch_angle =
      StrToOptDouble(values[static_cast<int16_t>(FieldColumn::kCouchAngle)]);
  field.couch_pedestal =
      StrToOptDouble(values[static_cast<int16_t>(FieldColumn::kCouchPedestal)]);
  field.tolerance_table =
      values[static_cast<int16_t>(FieldColumn::kToleranceTable)];
  field.arc_direction =
      values[static_cast<int16_t>(FieldColumn::kArcDirection)];
  field.arc_start_angle =
      StrToOptDouble(values[static_cast<int16_t>(FieldColumn::kArcStartAngle)]);
  field.arc_stop_angle =
      StrToOptDouble(values[static_cast<int16_t>(FieldColumn::kArcStopAngle)]);
  field.arc_mu_degree =
      StrToOptDouble(values[static_cast<int16_t>(FieldColumn::kArcMuDegree)]);
  field.wedge = values[static_cast<int16_t>(FieldColumn::kWedge)];
  field.dynamic_wedge =
      values[static_cast<int16_t>(FieldColumn::kDynamicWedge)];
  field.block = values[static_cast<int16_t>(FieldColumn::kBlock)];
  field.compensator = values[static_cast<int16_t>(FieldColumn::kCompensator)];
  field.e_applicator = values[static_cast<int16_t>(FieldColumn::kEApplicator)];
  field.e_field_def_aperture =
      values[static_cast<int16_t>(FieldColumn::kEFieldDefAperture)];
  field.bolus = values[static_cast<int16_t>(FieldColumn::kBolus)];
  field.portfilm_mu_open = StrToOptDouble(
      values[static_cast<int16_t>(FieldColumn::kPortfilmMuOpen)]);
  field.portfilm_coeff_open = StrToOptDouble(
      values[static_cast<int16_t>(FieldColumn::kPortfilmCoeffOpen)]);
  field.portfilm_delta_open = StrToOptDouble(
      values[static_cast<int16_t>(FieldColumn::kPortfilmDeltaOpen)]);
  field.portfilm_mu_treat = StrToOptDouble(
      values[static_cast<int16_t>(FieldColumn::kPortfilmMuTreat)]);
  field.portfilm_coeff_treat = StrToOptDouble(
      values[static_cast<int16_t>(FieldColumn::kPortfilmCoeffTreat)]);
  field.isocenter_position_x = StrToOptDouble(
      values[static_cast<int16_t>(FieldColumn::kIsocenterPositionX)]);
  field.isocenter_position_y = StrToOptDouble(
      values[static_cast<int16_t>(FieldColumn::kIsocenterPositionY)]);
  field.isocenter_position_z = StrToOptDouble(
      values[static_cast<int16_t>(FieldColumn::kIsocenterPositionZ)]);
  field.crc = std::stoi(values[static_cast<int16_t>(FieldColumn::kCrc)]);
  return 0;
}

auto ParseExtendedField(ExtendedField& field, std::vector<std::string>&& values)
    -> int {
  auto size = values.size();
  constexpr auto n_col = 12;
  if (size != n_col) {
    spdlog::error("expected_ {} columns in this line [actual={}]", n_col, size);
    return 1;
  }
  if (values[static_cast<int16_t>(ExtendedFieldColumn::kKeyword)] !=
      "EXTENDED_FIELD_DEF") {
    spdlog::error(
        "expected_ EXTENDED_FIELD_DEF as an identifier for the CSV line");
    return 2;
  }
  field.field_id = values[static_cast<int16_t>(ExtendedFieldColumn::kFieldId)];
  field.original_plan_uid =
      values[static_cast<int16_t>(ExtendedFieldColumn::kOriginalPlanUid)];
  field.original_beam_number =
      values[static_cast<int16_t>(ExtendedFieldColumn::kOriginalBeamNumber)];
  field.original_beam_name =
      values[static_cast<int16_t>(ExtendedFieldColumn::kOriginalBeamName)];
  field.is_fff = values[static_cast<int16_t>(ExtendedFieldColumn::kIsFff)];
  field.accessory_code =
      values[static_cast<int16_t>(ExtendedFieldColumn::kAccessoryCode)];
  field.accessory_type =
      values[static_cast<int16_t>(ExtendedFieldColumn::kAccessoryType)];
  field.high_dose_authorization =
      values[static_cast<int16_t>(ExtendedFieldColumn::kHighDoseAuthorization)];
  field.referenced_rt_plan_uid =
      values[static_cast<int16_t>(ExtendedFieldColumn::kReferencedRtPlanUid)];
  field.rt_plan_relationship =
      values[static_cast<int16_t>(ExtendedFieldColumn::kRtPlanRelationShip)];
  field.crc =
      std::stoi(values[static_cast<int16_t>(ExtendedFieldColumn::kCrc)]);
  return 0;
}

auto ParseControlPoint(ControlPoint& cp, std::vector<std::string>&& values)
    -> int {
  auto size = values.size();
  constexpr auto n_col = 236;
  if (size != n_col) {
    spdlog::error("expected_ {} columns in this line [actual={}]", n_col, size);
    return 1;
  }
  if (values[static_cast<int16_t>(ControlPointColumn::kKeyword)] !=
      "CONTROL_PT_DEF") {
    spdlog::error("expected_ CONTROL_PT_DEF as an identifier for the CSV line");
    return 2;
  }
  cp.field_id = values[static_cast<int16_t>(ControlPointColumn::kFieldId)];
  cp.mlc_type = values[static_cast<int16_t>(ControlPointColumn::kMlcType)];
  cp.mlc_leaves =
      std::stoi(values[static_cast<int16_t>(ControlPointColumn::kMlcLeaves)]);
  cp.total_control_points = std::stoi(
      values[static_cast<int16_t>(ControlPointColumn::kTotalControlPoints)]);
  cp.control_pt_number = std::stoi(
      values[static_cast<int16_t>(ControlPointColumn::kControlPtNumber)]);
  {
    const auto mu_convention =
        values[static_cast<int16_t>(ControlPointColumn::kMuConvention)];
    if (mu_convention == "1") {
      cp.mu_convention = MuConvention::fractional;
    } else if (mu_convention == "2") {
      cp.mu_convention = MuConvention::absolute_centi_mu;
    } else {
      spdlog::error(
          "Unsupported MU convention: {}",
          values[static_cast<int16_t>(ControlPointColumn::kMuConvention)]);
      return 3;
    }
  }
  cp.monitor_units = std::stod(
      values[static_cast<int16_t>(ControlPointColumn::kMonitorUnits)]);
  {
    const auto wedge_position =
        values[static_cast<int16_t>(ControlPointColumn::kWedgePosition)];
    if (wedge_position == "1") {
      cp.wedge_position = WedgePosition::in;
    } else {
      cp.wedge_position = WedgePosition::out;
    }
  }
  cp.energy =
      std::stod(values[static_cast<int16_t>(ControlPointColumn::kEnergy)]);
  cp.dose_rate =
      std::stod(values[static_cast<int16_t>(ControlPointColumn::kDoseRate)]);
  cp.ssd =
      StrToOptDouble(values[static_cast<int16_t>(ControlPointColumn::kSsd)]);
  {
    const auto scale_convention = std::stoi(
        values[static_cast<int16_t>(ControlPointColumn::kScaleConvention)]);
    if (scale_convention == 1) {
      cp.scale_convention = ScaleConvention::native;
    } else if (scale_convention == 2) {
      cp.scale_convention = ScaleConvention::iec;
    } else {
      spdlog::error(
          "Unsupported Scale_Convention: {}",
          values[static_cast<int16_t>(ControlPointColumn::kScaleConvention)]);
      return 4;
    }
  }
  cp.gantry_angle =
      std::stod(values[static_cast<int16_t>(ControlPointColumn::kGantryAngle)]);
  cp.gantry_dir = StrToRotationDirection(
      values[static_cast<int16_t>(ControlPointColumn::kGantryDir)]);
  cp.collimator_angle = std::stod(
      values[static_cast<int16_t>(ControlPointColumn::kCollimatorAngle)]);
  cp.collimator_dir = StrToRotationDirection(
      values[static_cast<int16_t>(ControlPointColumn::kCollimatorDir)]);
  cp.field_x_mode =
      values[static_cast<int16_t>(ControlPointColumn::kFieldXMode)];
  cp.field_x =
      StrToOptDouble(values[static_cast<int16_t>(ControlPointColumn::kFieldX)]);
  cp.collimator_x1 = StrToOptDouble(
      values[static_cast<int16_t>(ControlPointColumn::kCollimatorX1)]);
  cp.collimator_x2 = StrToOptDouble(
      values[static_cast<int16_t>(ControlPointColumn::kCollimatorX2)]);
  cp.field_y_mode =
      values[static_cast<int16_t>(ControlPointColumn::kFieldYMode)];
  cp.field_y =
      StrToOptDouble(values[static_cast<int16_t>(ControlPointColumn::kFieldY)]);
  cp.collimator_y1 = StrToOptDouble(
      values[static_cast<int16_t>(ControlPointColumn::kCollimatorY1)]);
  cp.collimator_y2 = StrToOptDouble(
      values[static_cast<int16_t>(ControlPointColumn::kCollimatorY2)]);
  cp.couch_vertical = StrToOptDouble(
      values[static_cast<int16_t>(ControlPointColumn::kCouchVertical)]);
  cp.couch_lateral = StrToOptDouble(
      values[static_cast<int16_t>(ControlPointColumn::kCouchLateral)]);
  cp.couch_longitudinal = StrToOptDouble(
      values[static_cast<int16_t>(ControlPointColumn::kCouchLongitudinal)]);
  cp.couch_angle = StrToOptDouble(
      values[static_cast<int16_t>(ControlPointColumn::kCouchAngle)]);
  cp.couch_dir = StrToRotationDirection(
      values[static_cast<int16_t>(ControlPointColumn::kCouchDir)]);
  cp.couch_pedestal = StrToOptDouble(
      values[static_cast<int16_t>(ControlPointColumn::kCouchPedestal)]);
  cp.couch_ped_dir = StrToRotationDirection(
      values[static_cast<int16_t>(ControlPointColumn::kCouchPedDir)]);
  cp.isocenter_position_x = StrToOptDouble(
      values[static_cast<int16_t>(ControlPointColumn::kIsocenterPositionX)]);
  cp.isocenter_position_y = StrToOptDouble(
      values[static_cast<int16_t>(ControlPointColumn::kIsocenterPositionY)]);
  cp.isocenter_position_z = StrToOptDouble(
      values[static_cast<int16_t>(ControlPointColumn::kIsocenterPositionZ)]);
  if (cp.mlc_leaves > ControlPoint::max_lp) {
    throw std::logic_error(
        fmt::format("Number of MLC leaf pairs [{}] exceeds the maximum number "
                    "of leaf pairs [{}]",
                    cp.mlc_leaves, ControlPoint::max_lp));
  }
  // allocate the memory upfront to avoid unnecessary memory allocations
  if (cp.mlc_leaves > 0) {
    cp.mlc_a.resize(cp.mlc_leaves);
    cp.mlc_b.resize(cp.mlc_leaves);
  } else {
    cp.mlc_a.clear();
    cp.mlc_b.clear();
  }
  for (int32_t i{0}; i < cp.mlc_leaves; ++i) {
    cp.mlc_a[i] =
        std::stod(values[static_cast<int16_t>(ControlPointColumn::kMlcA) + i]);
  }
  for (int32_t i{0}; i < cp.mlc_leaves; ++i) {
    cp.mlc_b[i] =
        std::stod(values[static_cast<int16_t>(ControlPointColumn::kMlcB) + i]);
  }
  cp.crc = std::stoi(values[static_cast<int16_t>(ControlPointColumn::kCrc)]);
  return 0;
}

}  // namespace details

}  // namespace rtp::connect::tools::core
