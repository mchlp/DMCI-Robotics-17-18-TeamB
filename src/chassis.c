#include "main.h"
#include "chassis.h"

void chassisSet(int left, int right) {
  motorSet(leftWheelsChannel, left);
  motorSet(rightWheelsChannel, right);
}
