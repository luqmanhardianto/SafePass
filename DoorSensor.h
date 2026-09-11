
#pragma once

#include <Arduino.h>
#include <stdint.h>

#include "esp32-hal-gpio.h"
#include "HardwareMap.h"
#include "Config.h"

class DoorSensor {
private:
  uint8_t pin;

  bool lastDoorSensorState = HIGH;
  bool stableDoorSensorState = HIGH;

  unsigned long lastTimeStateChanged = 0;
  unsigned long debounceTimeMs = INPUT_DEBOUNCE_MS;

public:
  void begin(DigitalInput input);

  void readState();

  bool isLocked() const;
};