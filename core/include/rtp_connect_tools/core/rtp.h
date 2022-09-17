#ifndef RTP_CONNECT_TOOLS_CORE_RTP_H
#define RTP_CONNECT_TOOLS_CORE_RTP_H

#include <vector>
#include <optional>
#include <string>

namespace rtp::connect::tools::core {

class Plan {
 public:
  std::string patient_id;
  std::string patient_last_name;
  std::string patient_first_name;
  std::string patient_m_initial;
  std::string plan_id;
  std::string date;
  std::string time;
  std::string course_id;
  std::string diagnosis;
  std::string md_last_name;
  std::string md_first_name;
  std::string md_m_initial;
  std::string md_approve_last_name;
  std::string md_approve_first_name;
  std::string md_approve_m_initial;
  std::string phy_approve_last_name;
  std::string phy_approve_first_name;
  std::string phy_approve_m_initial;
  std::string author_last_name;
  std::string author_first_name;
  std::string author_m_initial;
  std::string rtp_mfg;
  std::string rtp_model;
  std::string rtp_version;
  std::string rtp_if_protocol;
  std::string rtp_if_version;
  int32_t crc;
};

enum class PlanColumn : int16_t {
  kKeyword = 0,
  kPatientId = 1,
  kPatientLastName = 2,
  kPatientFirstName = 3,
  kPatientMInitial = 4,
  kPlanId = 5,
  kDate = 6,
  kTime = 7,
  kCourseId = 8,
  kDiagnosis = 9,
  kMDLastName = 10,
  kMDFirstName = 11,
  kMDMInitial = 12,
  kMDApproveLName = 13,
  kMDApproveFName = 14,
  kMDApproveMInitial = 15,
  kPhyApproveLName = 16,
  kPhyApproveFName = 17,
  kPhyApproveMInitial = 18,
  kAuthorLName = 19,
  kAuthorFName = 20,
  kAuthorMInitial = 21,
  kRtpMfg = 22,
  kRtpModel = 23,
  kRtpVersion = 24,
  kRtpIfProtocol = 25,
  kRtpIfVersion = 26,
  kCrc = 27,
};

class ExtendedPlan {
 public:
  std::string encoding;
  std::string fullname;
  std::string patient_comments;
  int32_t crc;
};

enum class ExtendedPlanColumn : uint8_t {
  kKeyword = 0,
  kEncoding = 1,
  kFullname = 2,
  kPatientComments = 3,
  kCrc = 4
};

class Rx {
 public:
  int32_t course_id{0};
  std::string course_name;
  std::string technique;
  std::string modality;
  std::string dose_spec;
  std::string rx_depth;
  double total_dose{0.0};
  double fraction_dose{0.0};
  std::string pattern;
  std::string rx_note;
  int32_t number_of_fields{0};
  int32_t crc{0};
};

enum class RxColumn : int16_t {
  kKeyword = 0,
  kCourseId = 1,
  kCourseName = 2,
  kTechnique = 3,
  kModality = 4,
  kDoseSpec = 5,
  kRxDepth = 6,
  kDoseTTL = 7,
  kDoseTx = 8,
  kPattern = 9,
  kRxNote = 10,
  kNumberOfFields = 11,
  kCrc = 12,
};

class SiteSetup {
 public:
  std::string rx_site_name;
  std::string patient_orientation;
  std::string treatment_machine;
  std::string tolerance_table;
  std::optional<double> isocenter_x{};
  std::optional<double> isocenter_y{};
  std::optional<double> isocenter_z{};
  std::string structure_set_uid;
  std::string frame_of_reference_uid;
  std::optional<double> couch_vertical{};
  std::optional<double> couch_lateral{};
  std::optional<double> couch_longitudinal{};
  std::optional<double> couch_angle{};
  std::optional<double> couch_pedestal{};
  std::optional<double> table_top_vert_displacement{};
  std::optional<double> table_top_long_displacement{};
  std::optional<double> table_top_lat_displacement{};
  std::string mrl_coil_name;
  std::optional<int32_t> mrl_coil_index;
  std::string couch_reference;
  std::optional<int32_t> couch_reference_index;
  std::string respiratory_motion_compensation_technique;
  std::string respiratory_signal_source;
  int32_t crc{0};
};

enum class SiteSetupColumn : int16_t {
  kKeyword = 0,
  kRxSiteName = 1,
  kPatientOrientation = 2,
  kTreatmentMachine = 3,
  kToleranceTable = 4,
  kIsocenterPositionX = 5,
  kIsocenterPositionY = 6,
  kIsocenterPositionZ = 7,
  kStructureSetUid = 8,
  kFrameOfReferenceUid = 9,
  kCouchVertical = 10,
  kCouchLateral = 11,
  kCouchLongitudinal = 12,
  kCouchAngle = 13,
  kCouchPedestal = 14,
  kTableTopVertDisplacement = 15,
  kTableTopLongDisplacement = 16,
  kTableTopLatDisplacement = 17,
  kMrlCoilName = 18,
  kMrlCoilIndex = 19,
  kCouchReference = 20,
  kCouchReferenceIndex = 21,
  kRespiratoryMotionCompensationTechnique = 22,
  kRespiratorySignalSource = 23,
  kCrc = 24
};

class Sim {
 public:
  std::string rx_site_name;
  std::string field_name;
  std::string field_id;
  std::string field_note;
  std::string treatment_machine;
  double gantry_angle{0.0};
  double collimator_angle{0.0};
  std::string field_x_mode{};
  std::optional<double> field_x{};
  std::optional<double> collimator_x1{};
  std::optional<double> collimator_x2{};
  std::string field_y_mode{};
  std::optional<double> field_y{};
  std::optional<double> collimator_y1{};
  std::optional<double> collimator_y2{};
  std::optional<double> couch_vertical{};
  std::optional<double> couch_lateral{};
  std::optional<double> couch_longitudinal{};
  std::optional<double> couch_angle{};
  std::optional<double> couch_pedestal{};
  std::optional<double> sad{};
  std::string ap_separation;
  std::string pa_separation;
  std::string lateral_separation;
  std::string tangential_separation;
  std::string other_label_1;
  std::optional<double> ssd_1{};
  std::optional<double> sfd_1{};
  std::string other_label_2;
  std::string other_measurement_1;
  std::string other_measurement_2;
  std::string other_label_3;
  std::string other_measurement_3;
  std::string other_measurement_4;
  std::string other_label_4;
  std::string other_measurement_5;
  std::string other_measurement_6;
  std::string blade_x_mode;
  std::optional<double> blade_x{};
  std::optional<double> blade_x1{};
  std::optional<double> blade_x2{};
  std::string blade_y_mode;
  std::optional<double> blade_y{};
  std::optional<double> blade_y1{};
  std::optional<double> blade_y2{};
  std::optional<double> ii_lateral{};
  std::optional<double> ii_longitudinal{};
  std::optional<double> ii_vertical{};
  std::optional<double> kvp{};
  std::optional<double> ma{};
  std::optional<double> seconds{};
  int32_t crc{};
};

enum class SimColumn {
  kKeyword = 0,
  kRxSiteName = 1,
  kFieldName = 2,
  kFieldId = 3,
  kFieldNote = 4,
  kTreatmentMachine = 5,
  kGantryAngle = 6,
  kCollimatorAngle = 7,
  kFieldXMode = 8,
  kFieldX = 9,
  kCollimatorX1 = 10,
  kCollimatorX2 = 11,
  kFieldYMode = 12,
  kFieldY = 13,
  kCollimatorY1 = 14,
  kCollimatorY2 = 15,
  kCouchVertical = 16,
  kCouchLateral = 17,
  kCouchLongitudinal = 18,
  kCouchAngle = 19,
  kCouchPedestal = 20,
  kSad = 21,
  kApSeparation = 22,
  kPaSeparation = 23,
  kLateralSeparation = 24,
  kTangentialSeparation = 25,
  kOtherLabel1 = 26,
  kSsd1 = 27,
  kSfd1 = 28,
  kOtherLabel2 = 29,
  kOtherMeasurement1 = 30,
  kOtherMeasurement2 = 31,
  kOtherLabel3 = 32,
  kOtherMeasurement3 = 33,
  kOtherMeasurement4 = 34,
  kOtherLabel4 = 35,
  kOtherMeasurement5 = 36,
  kOtherMeasurement6 = 37,
  kBladeXMode = 38,
  kBladeX = 39,
  kBladeX1 = 40,
  kBladeX2 = 41,
  kBladeYMode = 42,
  kBladeY = 43,
  kBladeY1 = 44,
  kBladeY2 = 45,
  kIiLateral = 46,
  kIiLongitudinal = 47,
  kIiVertical = 48,
  kKvp = 49,
  kMa = 50,
  kSeconds = 51,
  kCrc = 52
};

class Field {
 public:
  std::string rx_site_name;
  std::string field_name;
  std::string field_id;
  std::string field_note;
  std::optional<double> field_dose{};
  std::optional<double> field_monitor_units{};
  std::optional<double> wedge_monitor_units{};
  std::string treatment_machine;
  std::string treatment_type;
  std::string modality;
  std::optional<double> energy{0.0};
  std::string time;
  std::optional<double> dose_rate{};
  std::optional<double> sad{};
  std::optional<double> ssd{};
  std::optional<double> gantry_angle{};
  std::optional<double> collimator_angle{};
  std::string field_x_mode;
  std::optional<double> field_x{};
  std::optional<double> collimator_x1{};
  std::optional<double> collimator_x2{};
  std::string field_y_mode;
  std::optional<double> field_y{};
  std::optional<double> collimator_y1{};
  std::optional<double> collimator_y2{};
  std::optional<double> couch_vertical{};
  std::optional<double> couch_lateral{};
  std::optional<double> couch_longitudinal{};
  std::optional<double> couch_angle{};
  std::optional<double> couch_pedestal{};
  std::string tolerance_table;
  std::string arc_direction;
  std::optional<double> arc_start_angle{};
  std::optional<double> arc_stop_angle{};
  std::optional<double> arc_mu_degree{};
  std::string wedge;
  std::string dynamic_wedge;
  std::string block;
  std::string compensator;
  std::string e_applicator;
  std::string e_field_def_aperture;
  std::string bolus;
  std::optional<double> portfilm_mu_open{};
  std::optional<double> portfilm_coeff_open{};
  std::optional<double> portfilm_delta_open{};
  std::optional<double> portfilm_mu_treat{};
  std::optional<double> portfilm_coeff_treat{};
  std::optional<double> isocenter_position_x{};
  std::optional<double> isocenter_position_y{};
  std::optional<double> isocenter_position_z{};
  int32_t crc;
};

enum class FieldColumn {
  kKeyword = 0,
  kRxSiteName = 1,
  kFieldName = 2,
  kFieldId = 3,
  kFieldNote = 4,
  kFieldDose = 5,
  kFieldMonitorUnits = 6,
  kWedgeMonitorUnits = 7,
  kTreatmentMachine = 8,
  kTreatmentType = 9,
  kModality = 10,
  kEnergy = 11,
  kTime = 12,
  kDoseRate = 13,
  kSad = 14,
  kSsd = 15,
  kGantryAngle = 16,
  kCollimatorAngle = 17,
  kFieldXMode = 18,
  kFieldX = 19,
  kCollimatorX1 = 20,
  kCollimatorX2 = 21,
  kFieldYMode = 22,
  kFieldY = 23,
  kCollimatorY1 = 24,
  kCollimatorY2 = 25,
  kCouchVertical = 26,
  kCouchLateral = 27,
  kCouchLongitudinal = 28,
  kCouchAngle = 29,
  kCouchPedestal = 30,
  kToleranceTable = 31,
  kArcDirection = 32,
  kArcStartAngle = 33,
  kArcStopAngle = 34,
  kArcMuDegree = 35,
  kWedge = 36,
  kDynamicWedge = 37,
  kBlock = 38,
  kCompensator = 39,
  kEApplicator = 40,
  kEFieldDefAperture = 41,
  kBolus = 42,
  kPortfilmMuOpen = 43,
  kPortfilmCoeffOpen = 44,
  kPortfilmDeltaOpen = 45,
  kPortfilmMuTreat = 46,
  kPortfilmCoeffTreat = 47,
  kIsocenterPositionX = 48,
  kIsocenterPositionY = 49,
  kIsocenterPositionZ = 50,
  kCrc = 51
};

class ExtendedField {
 public:
  std::string field_id;
  std::string original_plan_uid;
  std::string original_beam_number;
  std::string original_beam_name;
  std::string is_fff;
  std::string accessory_code;
  std::string accessory_type;
  std::string high_dose_authorization;
  std::string referenced_rt_plan_uid;
  std::string rt_plan_relationship;
  int crc{0};
};

enum class ExtendedFieldColumn {
  kKeyword = 0,
  kFieldId = 1,
  kOriginalPlanUid = 2,
  kOriginalBeamNumber = 3,
  kOriginalBeamName = 4,
  kIsFff = 5,
  kAccessoryCode = 6,
  kAccessoryType = 7,
  kHighDoseAuthorization = 8,
  kReferencedRtPlanUid = 9,
  kRtPlanRelationShip = 10,
  kCrc = 11
};

enum class MuConvention : uint8_t { fractional = 1, absolute_centi_mu = 2 };

enum class WedgePosition : uint8_t {
  out = 0,
  in = 1,
};

enum class ScaleConvention : uint8_t { native = 1, iec = 2 };

enum class RotationDirection : uint8_t { none, cw, ccw };

class ControlPoint {
 public:
  constexpr static uint16_t max_lp{100};

