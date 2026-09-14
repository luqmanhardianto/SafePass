#include "Door.h"

void Door::begin(
  PushButton &pushButton,
  DoorSensor &doorSensor,
  Lock &lock,
  Indicator &redIndicator,
  Indicator &greenIndicator) {
  this->pushButton = &pushButton;
  this->doorSensor = &doorSensor;
  this->lock = &lock;
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
  return lock->isLocked();
}
bool Door::isOpen() const {
  return !doorSensor->isClosed();
}

bool Door::lock(){
  return lock->lock();
}

bool Door::unlock(){
  return lock->unlock();
}