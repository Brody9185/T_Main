/**
 * \file api.h
 * \brief PROS API master include file for user-level functionality.
 *
 * Includes all essential PROS C and C++ headers for VEX V5 robot programming.
 * This file should not be modified by users, as it is overwritten during kernel upgrades.
 *
 * \copyright Copyright (c) 2017–2023, Purdue University ACM SIGBots.
 * Licensed under the Mozilla Public License, v. 2.0
 * http://mozilla.org/MPL/2.0/
 */

#ifndef _PROS_API_H_
#define _PROS_API_H_

// Include standard libraries depending on language context
#ifdef __cplusplus
  #include <cerrno>
  #include <cmath>
  #include <cstdbool>
  #include <cstddef>
  #include <cstdint>
  #include <cstdio>
  #include <cstdlib>
  #include <iostream>
#else
  #include <errno.h>
  #include <math.h>
  #include <stdbool.h>
  #include <stddef.h>
  #include <stdint.h>
  #include <stdio.h>
  #include <stdlib.h>
  #include <unistd.h>
#endif

// PROS Version Macros
#define PROS_VERSION_MAJOR 4
#define PROS_VERSION_MINOR 1
#define PROS_VERSION_PATCH 1
#define PROS_VERSION_STRING "4.1.1"

// Include all core PROS C API headers
#include "pros/adi.h"
#include "pros/colors.h"
#include "pros/device.h"
#include "pros/distance.h"
#include "pros/error.h"
#include "pros/ext_adi.h"
#include "pros/gps.h"
#include "pros/imu.h"
#include "pros/link.h"
#include "pros/llemu.h"
#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/optical.h"
#include "pros/rotation.h"
#include "pros/rtos.h"
#include "pros/screen.h"
#include "pros/vision.h"

// Include C++ wrappers for all supported PROS modules
#ifdef __cplusplus
  #include "pros/adi.hpp"
  #include "pros/colors.hpp"
  #include "pros/device.hpp"
  #include "pros/distance.hpp"
  #include "pros/gps.hpp"
  #include "pros/imu.hpp"
  #include "pros/link.hpp"
  #include "pros/llemu.hpp"
  #include "pros/misc.hpp"
  #include "pros/motor_group.hpp"
  #include "pros/motors.hpp"
  #include "pros/optical.hpp"
  #include "pros/rotation.hpp"
  #include "pros/rtos.hpp"
  #include "pros/screen.hpp"
  #include "pros/vision.hpp"
#endif

#endif  // _PROS_API_H_