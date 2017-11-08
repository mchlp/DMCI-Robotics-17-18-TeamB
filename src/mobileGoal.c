#include "main.h"
#include "mobileGoal.h"

void mobileGoalSet(int speed) {
  motorSet(MOTOR_MOBILE_GOAL_LIFT, speed);
}
