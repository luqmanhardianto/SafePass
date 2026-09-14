#include "InterLock.h"
#include "Config.h"

void Interlock::begin(Door &doorA, Door &doorB) {
  this->doorA = &doorA;
  this->doorB = &doorB;
  state = State::IDLE;
}

void Interlock::update();
Interlock::State Interlock::getState() const;
bool Interlock::isFault() const;