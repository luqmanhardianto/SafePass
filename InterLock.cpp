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

    case State::DOOR_A_OPEN:
      // door A is open
      // door B cannot be released
      // wait until Door A closes
      if (doorA->isClosed()) {
        if (doorA->lock()) {
          state = State::IDLE;
        }
      }

      break;

    case State::RELEASE_B:
      // door B has been released
      // wait for the physical door to open
      if (doorB->isOpen()) {
        state = State::DOOR_B_OPEN;
      }

      break;

    case State::DOOR_B_OPEN:

      // door B is open
      // door A cannot be released.
      // wait until Door B closes
      if (doorB->isClosed()) {

        if (doorB->lock()) {
          state = State::IDLE;
        }
      }

      break;

    case State::FAULT:
      // stay in FAULT for now
      // recovery behavior will be defined later
      break;
  }
}

Interlock::State Interlock::getState() const {
  return state;
}

bool Interlock::isFault() const {
  return state == State::FAULT;
}