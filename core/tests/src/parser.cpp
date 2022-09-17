#include "rtp_connect_tools/core/rtp.h"
#include "rtp_connect_tools/core/parser.h"

#include <catch2/catch_test_macros.hpp>

namespace core = rtp::connect::tools::core;

TEST_CASE("StrToOptInt32") {
  REQUIRE(std::optional<int32_t>{} == core::details::StrToOptInt32(""));
  REQUIRE(std::optional<int32_t>{5} == core::details::StrToOptInt32("5"));
}

TEST_CASE("StrToOptDouble") {
  REQUIRE(std::optional<double>{} == core::details::StrToOptDouble(""));
  REQUIRE(std::optional<double>{5.0} == core::details::StrToOptDouble("5.0"));
}

TEST_CASE("ParsePlan") {
  std::vector<std::string> values{{"PLAN_DEF"},
                                  {"Patient_ID"},
                                  {"Patient_Last_Name"},
                                  {"Patient_First_Name"},
                                  {"Patient_MInitial"},
                                  {"Plan_ID"},
                                  {"Plan_Date"},
                                  {"Plan_Time"},
                                  {"Course_ID"},
                                  {"Diagnosis"},
                                  {"MD_Last_Name"},
                                  {"MD_First_Name"},
                                  {"MD_MInitial"},
                                  {"MD_Approve_LName"},
                                  {"MD_Approve_FName"},
                                  {"MD_Approve_MInitial"},
                                  {"Phy_Approve_LName"},
                                  {"Phy_Approve_FName"},
                                  {"Phy_Approve_MInitial"},
                                  {"Author_Last_Name"},
                                  {"Author_First_Name"},
                                  {"Author_MInitial"},
                                  {"RTP_Mfg"},
                                  {"RTP_Model"},
                                  {"RTP_Version"},
                                  {"RTP_IF_Protocol"},
                                  {"RTP_IF_Version"},
                                  {"1234"}};
  core::Plan plan_def;
  REQUIRE(core::details::ParsePlan(plan_def, std::move(values)) == 0);
  REQUIRE("Patient_ID" == plan_def.patient_id);
  REQUIRE("Patient_Last_Name" == plan_def.patient_last_name);
  REQUIRE("Patient_First_Name" == plan_def.patient_first_name);
  REQUIRE("Patient_MInitial" == plan_def.patient_m_initial);
  REQUIRE("Plan_ID" == plan_def.plan_id);
  REQUIRE("Plan_Date" == plan_def.date);
  REQUIRE("Plan_Time" == plan_def.time);
  REQUIRE("Course_ID" == plan_def.course_id);
  REQUIRE("Diagnosis" == plan_def.diagnosis);
  REQUIRE("MD_Last_Name" == plan_def.md_last_name);
  REQUIRE("MD_First_Name" == plan_def.md_first_name);
  REQUIRE("MD_MInitial" == plan_def.md_m_initial);
  REQUIRE("MD_Approve_LName" == plan_def.md_approve_last_name);
  REQUIRE("MD_Approve_FName" == plan_def.md_approve_first_name);
  REQUIRE("MD_Approve_MInitial" == plan_def.md_approve_m_initial);
  REQUIRE("Phy_Approve_LName" == plan_def.phy_approve_last_name);
  REQUIRE("Phy_Approve_FName" == plan_def.phy_approve_first_name);
  REQUIRE("Phy_Approve_MInitial" == plan_def.phy_approve_m_initial);
  REQUIRE("Author_Last_Name" == plan_def.author_last_name);
  REQUIRE("Author_First_Name" == plan_def.author_first_name);
  REQUIRE("Author_MInitial" == plan_def.author_m_initial);
  REQUIRE("RTP_Mfg" == plan_def.rtp_mfg);
  REQUIRE("RTP_Model" == plan_def.rtp_model);
  REQUIRE("RTP_Version" == plan_def.rtp_version);
  REQUIRE("RTP_IF_Protocol" == plan_def.rtp_if_protocol);
  REQUIRE("RTP_IF_Version" == plan_def.rtp_if_version);
  REQUIRE(1234 == plan_def.crc);
}

