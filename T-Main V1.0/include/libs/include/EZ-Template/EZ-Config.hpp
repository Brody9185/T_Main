#pragma once

#include "config.hpp"

inline ez::Drive EZchassis = ez::Drive(
    {CONFIG::getLeftDrv()},
    {CONFIG::getRightDrv()},
    CONFIG::IMU,
    CONFIG::Wheel_Diameter,
    CONFIG::Wheel_RPM
);

inline ez::tracking_wheel vert_tracker(CONFIG::Vrt1Prt, CONFIG::Vrt1D, CONFIG::Vrt1DTC);
inline ez::tracking_wheel vert_tracker2(CONFIG::Vrt2Prt, CONFIG::Vrt2D, CONFIG::Vrt2DTC);
inline ez::tracking_wheel horiz_tracker(CONFIG::Hr1Prt, CONFIG::Hr1D, CONFIG::Hr1DTC);
inline ez::tracking_wheel horiz_tracker2(CONFIG::Hr2Prt, CONFIG::Hr2D, CONFIG::Hr2DTC);