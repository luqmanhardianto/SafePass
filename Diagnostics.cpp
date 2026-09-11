#include "HardwareSerial.h"
#include "esp32-hal.h"
#include <sys/_stdint.h>
#include "Diagnostics.h"

#include "InputManager.h"
#include "OutputManager.h"
#include "HardwareMap.h"
#include "Config.h"

void Diagnostics::begin(
  InputManager *inputManager, 
  OutputManager *outputManager) {
    input = inputManager;
    output = outputManager;

    lastStatusTime = millis();
}

void Diagnostics::update() {
  uint32_t now = millis();

  if (now - lastStatusTime < DIAGNOSTICS_INTERVAL_MS){
    return;
  }

  lastStatusTime = now;

  showInputState();
  shwoOutputState();
}

void Diagnostics::showInputState() {
  if (input == nullptr) {
  return;
  }

  Serial.print();
}

void Diagnostics::shwoOutputState() {
}