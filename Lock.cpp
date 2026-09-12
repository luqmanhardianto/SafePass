#include <stdint.h>
#include <Wire.h>

#include "Config.h"
#include "Lock.h"

namespace {

// One shared output byte for the single TCA9554 device.
uint8_t sharedOutputState = 0x00;

// The TCA9554 is shared by all Lock objects, so initialize it only once.
bool tca9554Initialized = false;

bool writeSharedOutputState(uint8_t outputState) {
  Wire.beginTransmission(TCA9554_ADDRESS);
  Wire.write(TCA9554_REG_OUTPUT);
  Wire.write(outputState);

  return Wire.endTransmission() == 0;
}

bool initializeTca9554() {
  if (tca9554Initialized) {
    return true;
  }

  Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);

  // All TCA9554 pins are outputs.
  Wire.beginTransmission(TCA9554_ADDRESS);
  Wire.write(TCA9554_REG_CONFIG);
  Wire.write(0x00);

  if (Wire.endTransmission() != 0) {
    return false;
  }

  // No polarity inversion.
  Wire.beginTransmission(TCA9554_ADDRESS);
  Wire.write(TCA9554_REG_POLARITY);
  Wire.write(0x00);

  if (Wire.endTransmission() != 0) {
    return false;
  }

  // Start from a known safe software output state.
  sharedOutputState = 0x00;

  if (!writeSharedOutputState(sharedOutputState)) {
    return false;
  }

  tca9554Initialized = true;
  return true;
}

}  // namespace

bool Lock::begin(DigitalOutput output) {
  this->output = output;
  this->locked = false;

   return initializeTca9554();
}

void Lock::lock() {
  if (!initializeTca9554()) {
    locked = false;
    return;
  }

  const uint8_t bit = static_cast<uint8_t>(output);

  // prepare the new state without changing the shared state
  const uint8_t newOutputState =
    sharedOutputState | (static_cast<uint8_t>(1U) << bit);

  if (writeSharedOutputState(newOutputState)) {
    sharedOutputState = newOutputState;
    locked = false;
  }
}

void Lock::unlock() {
  if (!initializeTca9554()) {
    locked = false;
    return;
  }

  const uint8_t bit = static_cast<uint8_t>(output);

  // prepare the new state without chaning shared state yet.
  const uint8_t newOutputState =
    sharedOutputState & ~(static_cast<uint8_t>(1U) << bit);

  if (writeSharedOutputState(newOutputState)) {
    sharedOutputState = newOutputState;
    locked = false;
  }
}

bool Lock::isLocked() const {
  return locked;
}
