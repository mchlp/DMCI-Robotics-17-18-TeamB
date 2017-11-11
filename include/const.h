
#ifndef CONST_H_
#define CONST_H_

//inputs from joystick
#define JOYSTICK_WHEELS_HORIZONTAL 1 // x axis on right joystick
#define JOYSTICK_WHEELS_VERTICAL 2 // y axis on right joystick
#define JOYSTICK_ARM 3 // y axis on left joystick
#define JOYSTICK_CLAW 5 // left side double buttons
#define JOYSTICK_MOBILE_GOAL_LIFT 6 // right side double buttons
#define JOYSTICK_MODE 8 // mode button group

//channels for motors
//#define MOTOR_ARM_LEFT 2
//#define MOTOR_ARM_RIGHT 3
#define MOTOR_ARM 2
#define MOTOR_CLAW 8
#define MOTOR_LEFT_WHEEL_FRONT 4
#define MOTOR_LEFT_WHEEL_BACK 5
#define MOTOR_RIGHT_WHEEL_FRONT 6
#define MOTOR_RIGHT_WHEEL_BACK 7
#define MOTOR_MOBILE_GOAL_LIFT 3

#define MAX_SPEED 127
#define PERCISE_SPEED 50

#define NORMAL_SPEED_MOD 1
#define PERCISE_SPEED_MOD 0.25

#define CONTROLLER_PRIMARY 1
#define CONTROLLER_PARTNER 2
#endif // CONST_H_
