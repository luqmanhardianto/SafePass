#include "esp32-hal.h"
#include "esp32-hal-gpio.h"
#include <stdint.h>
#include "HardwareMap.h"
#include "DoorSensor.h"

void DoorSensor::begin(DigitalInput input) {
  this->input.begin(input);

}

void DoorSensor::readState() {
input.readState();
}

bool DoorSensor::isClosed() const {
  return input.isActive();
}