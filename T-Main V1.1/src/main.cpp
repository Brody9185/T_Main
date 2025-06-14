#include "main.h"
#include "libs/include/Drive_Config.hpp"
#include "libs/include/maelstrom/logging.hpp"

/// Background task that initializes Maelstrom logging and continuously updates robot coordinates
inline void maelstrom_task() {
  maelstrom::logging::init(true, true, CONFIG::ezLeftMotors, CONFIG::ezRightMotors, true);
  maelstrom::logging::robot_faults_log();  // Start logging robot faults
  maelstrom::logging::robot_coords_log();  // Start logging robot position

  while (true) {
    maelstrom::logging::set_robot_coords(
      EZchassis.odom_x_get(),
      EZchassis.odom_y_get(),
      EZchassis.odom_theta_get()
    );
  }
}

/**
 * Initialization code — runs once when the robot starts up.
 * Must complete before any other competition functions run.
 */
void initialize() {
  pros::delay(500);  // Allow time for legacy ports to stabilize

  // Launch Maelstrom telemetry logger in the background
  pros::Task maelstromTask(maelstrom_task);

  // Set default EZ-Template chassis constants and settings
  default_constants();                                // Initialize drive/PID settings
  EZchassis.opcontrol_curve_buttons_toggle(false);    // Disable in-match curve tuning
  EZchassis.opcontrol_drive_activebrake_set(0.0);     // Disable active braking
  EZchassis.opcontrol_curve_default_set(0.0, 0.0);     // Set default joystick curves

  // --- Optional tracking wheel configuration ---
  EZchassis.odom_tracker_front_set(&horiz_tracker);
  EZchassis.odom_tracker_back_set(&horiz_tracker2);
  EZchassis.odom_tracker_left_set(&vert_tracker);
  EZchassis.odom_tracker_right_set(&vert_tracker2);

  // --- Autonomous routines added to selector ---
  ez::as::auton_selector.autons_add({
    {"Drive\n\nDrive forward and come back", drive_example},
    {"Turn\n\nTurn 3 times.", turn_example},
    {"Drive and Turn\n\nDrive forward, turn, come back", drive_and_turn},
    {"Drive and Turn\n\nSlow down during drive", wait_until_change_speed},
    {"Swing Turn\n\nSwing in an 'S' curve", swing_example},
    {"Motion Chaining\n\nChain drive, turn, and return movements", motion_chaining},
    {"Combine all 3 movements", combining_movements},
    {"Interference\n\nHandles robot interference detection", interfered_example},
    {"Simple Odom\n\nUses odometry to perform a basic drive", odom_drive_example},
    {"Pure Pursuit\n\nNavigate to (0, 30) via (6, 10), then return", odom_pure_pursuit_example},
    {"Pure Pursuit Wait Until\n\nTrigger intake at (12, 24)", odom_pure_pursuit_wait_until_example},
    {"Boomerang\n\nGo to (0, 24, 45) and return", odom_boomerang_example},
    {"Boomerang Pure Pursuit\n\nTo (24,24) via (0,24,45), then return", odom_boomerang_injected_pure_pursuit_example},
    {"Measure Offsets\n\nAutomatically measure and log wheel offsets", measure_offsets},
  });

  // Initialize chassis + autonomous selector
  LEMchassis.calibrate(false);
  EZchassis.initialize();
  ez::as::initialize();

  // IMU check feedback (rumble = good, "---" = bad)
  master.rumble(EZchassis.drive_imu_calibrated() ? "." : "---");
}

/**
 * Runs when the robot is disabled (competition switch/FMS).
 */
void disabled() {
  // Add optional disabled-time code here (e.g., battery monitoring)
}

/**
 * Runs once after initialize(), before autonomous.
 */
void competition_initialize() {
  // Add any pre-auton setup (e.g., LCD confirmation, pneumatics setup)
}

/**
 * Runs during the autonomous period.
 */
