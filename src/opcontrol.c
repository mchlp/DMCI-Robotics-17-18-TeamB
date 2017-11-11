/** @file opcontrol.c
 * @brief File for operator control code
 *
 * This file should contain the user operatorControl() function and any functions related to it.
 *
 * Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"

/*
 * Runs the user operator control code. This function will be started in its own task with the
 * default priority and stack size whenever the robot is enabled via the Field Management System
 * or the VEX Competition Switch in the operator control mode. If the robot is disabled or
 * communications is lost, the operator control task will be stopped by the kernel. Re-enabling
 * the robot will restart the task, not resume it from where it left off.
 *
 * If no VEX Competition Switch or Field Management system is plugged in, the VEX Cortex will
 * run the operator control task. Be warned that this will also occur if the VEX Cortex is
 * tethered directly to a computer via the USB A to A cable without any VEX Joystick attached.
 *
 * Code running in this task can take almost any action, as the VEX Joystick is available and
 * the scheduler is operational. However, proper use of delay() or taskDelayUntil() is highly
 * recommended to give other tasks (including system tasks such as updating LCDs) time to run.
 *
 * This task should never exit; it should end with some kind of infinite loop, even if empty.
 */

void operatorControl() {
	extern double speedMod;
	int power, turn, armRotate;
	bool clawOpen, clawClose, mobileGoalOpen, mobileGoalClose, perciseModeOn, perciseModeOff;

	while (1) {
		power = joystickGetAnalog(CONTROLLER_PRIMARY, JOYSTICK_WHEELS_VERTICAL);
		turn = joystickGetAnalog(CONTROLLER_PRIMARY, JOYSTICK_WHEELS_HORIZONTAL);
		armRotate = joystickGetAnalog(CONTROLLER_PRIMARY, JOYSTICK_ARM);
		clawOpen = joystickGetDigital(CONTROLLER_PRIMARY, JOYSTICK_CLAW, JOY_UP);
		clawClose = joystickGetDigital(CONTROLLER_PRIMARY, JOYSTICK_CLAW, JOY_DOWN);
		mobileGoalOpen = joystickGetDigital(CONTROLLER_PRIMARY, JOYSTICK_MOBILE_GOAL_LIFT, JOY_UP);
		mobileGoalClose = joystickGetDigital(CONTROLLER_PRIMARY, JOYSTICK_MOBILE_GOAL_LIFT, JOY_DOWN);
		perciseModeOn = joystickGetDigital(CONTROLLER_PRIMARY, JOYSTICK_MODE, JOY_RIGHT);
		perciseModeOff = joystickGetDigital(CONTROLLER_PRIMARY, JOYSTICK_MODE, JOY_LEFT);
		//clawMotion = joystickGetAnalog(CONTROLLER_PRIMARY, JOYSTICK_CLAW);
		chassisSet((power + turn) * speedMod, (power - turn)*speedMod); //set wheel motor speeds
		armSet(armRotate * speedMod); //set arm rotation speed

		if (perciseModeOn) {
			setPerciseMode(true);
		}
		if (perciseModeOff) {
			setPerciseMode(false);
		}
		
		//claw
		if (clawOpen) {
			clawSet(MAX_SPEED);
		} else if (clawClose) {
			clawSet(-MAX_SPEED);
		} else {
			clawSet(0);
		}

		//mobile goal
		if (mobileGoalOpen) {
			mobileGoalSet(MAX_SPEED);
		} else if (mobileGoalClose) {
			mobileGoalSet(-MAX_SPEED);
		} else {
			mobileGoalSet(0);
		}

		delay(20);
	}
}
