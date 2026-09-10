#pragma once

#include <Arduino.h>
#include "HardwareMap.h"

class InputManager {
public:
  void begin();

  bool readInput(DigitalInput input);
private:
  bool rawState[8];
  bool stableState[8];
  unsigned long lastChangeTime[8];
};