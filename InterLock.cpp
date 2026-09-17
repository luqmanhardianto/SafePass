#include "esp32-hal.h"
#include <sys/_types.h>
#include "HardwareSerial.h"
#include "InterLock.h"
#include "Config.h"
#include "Door.h"
#include <Arduino.h>

void Interlock::begin(Door &doorA, Door &doorB) {
  this->doorA = &doorA;
  this->doorB = &doorB;
  state = State::IDLE;

  updateIndicators();
}

void Interlock::update() {

  bool bothDoorsOpen =
    doorA->isOpen() && doorB->isOpen();

  bool bothLocksUnlocked =
    !doorA->isLocked() && !doorB->isLocked();


  if (bothDoorsOpen) {
    state = State::FAULT;
    updateIndicators();
    return;
  }

  if (bothLocksUnlocked) {
    state = State::FAULT;
    updateIndicators();
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

  updateIndicators();
}

void Interlock::updateIndicators() {
  switch (state) {
    case State::IDLE:

      // both doors available
      doorA->redOff();
      doorA->greenOn();

      doorB->redOff();
      doorB->greenOn();
      break;

    case State::RELEASE_A:
    case State::DOOR_A_OPEN:
      // door A is active
      // door B is unavailable
      doorA->redOff();
      doorA->greenOn();

      doorB->redOn();
      doorB->greenOff();
      break;

    case State::RELEASE_B:
    case State::DOOR_B_OPEN:
      // door B is active
      // door A is unavailable
      doorA->redOn();
      doorA->greenOff();

      doorB->redOff();
      doorB->greenOn();
      break;

    case State::FAULT:
      // fault condition
      // both doors unavailable
      doorA->redOn();
      doorA->greenOff();

      doorB->redOn();
      doorB->greenOff();
      break;
  }
}

void Interlock::updateFaultIndicators() {
  bool doorASafe =
    doorA->isClosed() && doorA->isLocked();

  bool doorBSafe =
    doorB->isClosed() && doorB->isLocked();

  unsigned long currentTime = millis();

  if (currentTime - faultIndicatorLastToggleTime >= FAULT_INDICATOR_BLINK_MS) {
    faultIndicatorLastToggleTime = currentTime;
    faultIndicatorBlinkState = !faultIndicatorBlinkState;
  }

  // door A fault indication
  if (doorASafe) {
    if (faultIndicatorBlinkState) {
      doorA->redOn();
    } else {
      doorA->redOff();
    }

  } else {
    doorA->redOn();
  }

  // door B fault indication
  if (doorBSafe) {
    if (faultIndicatorBlinkState) {
      doorB->redOn();
    } else {
      doorB->greenOff();
    }

  } else {
    doorB->redOn();
  }

  // green indicator ar disabled durinf fault
  doorA->greenOff();
  doorB->greenOff();
}

Interlock::State Interlock::getState() const {
  return state;
}

bool Interlock::isFault() const {
  return state == State::FAULT;
}