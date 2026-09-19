#include "Door.h"

void Door::begin(
  PushButton &pushButton,
  LockStatus &lockStatus,
  Lock &lock,
  Indicator &redIndicator,
  Indicator &greenIndicator) {
  this->pushButton = &pushButton;
  this->lockStatus = &lockStatus;
  this->doorlock = &lock;
  this->redIndicator = &redIndicator;
  this->greenIndicator = &greenIndicator;
}

bool Door::isButtonPressed() const {
  return pushButton->isPressed();
}

bool Door::isPhysicallyLocked() const {
  return lockStatus->isLocked();
}

bool Door::isLocked() const {
  return doorlock->isLocked();
}
bool Door::isPhysicallyUnlocked() const {
  return !lockStatus->isLocked();
}

bool Door::lock() {
  return doorlock->lock();
}

bool Door::unlock() {
  return doorlock->unlock();
}

bool Door::redOn() {
  return redIndicator->on();
}

bool Door::redOff() {
  return redIndicator->off();
}

bool Door::greenOn() {
  return greenIndicator->on();
}

bool Door::greenOff() {
  return greenIndicator->off();
}