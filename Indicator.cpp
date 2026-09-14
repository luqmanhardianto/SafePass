#include "Indicator.h"

bool Indicator::begin(TCA9554 &tca9554, DigitalOutput output) {
  this->tca9554 = &tca9554;
  this->output = output;
  this->onState = false;

  if (!this->tca9554->isInitialized()) {
    return false;
  }
  return true;
}
bool Indicator::on() {
  if (tca9554 == nullptr) {
    return false;
  }

  if (tca9554->setOutput(output, true)) {
    onState = true;
    return true;
  }

  return false;
}
bool Indicator::off();
bool Indicator::isOn() const;