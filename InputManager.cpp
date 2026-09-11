#include "esp32-hal.h"
#include "esp32-hal-gpio.h"
#include "InputManager.h"

void InputManager::begin(uint8_t pin) {
  setPin(pin);

  pinMode(this->pin, INPUT_PULLUP);

  rawState = digitalRead(this->pin);
  stableState = rawState;

  lastChangeTime = millis();
}

void InputManager::update() {
  bool currentState = digitalRead(pin);

  // raw input changed
  if (currentState != rawState) {
    rawState = currentState;
    lastChangeTime = millis();
  }

  // apply debounce to raw input
  if ((millis() - lastChangeTime) >= debounceTime) {
    stableState = rawState;
  }
}

void InputManager::setPin(uint8_t pin) {
  this->pin = pin;
}
uint8_t InputManager::getPin() const {
  return pin;
}

void InputManager::setDebounceTime(unsigned long timeMS) {
  debounceTime = timeMS;
}
unsigned long InputManager::getDebounceTime() const {
  return debounceTime;
}

bool InputManager::getRawState() const {
  return rawState;
}
bool InputManager::getStableState() const {
  return stableState;
}

bool InputManager::isActive() const {
  return stableState == LOW;
}
bool InputManager::isInactive() const {
  return stableState == HIGH;
}