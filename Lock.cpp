#include <stdint.h>
#include <Wire.h>

#include "Lock.h"
bool Lock::begin(TCA9554 &tca9554, DigitalOutput output) {
  this->tca9554 = &tca9554;
  this->output = output;
  this->locked = false;

  if (!this->tca9554->isInitialized()) {
    return false;
  }
  return true;
}

bool Lock::lock() {
  if (tca9554 == nullptr) {
    return false;
  }

  if (tca9554->setOutput(output, true)) {
    locked = true;
    return true;
  }
}
bool Lock::unlock();
bool Lock::isLocked() const {
  return locked;
}
