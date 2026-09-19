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
    doorA->isPhysicallyUnlocked() && doorB->isPhysicallyUnlocked();

  bool bothLocksUnlocked =
    !doorA->isLocked() && !doorB->isLocked();


  if (bothDoorsOpen) {
    enterFault();
  }

  if (bothLocksUnlocked) {
    enterFault();
  }

  switch (state) {
    case State::IDLE:
      // ignore button requests until both buttons
      // used for fault reset have been released.
      if (faultResetWaitForRelease) {

        if (!doorA->isButtonPressed() && !doorB->isButtonPressed()) {
          faultResetWaitForRelease = false;
        }

        break;
      }

      // both buttons pressed at the same time.
      // reject both requests.
      if (doorA->isButtonPressed() && doorB->isButtonPressed()) {
        break;
      }

      // request Door A.
      if (doorA->isButtonPressed()) {

        if (doorA->isPhysicallyLocked() && doorB->isPhysicallyLocked() && doorA->isLocked()) {

          if (doorA->unlock()) {

            unlockStartTime = millis();
            unlockTiming = true;

            state = State::RELEASE_A;
          }
        }

        break;
      }

      // request Door B.
      if (doorB->isButtonPressed()) {

        if (doorA->isPhysicallyLocked() && doorB->isPhysicallyLocked() && doorB->isLocked()) {

          if (doorB->unlock()) {

            unlockStartTime = millis();
            unlockTiming = true;

            state = State::RELEASE_B;
          }
        }

        break;
      }

      break;

    case State::RELEASE_A:
      // door A has ben released.
      // wait for the physical door to open.
      if (doorA->isPhysicallyUnlocked()) {

        unlockTiming = false;
        unlockStartTime = 0;

        state = State::DOOR_A_OPEN;
        break;
      }

      if (unlockTiming && millis() - unlockStartTime >= UNLOCK_TIMEOUT_MS) {

        unlockTiming = false;
        unlockStartTime = 0;

        if (doorA->lock()) {
          state = State::IDLE;
        } else {
          enterFault();
        }
      }

      break;

    case State::DOOR_A_OPEN:
      // door A is open
      // door B cannot be released
      // wait until Door A closes
      if (doorA->isPhysicallyLocked()) {
        state = State::WAIT_LOCK_A;
      }

      break;

    case State::WAIT_LOCK_A:

      if (!lockConfirmTiming) {

        if (doorA->lock()) {
          lockCOnfirmStartTime = millis();
          lockConfirmTiming = true;
        } else {
          enterFault();
        }

        break;
      }

      if (doorA->isPhysicallyLocked()) {
        lockConfirmTiming = false;
        lockCOnfirmStartTime = 0;

        state = State::IDLE;
        break;
      }

      if (millis() - lockCOnfirmStartTime >= LOCK_CONFIRM_TIMEOUT_MS) {
        lockConfirmTiming = false;
        lockCOnfirmStartTime = 0;

        enterFault();
      }

      break;

    case State::RELEASE_B:
      // door B has been released
      // wait for the physical door to open
      if (doorB->isPhysicallyUnlocked()) {

        unlockTiming = false;
        unlockStartTime = 0;

        state = State::DOOR_B_OPEN;
        break;
      }

      if (unlockTiming && millis() - unlockStartTime >= UNLOCK_TIMEOUT_MS) {

        unlockTiming = false;
        unlockStartTime = 0;

        if (doorB->lock()) {
          state = State::IDLE;
        } else {
          enterFault();
        }
      }

      break;

    case State::DOOR_B_OPEN:

      // door B is open
      // door A cannot be released.
      // wait until Door B closes
      if (doorB->isPhysicallyLocked()) {
        state = State::WAIT_LOCK_B;
      }

      break;

    case State::WAIT_LOCK_B:

      if (!lockConfirmTiming) {

        if (doorB->lock()) {

          lockCOnfirmStartTime = millis();
          lockConfirmTiming = true;
        } else {
          enterFault();
        }

        break;
      }

      if (doorB->isPhysicallyLocked()) {

        lockConfirmTiming = false;
        lockCOnfirmStartTime = 0;

        state = State::IDLE;
        break;
      }

      if (millis() - lockCOnfirmStartTime >= LOCK_CONFIRM_TIMEOUT_MS) {

        lockConfirmTiming = false;
        lockCOnfirmStartTime = 0;

        enterFault();
      }

      break;

    case State::FAULT:
      updateFaultReset();
      break;
  }
  if (state == State::FAULT) {
    updateFaultIndicators();
  } else {
    updateIndicators();
  }
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

void Interlock::enterFault() {
  // prevent repeated fault-entry actions
  if (state == State::FAULT) {
    return;
  }

  // command both doors to locked state
  doorA->lock();
  doorB->lock();

  // enter latched fault state
  state = State::FAULT;

  // reset fault indicator blinking
  faultIndicatorLastToggleTime = millis();
  faultIndicatorBlinkState = false;
}

void Interlock::updateFaultIndicators() {
  bool doorASafe =
    doorA->isPhysicallyLocked();

  bool doorBSafe =
    doorB->isPhysicallyLocked();

  unsigned long currentTime = millis();

  if ((currentTime - faultIndicatorLastToggleTime) >= FAULT_INDICATOR_BLINK_MS) {
    faultIndicatorLastToggleTime = currentTime;
    faultIndicatorBlinkState = !faultIndicatorBlinkState;
  }

  // green indicators are always off during FAULT
  doorA->greenOff();
  doorB->greenOff();

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
      doorB->redOff();
    }

  } else {
    doorB->redOn();
  }

  // green indicator ar disabled durinf fault
  doorA->greenOff();
  doorB->greenOff();
}

void Interlock::updateFaultReset() {
  // if reset already happened, wait for both buttons
  // to be released before allowing another reset
  if (faultResetWaitForRelease) {

    if (!doorA->isButtonPressed() && doorB->isButtonPressed()) {
      faultResetWaitForRelease = false;
    }

    return;
  }

  bool bothButtonsPressed =
    doorA->isButtonPressed() && doorB->isButtonPressed();

  // start reset timing
  if (bothButtonsPressed && !faultResetTiming) {
    faultRestStartTime = millis();
    faultResetTiming = true;
  }

  // cancel timing if either button is released
  if (!bothButtonsPressed && faultResetTiming) {
    faultResetTiming = false;
    faultRestStartTime = 0;
  }

  // check whether both buttons have been held long enough
  if (bothButtonsPressed && faultResetTiming) {

    if (millis() - faultRestStartTime >= FAULT_RESET_HOLD_MS) {

      faultResetTiming = false;
      faultRestStartTime = 0;

      bool doorASafe =
        doorA->isPhysicallyLocked() && doorA->isLocked();

      bool doorBSafe =
        doorB->isPhysicallyLocked() && doorB->isLocked();

      // reset is allowed only when both doors are safe
      if (doorASafe && doorBSafe) {
        state = State::IDLE;
        faultResetWaitForRelease = true;
      }
    }
  }
}

Interlock::State Interlock::getState() const {
  return state;
}

bool Interlock::isFault() const {
  return state == State::FAULT;
}