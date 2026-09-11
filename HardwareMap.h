#pragma once
#include <Arduino.h>
#include <sys/_stdint.h>

// physical digital input channel
enum class DigitalInput : uint8_t {
  DI1 = 0,
  DI2,
  DI3,
  DI4,
  DI5,
  DI6,
  DI7,
  DI8
};

// gpio assigned to each  digital input channel
constexpr uint8_t DI_PINS[] = {
  4, 5, 6, 7, 8, 9, 10, 11
};

// application function assigned to each input channel
enum class InputFunction : uint8_t {
  PUSHBUTTON_A,
  SENSOR_A,
  UNUSED_DI3,
  UNUSED_DI4,
  PUSHBUTTON_B,
  SENSOR_B,
  UNUSED_DI7,
  UNUSED_DI8
};

enum class DigitalOutput : uint8_t {
  DO1 = 0,
  DO2,
  DO3,
  DO4,
  DO5,
  DO6,
  DO7,
  DO8
};