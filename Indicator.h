#pragma once

#include <Arduino.h>
#include "TCA9554.h"
#include "HardwareMap.h"

class Indicator {
private:
  TCA9554 *tca9554;
  DigitalOutput output;
  bool onState = false;
public:
  bool begin(TCA9554 &tca9554, DigitalOutput output);
  bool on();
  bool off();
  bool isOn() const;
};