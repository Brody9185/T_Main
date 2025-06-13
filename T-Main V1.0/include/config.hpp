#pragma once

#include <vector>
#include "libs/include/EZ-Template/api.hpp"
#include "libs/include/EZ-Template/EZ-Config.hpp"
#include "libs/include/T_Lib/api.hpp"
#include "main.h"

namespace CONFIG {
    // Drive motor ports
    inline int LftMtr1 = 0;
    inline int LftMtr2 = 0;
    inline int LftMtr3 = 0;
    inline int LftMtr4 = 0;
    inline int RtMtr1 = 0;
    inline int RtMtr2 = 0;
    inline int RtMtr3 = 0;
    inline int RtMtr4 = 0;

    // Inertial Port
    inline int IMU = 0;

    // Wheel Diameter and gear
    inline double Wheel_Diameter = T_Lib::util::Wheel_Size::Omni_4in;
    inline double Mtr_RPM = 600;
    inline double Gear_Ratio = 0.6666667;
    inline double Wheel_RPM = Mtr_RPM * Gear_Ratio;

    // Vertical 1
    inline int Vrt1Prt = 0;
    inline double Vrt1D = T_Lib::util::Wheel_Size::Omni_2;
    inline double Vrt1DTC = 4;

    // Vertical 2
    inline int Vrt2Prt = 0;
    inline double Vrt2D = T_Lib::util::Wheel_Size::Omni_2;
    inline double Vrt2DTC = 4;

    // Horizontal 1
    inline int Hr1Prt = 0;  // You must initialize if you're using it in inline expressions
    inline double Hr1D = T_Lib::util::Wheel_Size::Omni_2;
    inline double Hr1DTC = 4;

    // Horizontal 2
    inline int Hr2Prt = 0;
    inline double Hr2D = T_Lib::util::Wheel_Size::Omni_2;
    inline double Hr2DTC = 4;

    // Motors as vectors (wrapped in a function to avoid early evaluation)
    inline std::vector<int> getLeftDrv() {
        return {LftMtr1, LftMtr2, LftMtr3, LftMtr4};
    }

    inline std::vector<int> getRightDrv() {
        return {RtMtr1, RtMtr2, RtMtr3, RtMtr4};
    }
}
