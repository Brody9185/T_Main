#include "libs/include/T_Lib/api.hpp"

namespace T_Lib {
    namespace util {

        // Contains actual measured diameters for common VEX wheel types (in inches).
        namespace Wheel_Size {
            // 4-inch class wheels (actual measured)
            inline constexpr double Omni_4in         = 4.20070012;  // Measured Omni 4"
            inline constexpr double Trac_4in         = 4.000;       // Measured Traction 4"
            inline constexpr double Trac_Flex_4in    = 4.000;       // Measured Flex Traction 4"
            inline constexpr double Mech_4in         = 4.000;       // Measured Mecanum 4"

            // 3.25-inch class wheels (actual measured)
            inline constexpr double Omni_325in       = 3.250;       // Measured Omni 3.25"
            inline constexpr double Trac_325in       = 3.250;       // Measured Traction 3.25"

            // 3-inch class wheels (actual measured)
            inline constexpr double Trac_Flex_3in    = 3.000;       // Measured Flex Traction 3"
            inline constexpr double Omni_275         = 2.750;       // Measured Omni 2.75"
            inline constexpr double Trac_275         = 2.750;       // Measured Traction 2.75"

            // 2-inch class wheels (actual measured)
            inline constexpr double Omni_2           = 2.000;       // Measured Omni 2"
            inline constexpr double Trac_2           = 2.000;       // Measured Traction 2"
            inline constexpr double Trac_Flex_2      = 2.000;       // Measured Flex Traction 2"
            inline constexpr double Mech_2           = 2.000;       // Measured Mecanum 2"

            // Specialty sizes (actual measured)
            inline constexpr double Trac_Flex_1625in = 1.625;       // Measured Flex Traction 1.625"
        }

    }  // namespace util
}  // namespace T_Lib