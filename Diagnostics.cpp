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
}

void Diagnostics::showInputState() {
}

void Diagnostics::shwoOutputState() {
}