  std::string field_id;
  std::string mlc_type;
  int32_t mlc_leaves{0};
  int32_t total_control_points{0};
  int32_t control_pt_number{0};
  MuConvention mu_convention{MuConvention::fractional};
  double monitor_units{0};
  WedgePosition wedge_position{WedgePosition::out};
  double energy{0.0};
  double dose_rate{0.0};
  std::optional<double> ssd{};
  ScaleConvention scale_convention{ScaleConvention::iec};
  double gantry_angle{0.0};
  RotationDirection gantry_dir{RotationDirection::none};
  double collimator_angle{0.0};
  RotationDirection collimator_dir{RotationDirection::none};
  std::string field_x_mode;
  std::optional<double> field_x{};
  std::optional<double> collimator_x1{};
  std::optional<double> collimator_x2{};
  std::string field_y_mode;
  std::optional<double> field_y{};
  std::optional<double> collimator_y1{};
  std::optional<double> collimator_y2{};
  std::optional<double> couch_vertical{};
  std::optional<double> couch_lateral{};
  std::optional<double> couch_longitudinal{};
  std::optional<double> couch_angle{};
  RotationDirection couch_dir{};
  std::optional<double> couch_pedestal{};
  RotationDirection couch_ped_dir{};
  std::optional<double> isocenter_position_x{};
  std::optional<double> isocenter_position_y{};
  std::optional<double> isocenter_position_z{};
  std::vector<double> mlc_a{};
  std::vector<double> mlc_b{};
  int32_t crc;
};

enum class ControlPointColumn {
  kKeyword = 0,
  kFieldId = 1,
  kMlcType = 2,
  kMlcLeaves = 3,
  kTotalControlPoints = 4,
  kControlPtNumber = 5,
  kMuConvention = 6,
  kMonitorUnits = 7,
  kWedgePosition = 8,
  kEnergy = 9,
  kDoseRate = 10,
  kSsd = 11,
  kScaleConvention = 12,
  kGantryAngle = 13,
  kGantryDir = 14,
  kCollimatorAngle = 15,
  kCollimatorDir = 16,
  kFieldXMode = 17,
  kFieldX = 18,
  kCollimatorX1 = 19,
  kCollimatorX2 = 20,
  kFieldYMode = 21,
  kFieldY = 22,
  kCollimatorY1 = 23,
  kCollimatorY2 = 24,
  kCouchVertical = 25,
  kCouchLateral = 26,
  kCouchLongitudinal = 27,
  kCouchAngle = 28,
  kCouchDir = 29,
  kCouchPedestal = 30,
  kCouchPedDir = 31,
  kIsocenterPositionX = 32,
  kIsocenterPositionY = 33,
  kIsocenterPositionZ = 34,
  kMlcA = 35,
  kMlcB = 135,
  kCrc = 235,
};

class Rtp {
 public:
  Plan plan_def;
  Rx rx_def;
  SiteSetup site_setup;
  Sim sim;
  std::vector<Field> fields;
  std::vector<ExtendedField> extended_fields;
  std::vector<ControlPoint> control_points;
};

}  // namespace rtp::connect::tools::core

#endif  // RTP_CONNECT_TOOLS_CORE_RTP_H
