#include "esp32-hal.h"
#include "esp32-hal-gpio.h"
#include <sys/_stdint.h>
#include "HardwareMap.h"
#include "InputManager.h"


void InputManager::begin(DigitalInput input) {
  this->pin = DI_PINS[static_cast<uint8_t>(input)];

  pinMode(pin, INPUT_PULLUP);
  
  // initialize state from the actual input level
  lastInputState = digitalRead(pin);
  stableInputState = lastInputState;

// initialize deboune timing
lastTimeStateChanged=millis();

// run one normal state update
  readState();
}
void InputManager::readState() {
  bool currentInputState = digitalRead(pin);

  if (currentInputState != lastInputState) {
    lastTimeStateChanged = millis();
  }

  if ((millis() - lastTimeStateChanged) > debounceTimeMs) {
    if (currentInputState != stableInputState) {
      stableInputState = currentInputState;
    }
  }
  lastInputState = currentInputState;
}
bool InputManager::isActive() const {
  return stableInputState == LOW;
}