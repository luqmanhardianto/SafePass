#pragma once

#include <Arduino.h>
#include "HardwareMap.h"
#include "Config.h"

class OutputManager {
public:
  bool begin();

  void writeOutput(DigitalOutput output, bool state);

  bool readOutput(DigitalOutput output) const;
private:
  uint8_t outputState = 0;
}