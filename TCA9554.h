#pragma once

#include <Arduino.h>
#include <stdint.h>

#include "HardwareMap.h"

class TCA9554 {
private:
  uint8_t sharedOutputState = 0x00;
  bool initialized = false;

  bool writeOutputState(uint8_t outputState);
public:
  bool begin();
  bool setOutput(DigitalOutput output, bool state);
  bool getOutput(DigitalOutput output) const;
  bool isInitialized() const;
};