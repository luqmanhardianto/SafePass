#include <sys/_stdint.h>
#include "Config.h"
#include "TCA9554.h"
#include <Wire.h>

bool TCA9554::begin() {
  if (initialized) {
    return true;
  }

  Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);

  // configure TCA9554 as outputs
  Wire.beginTransmission(TCA9554_ADDRESS);
  Wire.write(TCA9554_REG_CONFIG);
  Wire.write(0x00);

  if (Wire.endTransmission() != 0) {
    return false;
  }

  // no polarity inversion
  Wire.beginTransmission(TCA9554_ADDRESS);
  Wire.write(TCA9554_REG_POLARITY);
  Wire.write(0x00);

  if (Wire.endTransmission() != 0) {
    return false;
  }

  // start from a known output state
  sharedOutputState = 0x00;

  if (!writeOutputState(sharedOutputState)) {
    return false;
  }

  initialized = true;
  return true;
}

bool TCA9554::writeOutputState(uint8_t outputState) {
  Wire.beginTransmission(TCA9554_ADDRESS);
  Wire.write(TCA9554_REG_OUTPUT);
  Wire.write(outputState);
  return Wire.endTransmission() == 0;
}

bool TCA9554::setOutput(DigitalOutput output, bool state);
bool TCA9554::getOutput(DigitalOutput output) const {
  const uint8_t bit = static_cast<uint8_t>(output);
  return (sharedOutputState & (static_cast<uint8_t>(1U) << bit)) != 0;
}
bool TCA9554::isInitialized() const {
  return initialized;
}