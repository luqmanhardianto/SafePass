#include "Config.h"
#include "TCA9554.h"
#include <Wire.h>

bool TCA9554::begin();
bool TCA9554::writeOutputState(uint8_t outputState) {
  Wire.beginTransmission(TCA9554_ADDRESS);
  Wire.write(TCA9554_REG_OUTPUT);
  Wire.write(outputState);
  return Wire.endTransmission() == 0;
}

bool TCA9554::setOutput(DigitalOutput output, bool state);
bool TCA9554::getOutput(DigitalOutput output) const;
bool TCA9554::isInitialized() const;