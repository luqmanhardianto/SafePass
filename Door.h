#pragma once

#include <Arduino.h>

#include "PushButton.h"
#include "DoorSensor.h"
#include "Lock.h"
#include "Indicator.h"

class Door {
private:
  PushButton *pushButton;
  DoorSensor *doorSensor;
  Lock *doorlock;
  Indicator *redIndicator;
  Indicator *greenIndicator;
public:
  void begin(
    PushButton &pushButton,
    DoorSensor &doorSensor,
    Lock &lock,
    Indicator &redIndicator,
    Indicator &greenIndicator);

  bool isButtonPressed() const;
  bool isClosed() const;
  bool isLocked() const;
  bool isOpen() const;

  bool lock();
  bool unlock();

  bool redOn();
  bool redOff();

  bool greenOn();
  bool greenOff();
};