TEST_CASE("ParseRx") {
  std::vector<std::string> values{
      "RX_DEF",    "5",        "Rx_Site_Name", "Technique", "Modality",
      "Dose_Spec", "Rx_Depth", "7000",         "200",       "Pattern",
      "Rx_Note",   "3",        "1234"};
  core::Rx rxd;
  REQUIRE(core::details::ParseRx(rxd, std::move(values)) == 0);
  REQUIRE(5 == rxd.course_id);
  REQUIRE("Rx_Site_Name" == rxd.course_name);
  REQUIRE("Technique" == rxd.technique);
  REQUIRE("Modality" == rxd.modality);
  REQUIRE("Dose_Spec" == rxd.dose_spec);
  REQUIRE("Rx_Depth" == rxd.rx_depth);
  REQUIRE(7000 == rxd.total_dose);
  REQUIRE(200 == rxd.fraction_dose);
  REQUIRE("Pattern" == rxd.pattern);
  REQUIRE("Rx_Note" == rxd.rx_note);
  REQUIRE(3 == rxd.number_of_fields);
  REQUIRE(1234 == rxd.crc);
}

TEST_CASE("ParseSiteSetup") {
  std::vector<std::string> values{"SITE_SETUP_DEF",
                                  "Rx_Site_Name",
                                  "Patient_Orientation",
                                  "Treatment_Machine",
                                  "Tolerance_Table",
                                  "1.0",
                                  "2.0",
                                  "3.0",
                                  "1.200.20",
                                  "1.222.20",
                                  "32.0",
                                  "16.0",
                                  "8.0",
                                  "64.0",
                                  "90.0",
                                  "1.0",
                                  "2.0",
                                  "4.0",
                                  "MRL_COIL_NAME",
                                  "256",
                                  "Couch Reference",
                                  "128",
                                  "Respiratory_Motion_Compensation_Technique",
                                  "Respiratory_Signal_Source",
                                  "19"};
  const std::optional<double> iso_x{1.0};
  const std::optional<double> iso_y{2.0};
  const std::optional<double> iso_z{3.0};
  const std::optional<double> couch_vert{32.0};
  const std::optional<double> couch_lat{16.0};
  const std::optional<double> couch_longitudinal{8.0};
  const std::optional<double> couch_angle{64.0};
  const std::optional<double> couch_pedestal{90.0};
  const std::optional<double> table_top_vert_displacement{1.0};
  const std::optional<double> table_top_long_displacement{2.0};
  const std::optional<double> table_top_lat_displacement{4.0};
  const std::optional<int32_t> mrl_coil_index{256};
  const std::optional<int32_t> couch_reference_index{128};
  const int32_t crc = 19;
  core::SiteSetup site_setup;
  REQUIRE(core::details::ParseSiteSetup(site_setup, std::move(values)) == 0);
  REQUIRE("Rx_Site_Name" == site_setup.rx_site_name);
  REQUIRE("Patient_Orientation" == site_setup.patient_orientation);
  REQUIRE("Treatment_Machine" == site_setup.treatment_machine);
  REQUIRE("Tolerance_Table" == site_setup.tolerance_table);
  REQUIRE(iso_x == site_setup.isocenter_x);
  REQUIRE(iso_y == site_setup.isocenter_y);
  REQUIRE(iso_z == site_setup.isocenter_z);
  REQUIRE("1.200.20" == site_setup.structure_set_uid);
  REQUIRE("1.222.20" == site_setup.frame_of_reference_uid);
  REQUIRE(couch_vert == site_setup.couch_vertical);
  REQUIRE(couch_lat == site_setup.couch_lateral);
  REQUIRE(couch_longitudinal == site_setup.couch_longitudinal);
  REQUIRE(couch_angle == site_setup.couch_angle);
  REQUIRE(couch_pedestal == site_setup.couch_pedestal);
  REQUIRE(table_top_vert_displacement ==
          site_setup.table_top_vert_displacement);
  REQUIRE(table_top_long_displacement ==
          site_setup.table_top_long_displacement);
  REQUIRE(table_top_lat_displacement == site_setup.table_top_lat_displacement);
  REQUIRE("MRL_COIL_NAME" == site_setup.mrl_coil_name);
  REQUIRE(couch_reference_index == site_setup.couch_reference_index);
  REQUIRE("Respiratory_Motion_Compensation_Technique" ==
          site_setup.respiratory_motion_compensation_technique);
  REQUIRE("Respiratory_Signal_Source" == site_setup.respiratory_signal_source);
  REQUIRE(crc == site_setup.crc);
}

