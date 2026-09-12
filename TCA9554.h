#pragma once

#include <Arduino.h>
#include "HardwareMap.h"

class TCA9554 {
public:
  bool begin();
  bool setOutput(DigitalOutput output, bool state);
  bool getOutput(DigitalOutput output) const;
};