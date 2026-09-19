
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
    WAIT_LOCK_A,
    RELEASE_B,
    DOOR_B_OPEN,
    WAIT_LOCK_B,
    FAULT
  };

private:
  // door object
  Door *doorA;
  Door *doorB;

  // default state
  State state = State::IDLE;

  // fault indicator blinking
  unsigned long faultIndicatorLastToggleTime = 0;
  bool faultIndicatorBlinkState = false;

  // fault reset timing
  unsigned long faultRestStartTime = 0;
  bool faultResetTiming = false;
  bool faultResetWaitForRelease = false;

  // unlock timeout
  unsigned long unlockStartTime = 0;
  bool unlockTiming = false;

  // internal func helper
  void enterFault();
  void updateIndicators();
  void updateFaultIndicators();
  void updateFaultReset();
public:
  void begin(Door &doorA, Door &doorB);

  void update();
  State getState() const;
  bool isFault() const;
};