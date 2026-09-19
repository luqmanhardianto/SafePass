#pragma once

#include <Arduino.h>

#include "PushButton.h"
#include "LockStatus.h"
#include "Lock.h"
#include "Indicator.h"

class Door {
private:
  PushButton *pushButton;
  LockStatus *lockStatus;
  Lock *doorlock;
  Indicator *redIndicator;
  Indicator *greenIndicator;
public:
  void begin(
    PushButton &pushButton,
    LockStatus &lockStatus,
    Lock &lock,
    Indicator &redIndicator,
    Indicator &greenIndicator);

  bool isButtonPressed() const;

  bool isPhysicallyLocked() const;
  bool isPhysicallyUnlocked() const;


  bool isLocked() const;

  bool lock();
  bool unlock();

  bool redOn();
  bool redOff();

  bool greenOn();
  bool greenOff();
};