TEST_CASE("ParseSim") {
  std::vector<std::string> values{"SIM_DEF",
                                  "Rx_Site_Name",
                                  "Field_Name",
                                  "Field_ID",
                                  "Field_Note",
                                  "Treatment_Machine",
                                  "330.0",
                                  "45.0",
                                  "ASYMX",
                                  "10.0",
                                  "4.0",
                                  "6.0",
                                  "ASYMY",
                                  "20.0",
                                  "12.0",
                                  "8.0",
                                  "18.0",
                                  "-1.0",
                                  "140.0",
                                  "45.0",
                                  "90.0",
                                  "100.0",
                                  "6.0",
                                  "7.0",
                                  "8.0",
                                  "9.0",
                                  "Other_Label_1",
                                  "92.0",
                                  "150.0",
                                  "Other_Label_2",
                                  "Other_Measurement_1",
                                  "Other_Measurement_2",
                                  "Other_Label_3",
                                  "Other_Measurement_3",
                                  "Other_Measurement_4",
                                  "Other_Label_4",
                                  "Other_Measurement_5",
                                  "Other_Measurement_6",
                                  "Blade_x_Mode",
                                  "10.0",
                                  "4.0",
                                  "6.0",
                                  "Blade_y_Mode",
                                  "20.0",
                                  "11.0",
                                  "9.0",
                                  "-1.0",
                                  "-2.0",
                                  "-3.0",
                                  "70.0",
                                  "25.0",
                                  "13.0",
                                  "1234"};
  core::Sim sim;
  REQUIRE(core::details::ParseSim(sim, std::move(values)) == 0);
  REQUIRE("Rx_Site_Name" == sim.rx_site_name);
  REQUIRE("Field_Name" == sim.field_name);
  REQUIRE("Field_ID" == sim.field_id);
  REQUIRE("Field_Note" == sim.field_note);
  REQUIRE("Treatment_Machine" == sim.treatment_machine);
  REQUIRE(330.0 == sim.gantry_angle);
  REQUIRE(45.0 == sim.collimator_angle);
  REQUIRE("ASYMX" == sim.field_x_mode);
  REQUIRE(std::optional<double>{10.0} == sim.field_x);
  REQUIRE(std::optional<double>{4.0} == sim.collimator_x1);
  REQUIRE(std::optional<double>{6.0} == sim.collimator_x2);
  REQUIRE("ASYMY" == sim.field_y_mode);
  REQUIRE(std::optional<double>{20.0} == sim.field_y);
  REQUIRE(std::optional<double>{12.0} == sim.collimator_y1);
  REQUIRE(std::optional<double>{8.0} == sim.collimator_y2);
  REQUIRE(std::optional<double>{18.0} == sim.couch_vertical);
  REQUIRE(std::optional<double>{-1.0} == sim.couch_lateral);
  REQUIRE(std::optional<double>{140.0} == sim.couch_longitudinal);
  REQUIRE(std::optional<double>{45.0} == sim.couch_angle);
  REQUIRE(std::optional<double>{90.0} == sim.couch_pedestal);
  REQUIRE(std::optional<double>{100.0} == sim.sad);
  REQUIRE("6.0" == sim.ap_separation);
  REQUIRE("7.0" == sim.pa_separation);
  REQUIRE("8.0" == sim.lateral_separation);
  REQUIRE("9.0" == sim.tangential_separation);
  REQUIRE("Other_Label_1" == sim.other_label_1);
  REQUIRE(std::optional<double>{92.0} == sim.ssd_1);
  REQUIRE(std::optional<double>{150.0} == sim.sfd_1);
  REQUIRE("Other_Label_2" == sim.other_label_2);
  REQUIRE("Other_Measurement_1" == sim.other_measurement_1);
  REQUIRE("Other_Measurement_2" == sim.other_measurement_2);
  REQUIRE("Other_Label_3" == sim.other_label_3);
  REQUIRE("Other_Measurement_3" == sim.other_measurement_3);
  REQUIRE("Other_Measurement_4" == sim.other_measurement_4);
  REQUIRE("Other_Label_4" == sim.other_label_4);
  REQUIRE("Other_Measurement_5" == sim.other_measurement_5);
  REQUIRE("Other_Measurement_6" == sim.other_measurement_6);
  REQUIRE("Blade_x_Mode" == sim.blade_x_mode);
  REQUIRE(std::optional<double>{10.0} == sim.blade_x);
  REQUIRE(std::optional<double>{4.0} == sim.blade_x1);
  REQUIRE(std::optional<double>{6.0} == sim.blade_x2);
  REQUIRE("Blade_y_Mode" == sim.blade_y_mode);
  REQUIRE(std::optional<double>{20.0} == sim.blade_y);
  REQUIRE(std::optional<double>{11.0} == sim.blade_y1);
  REQUIRE(std::optional<double>{9.0} == sim.blade_y2);
  REQUIRE(std::optional<double>{-1.0} == sim.ii_lateral);
  REQUIRE(std::optional<double>{-2.0} == sim.ii_longitudinal);
  REQUIRE(std::optional<double>{-3.0} == sim.ii_vertical);
  REQUIRE(std::optional<double>{70.0} == sim.kvp);
  REQUIRE(std::optional<double>{25.0} == sim.ma);
  REQUIRE(std::optional<double>{13.0} == sim.seconds);
  REQUIRE(1234 == sim.crc);
}

