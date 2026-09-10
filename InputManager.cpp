#include "InputManager.h"
#include "Config.h"

void InputManager::begin() {
  for (uint8_t i = 0; i < 8; i++) {
    pinMode(DI_PINS[i], INPUT_PULLDOWN);

    rawState[i] = digitalRead(DI_PINS[i]);
    stableState[i] = rawState[i];

    lastChangeTime[i] = millis();
  }
}

bool InputManager::readInput(DigitalInput input) {
  uint8_t index = static_cast<uint8_t>(input);

  bool currentRawState = digitalRead(DI_PINS[index]);

  // detect raw input change
  if (currentRawState != rawState[index]) {
    rawState[index] = currentRawState;
    lastChangeTime[index] = millis();
  }

  // accept the new state only if it has remained stable
  // for the configured debounce time
  if (millis() - lastChangeTime[index] >= INPUT_DEBOUNCE_MS) {
    stableState[index] = rawState[index];
  }

  return stableState[index];
}