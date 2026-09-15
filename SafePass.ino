#include "HardwareMap.h"
#include "PushButton.h"
#include "DoorSensor.h"
#include "Lock.h"
#include "Indicator.h"
#include "TCA9554.h"
#include "Door.h"
#include "InterLock.h"

// define Input object DoorA
PushButton pushButtonA;
DoorSensor doorSensorA;
Lock lockA;
Indicator pilotLampGreenA;
Indicator pilotLampRedA;
Door doorA;

// define Input object DoorB
PushButton pushButtonB;
DoorSensor doorSensorB;
Lock lockB;
Indicator pilotLampGreenB;
Indicator pilotLampRedB;
Door doorB;

// define TCA9554
TCA9554 tca9554;

Interlock interlock;

const char *getStateName(Interlock::State state) {
  switch (state) {
    case Interlock::State::IDLE:
      return "IDLE";
    case Interlock::State::RELEASE_A:
      return "RELEASE_A";
    case Interlock::State::DOOR_A_OPEN:
      return "DOOR_A_OPEN";
    case Interlock::State::RELEASE_B:
      return "RELEASE_B";
    case Interlock::State::DOOR_B_OPEN:
      return "DOOR_B_OPEN";
    case Interlock::State::FAULT:
      return "FAULT";
    default:
      return "UNKNOWN";
  }
}

void setup() {
  Serial.begin(115200);
  delay(500);
  // init tca9554
  Serial.println();
  Serial.println("safepass interlock test");

  if (!tca9554.begin()) {
    Serial.println("ERROR: TCA9554 init failed");
    return;
  }

  Serial.println("TCA9554 ok");

  // Init digital inputs.
  pushButtonA.begin(DigitalInput::DI1);
  pushButtonB.begin(DigitalInput::DI5);

  doorSensorA.begin(DigitalInput::DI2);
  doorSensorB.begin(DigitalInput::DI6);

  delay(150);

  // init digital output
  if (!lockA.begin(tca9554, DigitalOutput::DO1)) {
    Serial.println("ERROR: lock A init failed");
    return;
  }

  if (!pilotLampGreenA.begin(tca9554, DigitalOutput::DO2)) {
    Serial.println("ERROR: green A init failed");
    return;
  }

  if (!pilotLampRedA.begin(tca9554, DigitalOutput::DO3)) {
    Serial.println("ERROR: red A init failed");
    return;
  }

  if (!lockB.begin(tca9554, DigitalOutput::DO5)) {
    Serial.println("ERROR: lock B init failed");
    return;
  }

  if (!pilotLampGreenB.begin(tca9554, DigitalOutput::DO6)) {
    Serial.println("ERROR: green B init failed");
    return;
  }

  if (!pilotLampRedB.begin(tca9554, DigitalOutput::DO7)) {
    Serial.println("ERROR: red B init failed");
    return;
  }

  doorA.begin(
    pushButtonA,
    doorSensorA,
    lockA,
    pilotLampRedA,
    pilotLampGreenA);

  doorB.begin(
    pushButtonB,
    doorSensorB,
    lockB,
    pilotLampRedB,
    pilotLampGreenB);

  // Interlock
  interlock.begin(doorA, doorB);

  // init safe state
  doorA.lock();
  doorB.lock();

  Serial.println("interlock init");
  Serial.print("state :");
  Serial.println(getStateName(interlock.getState()));
}

void loop() {
  // update physical input

  pushButtonA.readState();
  pushButtonB.readState();

  doorSensorA.readState();
  doorSensorB.readState();

  interlock.update();
}
