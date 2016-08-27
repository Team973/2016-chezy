/*
 * RobotInfo.h
 *
 *  Created on: Oct 9, 2015
 *      Author: Andrew
 */

#ifndef ROBOTINFO_H_
#define ROBOTINFO_H_

#include "lib/util/Util.h"

namespace frc973 {

/*
 * PWM pin-out
 */
constexpr int DRIVE_RIGHT_PWM = 1;
constexpr int DRIVE_LEFT_PWM = 0;

constexpr int TOP_FLYWHEEL_PWM = 3;
constexpr int BOTTOM_FLYWHEEL_PWM = 6;

//constexpr int UNUSED_PWM = 4;

//constexpr int LINEAR_EXTENSION_PWM = 5;

constexpr int SHOOTER_CONVEYER_MOTOR_PWM = 8;

constexpr int LOWER_CONVEYOR_MOTOR_PWM = 7;
constexpr int CROSS_INTAKE_MOTOR_PWM = 9;

/**
 * CAN bus riders
 */
constexpr int SHOOTER_TURRET_CAN_ID = 2;

/**
 * DIN pin-out
 */
constexpr int AIR_PRESSURE_DIN = 0;

constexpr int PIXY_CAM_DIGITAL_PORT = 9;

constexpr int LEFT_HOOK_HALL_DIN = 3;
constexpr int RIGHT_HOOK_HALL_DIN = 4;

constexpr int LEFT_DRIVE_ENCODER_A_DIN = 24;
constexpr int LEFT_DRIVE_ENCODER_B_DIN = 25;

/**
 * Analog In
 */
constexpr int PIXY_CAM_ANALOG_PORT = 0;

/**
 * Relay pin-out
 */
constexpr int COMPRESSOR_RELAY = 0;

/**
 * Solenoid channels
 */
constexpr int INTAKE_EXTENSION_SOL = 0;
constexpr int SHOOTER_ANGLE_SOL = 1;
constexpr int DRIVE_SHIFT_SOL = 2;


constexpr int POWER_TAKEOFF_SOL_A = 2;
constexpr int POWER_TAKEOFF_SOL_B = 5;

constexpr int GREEN_FLASHLIGHT = 7;
constexpr int MANUAL_FLASHLIGHT = 5;

/**
 * Power Distrobution Channels
 * (only the ones we care about)
 */

// (we don't care about any for this project)

/**
 * USB port-out (driver-station)
 */
constexpr int DRIVER_JOYSTICK_PORT = 0;
constexpr int OPERATOR_JOYSTICK_PORT = 1;

/**
 * Distance (in inches) of the drive per click of the encoder
 */
constexpr double DRIVE_WHEEL_DIAMETER = 4.0;
constexpr double DRIVE_CLICKS_PER_REVOLUTION = 360.0;
constexpr double DRIVE_GEAR_RATIO = 1.0;
constexpr double DRIVE_DIST_PER_REVOLUTION = DRIVE_WHEEL_DIAMETER *
		Constants::PI;
constexpr double DRIVE_DIST_PER_CLICK = DRIVE_DIST_PER_REVOLUTION *
		DRIVE_CLICKS_PER_REVOLUTION;

}

#endif /* SRC_ROBOTINFO_H_ */