TEST_CASE("ParseField") {
  std::vector<std::string> values{"FIELD_DEF",
                                  "Rx_Site_Name",
                                  "Field_Name",
                                  "Field_ID",
                                  "Field_Note",
                                  "1000",
                                  "999",
                                  "333",
                                  "Treatment_Machine",
                                  "Treatment_Type",
                                  "Modality",
                                  "6.0",
                                  "132530",
                                  "600",
                                  "100",
                                  "90",
                                  "330",
                                  "45",
                                  "ASYMX",
                                  "10.0",
                                  "6.0",
                                  "4.0",
                                  "ASYMY",
                                  "20.0",
                                  "11.0",
                                  "9.0",
                                  "14.0",
                                  "2.0",
                                  "140.0",
                                  "40.0",
                                  "90.0",
                                  "Tolerance_Table",
                                  "Arc_Direction",
                                  "13.0",
                                  "29.0",
                                  "15.0",
                                  "Wedge",
                                  "Dynamic_Wedge",
                                  "Block",
                                  "Compensator",
                                  "e_Applicator",
                                  "e_Field_Def_Aperture",
                                  "Bolus",
                                  "5.0",
                                  "6.0",
                                  "7.0",
                                  "8.0",
                                  "9.0",
                                  "26.0",
                                  "27.0",
                                  "28.0",
                                  "1234"};
  core::Field field;
  REQUIRE(core::details::ParseField(field, std::move(values)) == 0);
  REQUIRE("Rx_Site_Name" == field.rx_site_name);
  REQUIRE("Field_Name" == field.field_name);
  REQUIRE("Field_ID" == field.field_id);
  REQUIRE("Field_Note" == field.field_note);
  REQUIRE(std::optional<double>{1000.0} == field.field_dose);
  REQUIRE(std::optional<double>{999.0} == field.field_monitor_units);
  REQUIRE(std::optional<double>{333.0} == field.wedge_monitor_units);
  REQUIRE("Treatment_Machine" == field.treatment_machine);
  REQUIRE("Treatment_Type" == field.treatment_type);
  REQUIRE("Modality" == field.modality);
  REQUIRE(std::optional<double>{6.0} == field.energy);
  REQUIRE("132530" == field.time);
  REQUIRE(std::optional<double>{600.0} == field.dose_rate);
  REQUIRE(std::optional<double>{100.0} == field.sad);
  REQUIRE(std::optional<double>{90.0} == field.ssd);
  REQUIRE(std::optional<double>{330.0} == field.gantry_angle);
  REQUIRE(std::optional<double>{45.0} == field.collimator_angle);
  REQUIRE("ASYMX" == field.field_x_mode);
  REQUIRE(std::optional<double>{10} == field.field_x);
  REQUIRE(std::optional<double>{6} == field.collimator_x1);
  REQUIRE(std::optional<double>{4} == field.collimator_x2);
  REQUIRE("ASYMY" == field.field_y_mode);
  REQUIRE(std::optional<double>{20} == field.field_y);
  REQUIRE(std::optional<double>{11} == field.collimator_y1);
  REQUIRE(std::optional<double>{9} == field.collimator_y2);
  REQUIRE(std::optional<double>{14} == field.couch_vertical);
  REQUIRE(std::optional<double>{2} == field.couch_lateral);
  REQUIRE(std::optional<double>{140} == field.couch_longitudinal);
  REQUIRE(std::optional<double>{40} == field.couch_angle);
  REQUIRE(std::optional<double>{90} == field.couch_pedestal);
  REQUIRE("Tolerance_Table" == field.tolerance_table);
  REQUIRE("Arc_Direction" == field.arc_direction);
  REQUIRE(std::optional<double>{13} == field.arc_start_angle);
  REQUIRE(std::optional<double>{29} == field.arc_stop_angle);
  REQUIRE(std::optional<double>{15} == field.arc_mu_degree);
  REQUIRE("Wedge" == field.wedge);
  REQUIRE("Dynamic_Wedge" == field.dynamic_wedge);
  REQUIRE("Block" == field.block);
  REQUIRE("Compensator" == field.compensator);
  REQUIRE("e_Applicator" == field.e_applicator);
  REQUIRE("e_Field_Def_Aperture" == field.e_field_def_aperture);
  REQUIRE("Bolus" == field.bolus);
  REQUIRE(5.0 == field.portfilm_mu_open);
  REQUIRE(6.0 == field.portfilm_coeff_open);
  REQUIRE(7.0 == field.portfilm_delta_open);
  REQUIRE(8.0 == field.portfilm_mu_treat);
  REQUIRE(9.0 == field.portfilm_coeff_treat);
  REQUIRE(std::optional<double>{26.0} == field.isocenter_position_x);
  REQUIRE(std::optional<double>{27.0} == field.isocenter_position_y);
  REQUIRE(std::optional<double>{28.0} == field.isocenter_position_z);
  REQUIRE(1234 == field.crc);
}

