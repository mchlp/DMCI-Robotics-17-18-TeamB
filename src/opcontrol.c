#include "main.h"

#define TIME_DELAY 0.01
#define TIME_DELAY_MS (int)(TIME_DELAY * 1000)

#define NULL_PID { 1, 0, 0, TIME_DELAY, 0, 0, -1, 1, -1, 1 }

// Motor format: { pin, scale, offset, min, max }

static struct motor_pid mot_mob[] = {
	{ { 3, 1, 0, -1, 1 }, NULL_PID },
};

static struct motor_drive mot_drive = {
	{ { 4,-1, 0, -1, 1 }, NULL_PID }, { { 6, 1, 0, -1, 1 }, NULL_PID },
	{ { 5,-1, 0, -1, 1 }, NULL_PID }, { { 7, 1, 0, -1, 1 }, NULL_PID },
};

static double feedback_null[8];

void operatorControl() {

//	while(!isJoystickConnected(1));

	unsigned long wakeupTime = millis();
	double mult = 1;

	while (1) {
		double joya_fb = get_joy_map(1, 2);
		double joya_lr = get_joy_map(1, 4);
		double joya_mob = get_joy_ud(1, 5);

		double joyd_change_mode = get_joy_lr(1, 8);
		if(joyd_change_mode == -1) {
			mult = 0.5;
		} else if(joyd_change_mode == 1) {
			mult = 1;
		}

		printf("%f %f %f\n", joya_fb, joya_lr, joya_mob);

		write_group_pid(GROUP_PID(mot_mob), joya_mob, feedback_null);
		write_motor_drive(&mot_drive, joya_fb * mult, curve(joya_lr * mult), 0, 0, 0, 0);

		taskDelayUntil(&wakeupTime, TIME_DELAY_MS);
	}
}
