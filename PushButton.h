#pragma once

#include <Arduino.h>
#include "HardwareMap.h"

class InputManager;

class PushButton {
public:
  void begin(InputManager *inputManager, DigitalInput input);
  void update();

  DigitalInput getInput() const;
  bool getState() const;
  bool isPressed() const;
private:
  InputManager *input = nullptr;
  DigitalInput inputPin = DigitalInput::DI1;

  bool state = HIGH;
};