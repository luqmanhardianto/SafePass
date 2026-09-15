#include "InterLock.h"
#include "Config.h"
#include "Door.h"

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

  switch (state) {
    case State::IDLE:
      // both buttons pressed at the same time.
      // reject both requests.
      if (doorA->isButtonPressed() && doorB->isButtonPressed()) {
        break;
      }

      // request Door A.
      if (doorA->isButtonPressed()) {

        if (doorA->isClosed() && doorB->isClosed() && doorB->isLocked()) {

          if (doorA->unlock()) {
            state = State::RELEASE_A;
          }
        }
        break;
      }

      // request Door B.
      if (doorB->isButtonPressed()) {

        if (doorA->isClosed() && doorB->isClosed() && doorA->isLocked()) {

          if (doorB->unlock()) {
            state = State::RELEASE_B;
          }
        }
        break;
      }

      break;
      
    case State::RELEASE_A:
      // door A has ben released.
      // wait for the physical door to open.
      if (doorA->isOpen()) {
        state = State::DOOR_A_OPEN;
      }

      break;
  }
}

Interlock::State Interlock::getState() const {
  return state;
}

bool Interlock::isFault() const {
  return state == State::FAULT;
}