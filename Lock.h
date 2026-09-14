

#pragma once

#include <Arduino.h>
#include <stdint.h>

#include "HardwareMap.h"
#include "TCA9554.h"

class Lock {
private:
  TCA9554 *tca9554;
  DigitalOutput output;
  bool locked = false;
public:
  bool begin(TCA9554 &tca9554,DigitalOutput output);

  bool lock();
  bool unlock();

  bool isLocked() const;
};