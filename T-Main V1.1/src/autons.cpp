#include "libs/include/Drive_Config.hpp"
#include "config.hpp"

using namespace CONFIG;

///
// Drive Example
///
void drive_example() {
    EZchassis.pid_drive_set(24, DRIVE_SPEED, true);
    EZchassis.pid_wait();

    EZchassis.pid_drive_set(-12, DRIVE_SPEED);
    EZchassis.pid_wait();

    EZchassis.pid_drive_set(-12, DRIVE_SPEED);
    EZchassis.pid_wait();
}

///
// Turn Example
///
void turn_example() {
    EZchassis.pid_turn_set(90, TURN_SPEED);
    EZchassis.pid_wait();

    EZchassis.pid_turn_set(45, TURN_SPEED);
    EZchassis.pid_wait();

    EZchassis.pid_turn_set(0, TURN_SPEED);
    EZchassis.pid_wait();
}

///
// Combining Turn + Drive
///
void drive_and_turn() {
    EZchassis.pid_drive_set(24, DRIVE_SPEED, true);
    EZchassis.pid_wait();

    EZchassis.pid_turn_set(45, TURN_SPEED);
    EZchassis.pid_wait();

    EZchassis.pid_turn_set(-45, TURN_SPEED);
    EZchassis.pid_wait();

    EZchassis.pid_turn_set(0, TURN_SPEED);
    EZchassis.pid_wait();

    EZchassis.pid_drive_set(-24, DRIVE_SPEED, true);
    EZchassis.pid_wait();
}

///
// Wait Until and Changing Max Speed
///
void wait_until_change_speed() {
    EZchassis.pid_drive_set(24, 30, true);
    EZchassis.pid_wait_until(6);
    EZchassis.pid_speed_max_set(DRIVE_SPEED);
    EZchassis.pid_wait();

    EZchassis.pid_turn_set(45, TURN_SPEED);
    EZchassis.pid_wait();

    EZchassis.pid_turn_set(-45, TURN_SPEED);
    EZchassis.pid_wait();

    EZchassis.pid_turn_set(0, TURN_SPEED);
    EZchassis.pid_wait();

    EZchassis.pid_drive_set(-24, 30, true);
    EZchassis.pid_wait_until(-6);
    EZchassis.pid_speed_max_set(DRIVE_SPEED);
    EZchassis.pid_wait();
}

///
// Swing Example
///
void swing_example() {
    EZchassis.pid_swing_set(ez::LEFT_SWING, 45, SWING_SPEED, 45);
    EZchassis.pid_wait();

    EZchassis.pid_swing_set(ez::RIGHT_SWING, 0, SWING_SPEED, 45);
    EZchassis.pid_wait();

    EZchassis.pid_swing_set(ez::RIGHT_SWING, 45, SWING_SPEED, 45);
    EZchassis.pid_wait();

    EZchassis.pid_swing_set(ez::LEFT_SWING, 0, SWING_SPEED, 45);
    EZchassis.pid_wait();
}

///
// Motion Chaining
///
void motion_chaining() {
    EZchassis.pid_drive_set(24, DRIVE_SPEED, true);
    EZchassis.pid_wait();

    EZchassis.pid_turn_set(45, TURN_SPEED);
    EZchassis.pid_wait_quick_chain();

    EZchassis.pid_turn_set(-45, TURN_SPEED);
    EZchassis.pid_wait_quick_chain();

    EZchassis.pid_turn_set(0, TURN_SPEED);
    EZchassis.pid_drive_set(-24, DRIVE_SPEED, true);
    EZchassis.pid_wait();
}

///
// Combining All Motion Types
///
void combining_movements() {
    EZchassis.pid_drive_set(24, DRIVE_SPEED, true);
    EZchassis.pid_wait();

    EZchassis.pid_turn_set(45, TURN_SPEED);
    EZchassis.pid_wait();

    EZchassis.pid_swing_set(ez::RIGHT_SWING, -45, SWING_SPEED, 45);
    EZchassis.pid_wait();

    EZchassis.pid_turn_set(0, TURN_SPEED);
    EZchassis.pid_wait();

    EZchassis.pid_drive_set(-24, DRIVE_SPEED, true);
    EZchassis.pid_wait();
}

///
// Interference Recovery
///
void tug(int attempts) {
    for (int i = 0; i < attempts - 1; i++) {
        printf("i - %i", i);

        EZchassis.pid_drive_set(-12, 127);
        EZchassis.pid_wait();

        if (EZchassis.interfered) {
            EZchassis.drive_sensor_reset();
            EZchassis.pid_drive_set(-2, 20);
            pros::delay(1000);
        } else {
            return;
        }
    }
}

///
// Interference Handling Example
///
void interfered_example() {
    EZchassis.pid_drive_set(24, DRIVE_SPEED, true);
    EZchassis.pid_wait();

    if (EZchassis.interfered) {
        tug(3);
        return;
    }

    EZchassis.pid_turn_set(90, TURN_SPEED);
    EZchassis.pid_wait();
}

