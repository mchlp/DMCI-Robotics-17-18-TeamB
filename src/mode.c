#include "main.h"
#include "mode.h"

bool perciseModeOn = false;
double speedMod = NORMAL_SPEED_MOD;

void setPerciseMode(bool percise) {
  perciseModeOn = percise;
  if (perciseModeOn) {
    speedMod = PERCISE_SPEED_MOD;
  } else {
    speedMod = NORMAL_SPEED_MOD;
  }
}
