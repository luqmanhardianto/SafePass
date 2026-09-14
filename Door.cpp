#include "Door.h"

void Door::begin(
  PushButton &pushButton,
  DoorSensor &doorSensor,
  Lock &lock,
  Indicator &redIndicator,
  Indicator &greenIndicator){
    this->pushButton = &pushButton;
    this->doorSensor=&doorSensor;
    this->lock=&lock;
    this->redIndicator=&redIndicator;
    this->greenIndicator= &greenIndicator;
  }

bool Door::isButtonPressed() const{
  return pushButton->isPressed();
}

bool Door::isClosed() const{
  return doorSensor->isClosed();
}
bool Door::isLocked() const;
bool Door::isOpen() const;