///
// Odom Drive PID Example
///
void odom_drive_example() {
    EZchassis.pid_odom_set(24, DRIVE_SPEED, true);
    EZchassis.pid_wait();

    EZchassis.pid_odom_set(-12, DRIVE_SPEED);
    EZchassis.pid_wait();

    EZchassis.pid_odom_set(-12, DRIVE_SPEED);
    EZchassis.pid_wait();
}

///
// Odom Pure Pursuit Example
///
void odom_pure_pursuit_example() {
    EZchassis.pid_odom_set({{{6, 10}, fwd, DRIVE_SPEED},
                            {{0, 20}, fwd, DRIVE_SPEED},
                            {{0, 30}, fwd, DRIVE_SPEED}},
                            true);
    EZchassis.pid_wait();

    EZchassis.pid_odom_set({{0, 0}, rev, DRIVE_SPEED}, true);
    EZchassis.pid_wait();
}

///
// Pure Pursuit with Wait-Until
///
void odom_pure_pursuit_wait_until_example() {
    EZchassis.pid_odom_set({{{0, 24}, fwd, DRIVE_SPEED},
                            {{12, 24}, fwd, DRIVE_SPEED},
                            {{24, 24}, fwd, DRIVE_SPEED}},
                            true);
    EZchassis.pid_wait_until_index(1);
    EZchassis.pid_wait();
}

///
// Odom Boomerang
///
void odom_boomerang_example() {
    EZchassis.pid_odom_set({{0, 24, 45}, fwd, DRIVE_SPEED}, true);
    EZchassis.pid_wait();

    EZchassis.pid_odom_set({{0, 0, 0}, rev, DRIVE_SPEED}, true);
    EZchassis.pid_wait();
}

///
// Boomerang with Pure Pursuit Chaining
///
void odom_boomerang_injected_pure_pursuit_example() {
    EZchassis.pid_odom_set({{{0, 24, 45}, fwd, DRIVE_SPEED},
                            {{12, 24}, fwd, DRIVE_SPEED},
                            {{24, 24}, fwd, DRIVE_SPEED}},
                            true);
    EZchassis.pid_wait();

    EZchassis.pid_odom_set({{0, 0, 0}, rev, DRIVE_SPEED}, true);
    EZchassis.pid_wait();
}

///
// Tracker Wheel Offset Measurement
///
void measure_offsets() {
    int iterations = 10;

    double l_offset = 0.0, r_offset = 0.0, b_offset = 0.0, f_offset = 0.0;

    if (EZchassis.odom_tracker_left) EZchassis.odom_tracker_left->reset();
    if (EZchassis.odom_tracker_right) EZchassis.odom_tracker_right->reset();
    if (EZchassis.odom_tracker_back) EZchassis.odom_tracker_back->reset();
    if (EZchassis.odom_tracker_front) EZchassis.odom_tracker_front->reset();

    for (int i = 0; i < iterations; i++) {
        EZchassis.pid_targets_reset();
        EZchassis.drive_imu_reset();
        EZchassis.drive_sensor_reset();
        EZchassis.drive_brake_set(pros::E_MOTOR_BRAKE_HOLD);
        EZchassis.odom_xyt_set(0, 0, 0);

        double imu_start = EZchassis.odom_theta_get();
        double target = (i % 2 == 0) ? 90 : 270;

        EZchassis.pid_turn_set(target, 63, ez::raw);
        EZchassis.pid_wait();
        pros::delay(250);

        double t_delta = util::to_rad(fabs(util::wrap_angle(EZchassis.odom_theta_get() - imu_start)));

        double l_delta = EZchassis.odom_tracker_left ? EZchassis.odom_tracker_left->get() : 0.0;
        double r_delta = EZchassis.odom_tracker_right ? EZchassis.odom_tracker_right->get() : 0.0;
        double b_delta = EZchassis.odom_tracker_back ? EZchassis.odom_tracker_back->get() : 0.0;
        double f_delta = EZchassis.odom_tracker_front ? EZchassis.odom_tracker_front->get() : 0.0;

        l_offset += l_delta / t_delta;
        r_offset += r_delta / t_delta;
        b_offset += b_delta / t_delta;
        f_offset += f_delta / t_delta;
    }

    l_offset /= iterations;
    r_offset /= iterations;
    b_offset /= iterations;
    f_offset /= iterations;

    if (EZchassis.odom_tracker_left) EZchassis.odom_tracker_left->distance_to_center_set(l_offset);
    if (EZchassis.odom_tracker_right) EZchassis.odom_tracker_right->distance_to_center_set(r_offset);
    if (EZchassis.odom_tracker_back) EZchassis.odom_tracker_back->distance_to_center_set(b_offset);
    if (EZchassis.odom_tracker_front) EZchassis.odom_tracker_front->distance_to_center_set(f_offset);
}