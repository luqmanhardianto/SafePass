#include "HardwareMap.h"
#include "esp32-hal-gpio.h"
#include "PushButton.h"

void PushButton::begin(DigitalInput input) {
  inputChannel = input;
  inputManager.begin();
  this->inputPin = input;

  state = HIGH;
}

void PushButton::update() {
  if (input == nullptr) {
    return;
  }

  state = input->readInput(inputPin);
}

DigitalInput PushButton::getInput() const {
  return inputPin;
}

bool PushButton::getState() const {
  return state;
}

bool PushButton::isPressed() const {
  return state == LOW;
}