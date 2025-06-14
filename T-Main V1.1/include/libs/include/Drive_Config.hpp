#pragma once

// === External Library Includes ===
#include "libs/include/EZ-Template/drive/drive.hpp"
#include "libs/include/lemlib/chassis/chassis.hpp"
#include "config.hpp"
#include "pros/rotation.hpp"

using namespace CONFIG;  // Namespace from your config.hpp for robot-specific constants

//--------------------------------------//
//           EZ-TEMPLATE SETUP          //
//--------------------------------------//

// EZ-Template Chassis Setup
inline ez::Drive EZchassis = ez::Drive(
    {ezLeftMotors},
    {ezRightMotors},
    IMU,
    Wheel_Diameter,
    Wheel_RPM
);

// Optional tracking wheels (for odometry)
inline ez::tracking_wheel vert_tracker(Vrt1Prt, Vrt1D, Vrt1DTC);
inline ez::tracking_wheel vert_tracker2(Vrt2Prt, Vrt2D, Vrt2DTC);
inline ez::tracking_wheel horiz_tracker(Hr1Prt, Hr1D, Hr1DTC);
inline ez::tracking_wheel horiz_tracker2(Hr2Prt, Hr2D, Hr2DTC);

// Configure EZ-Template PID & motion settings
inline void default_constants() {
    // PID constants for different motion types
    EZchassis.pid_drive_constants_set(lin_P, lin_I, lin_D, lin_Start_I);
    EZchassis.pid_heading_constants_set(hd_P, hd_I, hd_D, hd_Start_I);
    EZchassis.pid_turn_constants_set(trn_P, trn_I, trn_D, trn_Start_I);
    EZchassis.pid_swing_constants_set(swn_P, swn_I, swn_D, swn_Start_I);
    EZchassis.pid_odom_angular_constants_set(ang_P, ang_I, ang_D, ang_Start_I);
    EZchassis.pid_odom_boomerang_constants_set(bm_P, bm_I, bm_D, bm_Start_I);

    // Exit conditions
    EZchassis.pid_turn_exit_condition_set(ASET, ALE, ALET, ASE, 500, 500);
    EZchassis.pid_swing_exit_condition_set(ASET, ALE, ALET, ASE, 500, 500);
    EZchassis.pid_drive_exit_condition_set(LSET, LLE, LLET, LSE, 500, 500);
    EZchassis.pid_odom_turn_exit_condition_set(ASET, ALE, ALET, ASE, 500, 750);
    EZchassis.pid_odom_drive_exit_condition_set(LSET, LLE, LLET, LSE, 500, 750);

    // Chain values for smoothing motion
    EZchassis.pid_turn_chain_constant_set(ACh);
    EZchassis.pid_swing_chain_constant_set(SCh);
    EZchassis.pid_drive_chain_constant_set(LCh);

    // Slew (acceleration limiting)
    EZchassis.slew_turn_constants_set(ASDM * 1_deg, ASSM);
    EZchassis.slew_drive_constants_set(LSDM * 1_in, LSSM);
    EZchassis.slew_swing_constants_set(LSDM * 1_in, LSSM);

    // Odometry pathing
    EZchassis.odom_turn_bias_set(0.9);               // Higher = prioritize turns
    EZchassis.odom_look_ahead_set(7_in);             // Distance robot looks ahead in path
    EZchassis.odom_boomerang_distance_set(16_in);    // Max "carrot" lead distance
    EZchassis.odom_boomerang_dlead_set(0.625);       // Curve aggressiveness toward end of motion

    // Default turning behavior
    EZchassis.pid_angle_behavior_set(ez::shortest);
}

//--------------------------------------//
//              LEMLIB SETUP            //
//--------------------------------------//

// Inertial sensor instance
inline pros::Imu imu(IMU);

// Rotation sensors for tracking wheels
inline pros::Rotation horizontalEnc(Hr1Prt);
inline pros::Rotation verticalEnc(Vrt1Prt);
inline pros::Rotation horizontalEnc2(Hr2Prt);
inline pros::Rotation verticalEnc2(Vrt2Prt);

// Tracking wheel objects (encoders + geometry)
inline lemlib::TrackingWheel horizontal(&horizontalEnc, Hr1D, Hr1DTC);
inline lemlib::TrackingWheel vertical(&verticalEnc, Vrt1D, Vrt1DTC);
inline lemlib::TrackingWheel horizontal2(&horizontalEnc2, Hr2D, Hr2DTC);
inline lemlib::TrackingWheel vertical2(&verticalEnc2, Vrt2D, Vrt2DTC);

// Chassis drivetrain configuration
inline lemlib::Drivetrain drivetrain(
    &leftMotors,
    &rightMotors,
    Track_Width,
    Wheel_Diameter,
    Wheel_RPM,
    ACh  // Drift constant
);

// Linear (forward/reverse) motion controller
inline lemlib::ControllerSettings linearController(
    lin_P, lin_I, lin_D,
    lin_Start_I,
    LSE, LSET, LLE, LLET,
    LSSM
);

// Angular (turning) motion controller
inline lemlib::ControllerSettings angularController(
    ang_P, ang_I, ang_D,
    ang_Start_I,
    ASE, ASET, ALE, ALET,
    ASSM
);

// Odometry sensor bundle
inline lemlib::OdomSensors sensors(
    &vertical,
    &vertical2,
    &horizontal,
    &horizontal2,
    &imu
);

// Input curve for throttle (right joystick)
inline lemlib::ExpoDriveCurve throttleCurve(RDB, RMO, RC);

// Input curve for steering (left joystick)
inline lemlib::ExpoDriveCurve steerCurve(LDB, LMO, LC);

// Main chassis object
inline lemlib::Chassis LEMchassis(
    drivetrain,
    linearController,
    angularController,
    sensors,
    &throttleCurve,
    &steerCurve
);
