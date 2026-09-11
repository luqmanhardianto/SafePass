#include "HardwareMap.h"
#include "esp32-hal-gpio.h"
#include "PushButton.h"

void PushButton::begin(uint8_t pin) {
  input.begin(pin);
  state = input.getStableState();
}

void PushButton::update() {
  input.update();
  state = input.getStableState();
}

uint8_t PushButton::getPin() const {
  return input.getPin();
}

bool PushButton::getState() const {
  return state;
}
bool PushButton::isPressed() const {
  return input.isActive();
}
bool PushButton::isReleased() const {
  return input.isInactive();
}