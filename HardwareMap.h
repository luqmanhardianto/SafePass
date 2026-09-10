#pragma once

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

constexpr uint8_t DI_PINS[] = {
  4, 5, 6, 7, 8, 9, 10, 11
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