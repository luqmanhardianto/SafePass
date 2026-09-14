#include "InterLock.h"
#include "Config.h"

void Interlock::begin(Door &doorA, Door &doorB) {
  this->doorA = &doorA;
  this->doorB = &doorB;
  state = State::IDLE;
}

void Interlock::update() {
  // safety invariant:
  // both doors must never be open at the same time.
  if (doorA->isOpen() && doorB->isOpen()) {
    state = State::FAULT;
    return;
  }

  // safety invariant:
  // both door must never be command unlocked at the same time.
  if (doorA->isLocked() == false && doorB->isLocked() == false) {
    state = State::FAULT;
    return;
  }
}

Interlock::State Interlock::getState() const {
  return state;
}

bool Interlock::isFault() const {
  return state == State::FAULT;
}