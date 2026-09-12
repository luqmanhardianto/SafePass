#include "esp32-hal.h"
#include "esp32-hal-gpio.h"
#include <stdint.h>
#include "HardwareMap.h"
#include "PushButton.h"

void PushButton::begin(DigitalInput input) {
  this->input.begin(input);
}

void PushButton::readState() {
  this->input.readState();
}

bool PushButton::isPressed() const {
  return this->isPressed();
}
