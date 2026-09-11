#include "esp32-hal.h"
#include "esp32-hal-gpio.h"
#include <stdint.h>
#include "HardwareMap.h"
#include "PushButton.h"

void PushButton::begin(InputFunction pin) {
  this->pin = DI_PINS[static_cast<uint8_t>(pin)];

  pinMode(this->pin, INPUT_PULLUP);
}

void PushButton::readState() {
  // read current raw state of push button
  bool currentButtonState = digitalRead(pin);

  // if state buton change, reset debounce time
  if (currentButtonState != lastButtonState) {
    lastTimeStateChanged = millis();
  }

  if ((millis() - lastTimeStateChanged) > debounceTimeMs) {

    if (currentButtonState != stableButtonState) {
      stableButtonState = currentButtonState;
    }
  }

  lastButtonState = currentButtonState;
}

bool PushButton::isPressed() const {
  return (stableButtonState == LOW);
}

uint8_t PushButton::getPin() const {
  return pin;
}