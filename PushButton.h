#pragma once

#include <Arduino.h>
#include <sys/_stdint.h>

#include "HardwareMap.h"
#include "InputManager.h"

class PushButton {
private:
  InputManager input;
public:
  void begin(DigitalInput input);

  void readState();

  bool isPressed() const;
};