#include "esp32-hal.h"
#include "esp32-hal-gpio.h"
#include <stdint.h>
#include "HardwareMap.h"
#include "DoorSensor.h"

void DoorSensor::begin(DigitalInput input) {
  this->pin = DI_PINS[static_cast<uint8_t>(input)];

  pinMode(this->pin, INPUT_PULLUP);
}

void DoorSensor::readState() {
  bool currentDoorSensorState = digitalRead(pin);

  if (currentDoorSensorState != lastDoorSensorState) {
    lastTimeStateChanged = millis();
  }

  if ((millis() - lastTimeStateChanged) > debounceTimeMs) {
    if (currentDoorSensorState != stableDoorSensorState) {
      stableDoorSensorState = currentDoorSensorState;
    }
  }

  lastDoorSensorState = currentDoorSensorState;
}

bool DoorSensor::isLocked() const {
  return stableDoorSensorState == LOW;
}