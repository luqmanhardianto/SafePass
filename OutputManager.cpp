#include <sys/types.h>
#include <sys/_stdint.h>
#include <Arduino.h>
#include <Wire.h>

#include "OutputManager.h"
#include "Config.h"

bool OutputManager::begin() {
  Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);

  outputState = 0x00;

  // TCA9554 polarity register
  Wire.beginTransmission(TCA9554_ADDRESS);
  Wire.write(0x02);
  Wire.write(0x00);

  if (Wire.endTransmission() != 0) {
    return false;
  }

  // TCA9554 configuration register
  // 0 = output
  Wire.beginTransmission(TCA9554_ADDRESS);
  Wire.write(0x03);
  Wire.write(0x00);

  if (Wire.endTransmission() != 0) {
    return false;
  }

  // TCA9554 output register
  Wire.beginTransmission(TCA9554_ADDRESS);
  Wire.write(0x01);
  Wire.write(outputState);

  if (Wire.endTransmission() != 0) {
    return false;
  }

  return true;
}

void OutputManager::writeOutput(DigitalOutput output, bool state) {
  uint8_t bit = static_cast<uint8_t>(output);

  if (state) {
    outputState |= (1 << bit);
  } else {
    outputState &= ~(1 << bit);
  }

  Wire.beginTransmission(TCA9554_ADDRESS);
  Wire.write(0x01);
  Wire.write(outputState);
  Wire.endTransmission();
}

bool OutputManager::readOutput(DigitalOutput output) const {
  uint8_t bit = static_cast<uint8_t>(output);

  return (outputState & (1 << bit) != 0);
}