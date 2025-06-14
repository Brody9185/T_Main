/**
 * \file main.h
 * \brief Common definitions and headers for the PROS project.
 *
 * Includes core configurations, libraries, and competition task prototypes.
 *
 * Copyright (c) 2017-2021, Purdue University ACM SIGBots.
 * Licensed under the Mozilla Public License, v. 2.0
 * http://mozilla.org/MPL/2.0/
 */

#ifndef _PROS_MAIN_H_
#define _PROS_MAIN_H_

// Enables simpler enum names (e.g., CONTROLLER_MASTER instead of E_CONTROLLER_MASTER)
#define PROS_USE_SIMPLE_NAMES

// Enables C++ user-defined literals (e.g., 4_mtr = 50 sets motor 4's speed)
#define PROS_USE_LITERALS

// Core PROS API
#include "api.h"

// Custom project libraries and configuration
#include "libs/include/libapi.hpp"
#include "autons.hpp"
#include "config.hpp"

// Enable OkapiLib literals like 100_rpm, 12_in, etc.
using namespace okapi::literals;

/**
 * Competition mode function prototypes.
 * These are called automatically by PROS in competition, but can also be called manually (e.g. for testing).
 */
#ifdef __cplusplus
extern "C" {
#endif

void initialize(void);
void disabled(void);
void competition_initialize(void);
void autonomous(void);
void opcontrol(void);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
// Add C++-only includes here if needed (e.g., <iostream>)
#endif

#endif  // _PROS_MAIN_H_
