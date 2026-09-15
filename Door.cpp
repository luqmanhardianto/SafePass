#include "Door.h"

void Door::begin(
  PushButton &pushButton,
  DoorSensor &doorSensor,
  Lock &lock,
  Indicator &redIndicator,
  Indicator &greenIndicator) {
  this->pushButton = &pushButton;
  this->doorSensor = &doorSensor;
  this->doorlock = &lock;
  this->redIndicator = &redIndicator;
  this->greenIndicator = &greenIndicator;
}

bool Door::isButtonPressed() const {
  return pushButton->isPressed();
}

bool Door::isClosed() const {
  return doorSensor->isClosed();
}

bool Door::isLocked() const {
  return doorlock->isLocked();
}
bool Door::isOpen() const {
  return !doorSensor->isClosed();
}

bool Door::lock() {
  return doorlock->lock();
}

bool Door::unlock() {
  return doorlock->unlock();
}

bool Door::redOn(){
  return redIndicator->on();
}

bool Door::redOff(){
  return redIndicator->off();
}

bool Door::greenOn();
bool Door::greenOff();