
#pragma once

#include <Arduino.h>
#include <stdint.h>

#include "Door.h"

class Interlock {
public:
  enum class State : uint8_t {
    IDLE,
    RELEASE_A,
    DOOR_A_OPEN,
    RELEASE_B,
    DOOR_B_OPEN,
    FAULT
  };

private:
  Door *doorA;
  Door *doorB;
  State state = State::IDLE;

  void updateIndicators();

  // fault indicator blinking
  unsigned long faultIndicatorLastToggleTime = 0;
  bool faultIndicatorBlinkState = false;

  // helpoer fault indicator
  void updateFaultIndicators();

public:
  void begin(Door &doorA, Door &doorB);

  void update();
  State getState() const;
  bool isFault() const;
};