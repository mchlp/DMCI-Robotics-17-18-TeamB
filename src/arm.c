#include "main.h"
#include "arm.h"

void armSet(int speed) {
  motorSet(armChannel, speed);
}
