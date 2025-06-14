/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#pragma once

/** 
 * @mainpage OkapiLib Documentation
 *
 * @section intro_sec Introduction
 *
 * OkapiLib is a high-level C++ library built on top of PROS for VEX V5 robots.
 * It simplifies complex tasks like motion profiling, odometry, PID control, 
 * and sensor integration, while remaining highly flexible and extensible.
 *
 * @section getting_started Getting Started
 * See the [Getting Started Guide](docs/tutorials/walkthrough/gettingStarted.md)
 * or try the [Clawbot tutorial](docs/tutorials/walkthrough/clawbot.md).
 *
 * @section docs Using the Docs
 * Use the [Tutorials](docs/tutorials/index.md) for guided instruction,
 * or [API Docs](docs/api/index.md) for in-depth technical details.
 */

// === Chassis Controllers ===
#include "okapi/api/chassis/controller/chassisControllerIntegrated.hpp"
#include "okapi/api/chassis/controller/chassisControllerPid.hpp"
#include "okapi/api/chassis/controller/chassisScales.hpp"
#include "okapi/api/chassis/controller/defaultOdomChassisController.hpp"
#include "okapi/api/chassis/controller/odomChassisController.hpp"

// === Chassis Models ===
#include "okapi/api/chassis/model/hDriveModel.hpp"
#include "okapi/api/chassis/model/readOnlyChassisModel.hpp"
#include "okapi/api/chassis/model/skidSteerModel.hpp"
#include "okapi/api/chassis/model/threeEncoderSkidSteerModel.hpp"
#include "okapi/api/chassis/model/threeEncoderXDriveModel.hpp"
#include "okapi/api/chassis/model/xDriveModel.hpp"

// === Chassis Controller Builder ===
#include "okapi/impl/chassis/controller/chassisControllerBuilder.hpp"

// === Async Controllers ===
#include "okapi/api/control/async/asyncLinearMotionProfileController.hpp"
#include "okapi/api/control/async/asyncMotionProfileController.hpp"
#include "okapi/api/control/async/asyncPosIntegratedController.hpp"
#include "okapi/api/control/async/asyncPosPidController.hpp"
#include "okapi/api/control/async/asyncVelIntegratedController.hpp"
#include "okapi/api/control/async/asyncVelPidController.hpp"
#include "okapi/api/control/async/asyncWrapper.hpp"

// === Controller IO Interfaces ===
#include "okapi/api/control/controllerInput.hpp"
#include "okapi/api/control/controllerOutput.hpp"

// === Iterative Controllers ===
#include "okapi/api/control/iterative/iterativeMotorVelocityController.hpp"
#include "okapi/api/control/iterative/iterativePosPidController.hpp"
#include "okapi/api/control/iterative/iterativeVelPidController.hpp"

// === Controller Utilities ===
#include "okapi/api/control/util/controllerRunner.hpp"
#include "okapi/api/control/util/flywheelSimulator.hpp"
#include "okapi/api/control/util/pidTuner.hpp"
#include "okapi/api/control/util/settledUtil.hpp"

// === Async Builder Utilities ===
#include "okapi/impl/control/async/asyncMotionProfileControllerBuilder.hpp"
#include "okapi/impl/control/async/asyncPosControllerBuilder.hpp"
#include "okapi/impl/control/async/asyncVelControllerBuilder.hpp"

// === Iterative Controller Factories ===
#include "okapi/impl/control/iterative/iterativeControllerFactory.hpp"
#include "okapi/impl/control/util/controllerRunnerFactory.hpp"
#include "okapi/impl/control/util/pidTunerFactory.hpp"

// === Odometry ===
#include "okapi/api/odometry/odomMath.hpp"
#include "okapi/api/odometry/odometry.hpp"
#include "okapi/api/odometry/threeEncoderOdometry.hpp"

// === Devices: Rotary Sensors ===
#include "okapi/api/device/rotarysensor/continuousRotarySensor.hpp"
#include "okapi/api/device/rotarysensor/rotarySensor.hpp"

// === Devices: Implementation ===
#include "okapi/impl/device/adiUltrasonic.hpp"
#include "okapi/impl/device/button/adiButton.hpp"
#include "okapi/impl/device/button/controllerButton.hpp"
#include "okapi/impl/device/controller.hpp"
#include "okapi/impl/device/distanceSensor.hpp"
#include "okapi/impl/device/motor/adiMotor.hpp"
#include "okapi/impl/device/motor/motor.hpp"
#include "okapi/impl/device/motor/motorGroup.hpp"
#include "okapi/impl/device/opticalSensor.hpp"

// === Devices: Rotary Sensor Types ===
#include "okapi/impl/device/rotarysensor/IMU.hpp"
#include "okapi/impl/device/rotarysensor/adiEncoder.hpp"
#include "okapi/impl/device/rotarysensor/adiGyro.hpp"
#include "okapi/impl/device/rotarysensor/integratedEncoder.hpp"
#include "okapi/impl/device/rotarysensor/potentiometer.hpp"
#include "okapi/impl/device/rotarysensor/rotationSensor.hpp"

// === Filters ===
#include "okapi/api/filter/averageFilter.hpp"
#include "okapi/api/filter/composableFilter.hpp"
#include "okapi/api/filter/demaFilter.hpp"
#include "okapi/api/filter/ekfFilter.hpp"
#include "okapi/api/filter/emaFilter.hpp"
#include "okapi/api/filter/filter.hpp"
#include "okapi/api/filter/filteredControllerInput.hpp"
#include "okapi/api/filter/medianFilter.hpp"
#include "okapi/api/filter/passthroughFilter.hpp"
#include "okapi/api/filter/velMath.hpp"
#include "okapi/impl/filter/velMathFactory.hpp"

// === Units ===
#include "okapi/api/units/QAcceleration.hpp"
#include "okapi/api/units/QAngle.hpp"
#include "okapi/api/units/QAngularAcceleration.hpp"
#include "okapi/api/units/QAngularJerk.hpp"
#include "okapi/api/units/QAngularSpeed.hpp"
#include "okapi/api/units/QArea.hpp"
#include "okapi/api/units/QForce.hpp"
#include "okapi/api/units/QFrequency.hpp"
#include "okapi/api/units/QJerk.hpp"
#include "okapi/api/units/QLength.hpp"
#include "okapi/api/units/QMass.hpp"
#include "okapi/api/units/QPressure.hpp"
#include "okapi/api/units/QSpeed.hpp"
#include "okapi/api/units/QTime.hpp"
#include "okapi/api/units/QTorque.hpp"
#include "okapi/api/units/QVolume.hpp"
#include "okapi/api/units/RQuantityName.hpp"

// === Utilities ===
#include "okapi/api/util/abstractRate.hpp"
#include "okapi/api/util/abstractTimer.hpp"
#include "okapi/api/util/mathUtil.hpp"
#include "okapi/api/util/supplier.hpp"
#include "okapi/api/util/timeUtil.hpp"
#include "okapi/impl/util/configurableTimeUtilFactory.hpp"
#include "okapi/impl/util/rate.hpp"
#include "okapi/impl/util/timeUtilFactory.hpp"
#include "okapi/impl/util/timer.hpp"