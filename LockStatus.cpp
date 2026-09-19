#include "esp32-hal.h"
#include "esp32-hal-gpio.h"
#include <stdint.h>
#include "HardwareMap.h"
#include "LockStatus.h"

void LockStatus::begin(DigitalInput input) {
  this->input.begin(input);
}

void LockStatus::readState() {
  input.readState();
}

bool LockStatus::isLocked() const {
  return input.isActive();
}

bool LockStatus::isUnlocked() const{
  return !input.isActive();
}