

#pragma once

#include <Arduino.h>
#include <stdint.h>

#include "HardwareMap.h"

class Lock {
private:
  DigitalOutput output;
  bool locked = false;
public:
  bool begin(DigitalOutput output);

  void lock();
  void unlock();

  bool isLocked() const;
};