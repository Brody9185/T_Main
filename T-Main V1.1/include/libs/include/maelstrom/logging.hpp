#ifndef _LOGGING_HPP_
#define _LOGGING_HPP_

// Includes
#include "libs/include/maelstrom/api.hpp"
#include <fstream>
#include <vector>
#include <cstdint>
#include <string>

namespace maelstrom {
namespace logging {

    // === ENUM DEFINITIONS ===

    /// Format options for date/time output
    enum date_time_format {
        E_YEAR,
        E_MONTH,
        E_DAY,
        E_DATE,
        E_TIME,
        E_DATE_TIME,
        E_DATE_TIME_FILE_PATH_FORMAT,
        E_NONE
    };

    /// Log file types
    enum log_file {
        E_ERROR_LOG,
        E_DATA_LOG
    };

    // === VARIABLES ===

    /// Motor fault tracking: faults[side][port index]
    extern std::vector<std::vector<bool>> faults;

    // === INITIALIZATION ===

    /**
     * @brief Initializes logging system.
     * 
     * @param run_error_log Enable error logging.
     * @param run_data_log Enable data logging.
     * @param left_motor_ports List of left motor ports.
     * @param right_motor_ports List of right motor ports.
     * @param battery_threshold Minimum acceptable voltage.
     * @return Pointer to logging enabled status.
     */
    extern bool* init(bool run_error_log, bool run_data_log, std::vector<int> left_motor_ports, std::vector<int> right_motor_ports, int battery_threshold);

    // === LOGGING FUNCTIONS ===

    /**
     * @brief Logs if the battery voltage is below a given threshold.
     * 
     * @param battery_threshold Minimum acceptable voltage.
     * @return true if battery is healthy.
     */
    bool battery(int battery_threshold);

    /// @brief Gets the current date/time in default format.
    std::string get_current_date_time();

    /// @brief Logs any detected robot faults.
    extern void robot_faults_log();

    /**
     * @brief Checks if a motor is connected.
     * 
     * @param port Motor port number.
     * @return true if the motor is connected.
     */
    bool motor_connected(int port);

    /**
     * @brief Logs a specific motor fault.
     * 
     * @param port_index Index in the motor list.
     * @param motor_fault Fault flag from the motor.
     */
    void motor_fault_log(int port_index, uint32_t motor_fault);

    /// @brief Logs the robot’s current coordinates.
    void robot_coords_log();

    /**
     * @brief Sets the robot's current position manually.
     * 
     * @param x X position (inches or meters depending on your units).
     * @param y Y position.
     * @param theta Heading in radians or degrees.
     */
    extern void set_robot_coords(double x, double y, double theta);

    /**
     * @brief Sets the system timezone (affects time logging).
     * 
     * @param timezone_string A valid timezone string (e.g., "EST5EDT", "UTC", etc.)
     */
    void set_timezone(const char* timezone_string);

    /**
     * @brief Logs task completion with status.
     * 
     * @param task_name Name/label of the task.
     * @param completion Whether the task succeeded.
     */
    void task_complete(std::string task_name, bool completion);

    /**
     * @brief Writes a message to the appropriate log file.
     * 
     * @param message The log message.
     * @param file Target log file.
     */
    void write_to_file(std::string message, log_file file);

} // namespace logging
} // namespace maelstrom

#endif // _LOGGING_HPP_