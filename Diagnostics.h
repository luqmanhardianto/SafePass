
#pragma once
#include <Arduino.h>

class InputManager;
class OutputManager;

class Diagnostics {
public:
  void begin(InputManager* inputManager, OutputManager* outputManager);
  void update();
private:
  InputManager* input = nullptr;
  OutputManager* output = nullptr;

  uint32_t lastStatusTime = 0;

  void showInputState();
  void shwoOutputState();
};