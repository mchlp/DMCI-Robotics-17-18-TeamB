#include "main.h"
#include "arm.h"

void armSet(int speed) {
  motorSet(MOTOR_ARM_LEFT, speed);
  motorSet(MOTOR_ARM_RIGHT, speed);
}
