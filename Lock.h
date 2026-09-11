#include "HardwareMap.h"

#pragma once

#include <Arduino.h>
#include <stdint.h>

class Lock {
private:
  uint8_t outputBit;
  bool locked = false;
public:
  void begin(DigitalOutput output);

  void lock();
  void unlock();

  bool isLocked() const;
};