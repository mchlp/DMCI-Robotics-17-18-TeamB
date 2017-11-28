#ifndef util_c
#define util_c

#include <main.h>

#define GROUP_PID(x) x, sizeof(x) / sizeof(struct motor_pid)

#include <inttypes.h>

struct pid {
	double kp, ki, kd;
	double dt, vi, el;
	double clampi_min, clampi_max;
	double clampd_min, clampd_max;
};

struct motor {
	unsigned char channel;
	double mul;
	double off;
	double min;
	double max;
};

struct motor_pid {
	struct motor motor;
	struct pid pid;
};

struct motor_drive {
	struct motor_pid mfl;
	struct motor_pid mfr;
	struct motor_pid mbl;
	struct motor_pid mbr;
};

static inline double curve(double val) {
	double out = val * val;
	if(out < 0)
		out = -out;
	if(val < 0)
		return -out;
	return out;
}


static inline double clamp(double val, double min, double max) {
	if(val < min)
		return min;
	else if(val > max)
		return max;
	return val;
}

static inline double map(double x, double inp_min, double inp_max, double out_min, double out_max) {
	return (x - inp_min) * (out_max - out_min) / (inp_max - inp_min) + out_min;
}

static inline double map_clamp(double x, double inp_min, double inp_max, double out_min, double out_max) {
	return map(clamp(x, inp_min, inp_max), inp_min, inp_max, out_min, out_max);
}

static inline double map_input(int inp) {
	return inp / 127.0;
}

static inline void write_motor(struct motor *mot, double value) {
	if(mot->channel == 0)
		return;
	double output = clamp(mot->mul * value + mot->off, mot->min, mot->max);
//	printf("motorSet(%d, %d)\e[0K\n", mot->channel, (int)clamp(output * 127, -127, 127));
	motorSet(mot->channel, clamp(output * 127, -127, 127));
}

static inline int get_joy_ud(unsigned char joystick, unsigned char buttonGroup) {
	int ctr = 0;
	if(joystickGetDigital(joystick, buttonGroup, JOY_UP))
		ctr --;
	if(joystickGetDigital(joystick, buttonGroup, JOY_DOWN))
		ctr ++;
	return ctr;
}

static inline int get_joy_lr(unsigned char joystick, unsigned char buttonGroup) {
	int ctr = 0;
	if(joystickGetDigital(joystick, buttonGroup, JOY_LEFT))
		ctr --;
	if(joystickGetDigital(joystick, buttonGroup, JOY_RIGHT))
		ctr ++;
	return ctr;
}

static inline double get_joy_map(unsigned char joystick, unsigned char axis) {
	return joystickGetAnalog(joystick, axis) / 127.0;
}

static inline double pid_update(struct pid *p, double setpoint, double feedback) {
	double error = feedback - setpoint;
	double de = clamp((error - p->el) / p->dt * p->kd, p->clampd_min * p->kd, p->clampd_max * p->kd);
	p->vi = clamp(p->vi + error * p->dt * p->ki, p->clampi_min, p->clampi_max);
	if(abs(error) < 0.05) {
		p->vi = 0;
	}
	double corr = error * p->kp + p->vi + de;
	p->el = error;
	return corr;
}

static inline void write_motor_pid(struct motor_pid *p, double setpoint, double feedback) {
	write_motor(&p->motor, pid_update(&p->pid, setpoint, feedback));
}

static inline void write_group_pid(struct motor_pid *group, uint8_t nmotor, double setpoint, double *feedback) {
	for(uint8_t i = 0; i < nmotor; ++i) {
		write_motor_pid(&group[i], setpoint, feedback[i]);
	}
}

static inline void write_motor_drive(struct motor_drive *drive, double forward, double right, double ffl, double ffr, double fbl, double fbr) {
	write_motor_pid(&drive->mfl, forward + right, ffl);
	write_motor_pid(&drive->mfr, forward - right, ffr);
	write_motor_pid(&drive->mbl, forward + right, fbl);
	write_motor_pid(&drive->mbr, forward - right, fbr);
}

#endif