TEST_CASE("ParseExtendedField") {
  std::vector<std::string> values{
      "EXTENDED_FIELD_DEF",      "Field ID",
      "Original Plan UID",       "Original Beam Number",
      "Original Beam Name",      "IsFFF",
      "Accessory Code",          "Accessory Type",
      "High Dose Authorization", "Referenced RT Plan UID",
      "RT Plan Relationship",    "1234"};
  core::ExtendedField field;
  REQUIRE(core::details::ParseExtendedField(field, std::move(values)) == 0);
  REQUIRE("Field ID" == field.field_id);
  REQUIRE("Original Plan UID" == field.original_plan_uid);
  REQUIRE("Original Beam Number" == field.original_beam_number);
  REQUIRE("Original Beam Name" == field.original_beam_name);
  REQUIRE("IsFFF" == field.is_fff);
  REQUIRE("Accessory Code" == field.accessory_code);
  REQUIRE("Accessory Type" == field.accessory_type);
  REQUIRE("High Dose Authorization" == field.high_dose_authorization);
  REQUIRE("Referenced RT Plan UID" == field.referenced_rt_plan_uid);
  REQUIRE("RT Plan Relationship" == field.rt_plan_relationship);
  REQUIRE(1234 == field.crc);
}

TEST_CASE("ParseControlPoint") {
  std::vector<std::string> values{"CONTROL_PT_DEF",
                                  "Field ID",
                                  "MLC_Type",
                                  "40",
                                  "5",
                                  "2",
                                  "1",
                                  "999",
                                  "1",
                                  "6.0",
                                  "600.0",
                                  "90.0",
                                  "2",
                                  "330.0",
                                  "CW",
                                  "45.0",
                                  "CCW",
                                  "ASYMX",
                                  "10.0",
                                  "6.0",
                                  "4.0",
                                  "ASYMY",
                                  "20.0",
                                  "11.0",
                                  "9.0",
                                  "13.0",
                                  "14.0",
                                  "15.0",
                                  "16.0",
                                  "CW",
                                  "90.0",
                                  "CCW",
                                  "1.0",
                                  "2.0",
                                  "3.0"};
  for (uint16_t i{0}; i < core::ControlPoint::max_lp * 2; ++i) {
    values.push_back(std::to_string(static_cast<int32_t>(i) + 1));
  }
  values.emplace_back("1234");

  core::ControlPoint cp;
  REQUIRE(core::details::ParseControlPoint(cp, std::move(values)) == 0);
  REQUIRE("Field ID" == cp.field_id);
  REQUIRE("MLC_Type" == cp.mlc_type);
  REQUIRE(40 == cp.mlc_leaves);
  REQUIRE(5 == cp.total_control_points);
  REQUIRE(2 == cp.control_pt_number);
  REQUIRE(core ::MuConvention::fractional == cp.mu_convention);
  REQUIRE(999.0 == cp.monitor_units);
  REQUIRE(core::WedgePosition::in == cp.wedge_position);
  REQUIRE(6.0 == cp.energy);
  REQUIRE(600.0 == cp.dose_rate);
  REQUIRE(std::optional<double>{90.0} == cp.ssd);
  REQUIRE(core::ScaleConvention::iec == cp.scale_convention);
  REQUIRE(std::optional<double>{330.0} == cp.gantry_angle);
  REQUIRE(core::RotationDirection::cw == cp.gantry_dir);
  REQUIRE(std::optional<double>{45.0} == cp.collimator_angle);
  REQUIRE(core::RotationDirection::ccw == cp.collimator_dir);
  REQUIRE("ASYMX" == cp.field_x_mode);
  REQUIRE(std::optional<double>{10.0} == cp.field_x);
  REQUIRE(std::optional<double>{6.0} == cp.collimator_x1);
  REQUIRE(std::optional<double>{4.0} == cp.collimator_x2);
  REQUIRE("ASYMY" == cp.field_y_mode);
  REQUIRE(std::optional<double>{20.0} == cp.field_y);
  REQUIRE(std::optional<double>{11.0} == cp.collimator_y1);
  REQUIRE(std::optional<double>{9.0} == cp.collimator_y2);
  REQUIRE(std::optional<double>{13.0} == cp.couch_vertical);
  REQUIRE(std::optional<double>{14.0} == cp.couch_lateral);
  REQUIRE(std::optional<double>{15.0} == cp.couch_longitudinal);
  REQUIRE(std::optional<double>{16.0} == cp.couch_angle);
  REQUIRE(core::RotationDirection::cw == cp.couch_dir);
  REQUIRE(std::optional<double>{90.0} == cp.couch_pedestal);
  REQUIRE(core::RotationDirection::ccw == cp.couch_ped_dir);
  REQUIRE(std::optional<double>{1.0} == cp.isocenter_position_x);
  REQUIRE(std::optional<double>{2.0} == cp.isocenter_position_y);
  REQUIRE(std::optional<double>{3.0} == cp.isocenter_position_z);

  for (uint32_t i{0}; i < cp.mlc_leaves; ++i) {
    REQUIRE(static_cast<double>(i + 1) == cp.mlc_a[i]);
    REQUIRE(static_cast<double>(i + 101) == cp.mlc_b[i]);
  }
  REQUIRE(1234 == cp.crc);
}