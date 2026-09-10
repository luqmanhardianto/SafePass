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

constexpr uint8_t DI_PINS[]={
  4,5,6,7,8,9,10,11
};