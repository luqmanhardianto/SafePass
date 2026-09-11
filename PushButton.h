#pragma once

#include <Arduino.h>
#include "HardwareMap.h"
#include "InputManager.h"

class PushButton {
public:
  void begin(DigitalInput input);
  void update();

  DigitalInput getInput() const;
  bool getState() const;
  bool isPressed() const;
private:
  InputManager inputManager;
  DigitalInput inputChannel = DigitalInput::DI1;

  bool state = HIGH;
};