void autonomous() {
  EZchassis.pid_targets_reset();                 // Clear any previous PID targets
  EZchassis.drive_imu_reset();                   // Zero IMU
  EZchassis.drive_sensor_reset();                // Reset motor encoders
  EZchassis.odom_xyt_set(0_in, 0_in, 0_deg);     // Set starting pose
  EZchassis.drive_brake_set(MOTOR_BRAKE_HOLD);   // Enable hold mode for precise stops

  /*
    NOTE:
    - Odometry and Pure Pursuit depend on consistent chassis movement.
    - Avoid wheel slip and sudden moves for best results.
  */

  ez::as::auton_selector.selected_auton_call();  // Run the selected routine
}

/**
 * Displays data for a specific tracking wheel.
 */
void screen_print_tracker(ez::tracking_wheel *tracker, std::string name, int line) {
  if (!tracker) return;
  std::string value = name + " tracker: " + util::to_string_with_precision(tracker->get());
  std::string width = "  width: " + util::to_string_with_precision(tracker->distance_to_center_get());
  ez::screen_print(value + width, line);
}

/**
 * Debug screen task — only shows when not in competition mode.
 */
void ez_screen_task() {
  while (true) {
    if (!pros::competition::is_connected()) {
      if (EZchassis.odom_enabled() && !EZchassis.pid_tuner_enabled()) {
        if (ez::as::page_blank_is_on(0)) {
          ez::screen_print(
            "x: " + util::to_string_with_precision(EZchassis.odom_x_get()) +
            "\ny: " + util::to_string_with_precision(EZchassis.odom_y_get()) +
            "\na: " + util::to_string_with_precision(EZchassis.odom_theta_get()),
            1
          );

          screen_print_tracker(EZchassis.odom_tracker_left,  "l", 4);
          screen_print_tracker(EZchassis.odom_tracker_right, "r", 5);
          screen_print_tracker(EZchassis.odom_tracker_back,  "b", 6);
          screen_print_tracker(EZchassis.odom_tracker_front, "f", 7);
        }
      }
    } else {
      if (ez::as::page_blank_amount() > 0)
        ez::as::page_blank_remove_all();
    }

    pros::delay(ez::util::DELAY_TIME);
  }
}
pros::Task ezScreenTask(ez_screen_task);

/**
 * Optional EZ-Template extras:
 * - Live PID tuning with 'X'
 * - Manual autonomous run with DOWN + B
 */
void ez_template_extras() {
  if (!pros::competition::is_connected()) {
    if (master.get_digital_new_press(DIGITAL_X))
      EZchassis.pid_tuner_toggle();

    if (master.get_digital(DIGITAL_B) && master.get_digital(DIGITAL_DOWN)) {
      auto prev_brake = EZchassis.drive_brake_get();
      autonomous();                               // Manually trigger auton
      EZchassis.drive_brake_set(prev_brake);      // Restore brake mode
    }

    EZchassis.pid_tuner_iterate();  // Update live PID tuning
  } else {
    if (EZchassis.pid_tuner_enabled())
      EZchassis.pid_tuner_disable();
  }
}

/**
 * Main operator control loop (teleop).
 */
void opcontrol() {
  EZchassis.drive_brake_set(MOTOR_BRAKE_COAST);  // Use coast for smoother driver control

  while (true) {
    ez_template_extras();                        // Handle optional extras

    // Choose ONE of the following drive modes:
    // EZchassis.opcontrol_tank();
    EZchassis.opcontrol_arcade_standard(ez::SPLIT);  // Split arcade control (2 joysticks)
    // EZchassis.opcontrol_arcade_standard(ez::SINGLE);
    // EZchassis.opcontrol_arcade_flipped(ez::SPLIT);
    // EZchassis.opcontrol_arcade_flipped(ez::SINGLE);

    // Add driver control functions here

    pros::delay(ez::util::DELAY_TIME);  // Maintain consistent loop timing
  }
}
