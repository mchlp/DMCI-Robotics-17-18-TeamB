#include "main.h"
#include "chassis.h"

void chassisSet(int left, int right) {
  motorSet(MOTOR_LEFT_WHEEL_BACK, left);
  motorSet(MOTOR_LEFT_WHEEL_FRONT, left);
  motorSet(MOTOR_RIGHT_WHEEL_BACK, right);
  motorSet(MOTOR_RIGHT_WHEEL_FRONT, right);
}
