
#include "main.h"

#define TIME_DELAY 0.01
#define TIME_DELAY_MS (int)(TIME_DELAY * 1000)

#define TDU() taskDelayUntil(&wakeupTime, TIME_DELAY_MS)
#define FORI(n) for(unsigned _ = 0; _ < n; ++_)
#define WAIT(n) FORI(n / TIME_DELAY_MS) TDU()

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

void autonomous() {

	unsigned long wakeupTime = millis();

	// Extend mobile goal
	write_group_pid(GROUP_PID(mot_mob), 1, feedback_null);
	WAIT(500);
	write_motor_drive(&mot_drive, 1, 0, 0, 0, 0, 0);
	WAIT(1000);
	write_group_pid(GROUP_PID(mot_mob), 0, feedback_null);

	// Drive forward
	WAIT(1000);
	write_motor_drive(&mot_drive, 0, 0, 0, 0, 0, 0);

	// Retract mobile goal
	write_group_pid(GROUP_PID(mot_mob), -1, feedback_null);
	WAIT(1000);

	write_motor_drive(&mot_drive, -1, 0.3, 0, 0, 0, 0);
	WAIT(1000);
	write_group_pid(GROUP_PID(mot_mob), 0, feedback_null);
	// Drive back
	WAIT(500);
	write_motor_drive(&mot_drive, 0, 0, 0, 0, 0, 0);

	// Drive Turn
	write_motor_drive(&mot_drive, 0, -1, 0, 0, 0, 0);
	WAIT(800);
	write_motor_drive(&mot_drive, 0, 0, 0, 0, 0, 0);

/*

	// Drive Forward
	write_motor_drive(&mot_drive, 1, 0, 0, 0, 0, 0);
	WAIT(500);
	write_motor_drive(&mot_drive, 0, 0, 0, 0, 0, 0);
*/
	// Extend mobile goal
	write_group_pid(GROUP_PID(mot_mob), 1, feedback_null);
	WAIT(2000);
	write_group_pid(GROUP_PID(mot_mob), 0, feedback_null);

	// Extend mobile goal
	write_group_pid(GROUP_PID(mot_mob), -1, feedback_null);
	WAIT(500);
	write_group_pid(GROUP_PID(mot_mob), 0, feedback_null);

	// Drive back
	write_motor_drive(&mot_drive, -1, 0, 0, 0, 0, 0);
	WAIT(1500);
	write_motor_drive(&mot_drive, 0, 0, 0, 0, 0, 0);


	return;
}
