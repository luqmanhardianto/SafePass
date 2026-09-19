#include "HardwareMap.h"
#include "PushButton.h"
#include "LockStatus.h"
#include "Lock.h"
#include "Indicator.h"
#include "TCA9554.h"
#include "Door.h"
#include "InterLock.h"

// define Input object DoorA
PushButton pushButtonA;
LockStatus lockStatusA;
Lock lockA;
Indicator pilotLampGreenA;
Indicator pilotLampRedA;
Door doorA;

// define Input object DoorB
PushButton pushButtonB;
LockStatus lockStatusB;
Lock lockB;
Indicator pilotLampGreenB;
Indicator pilotLampRedB;
Door doorB;

// define TCA9554
TCA9554 tca9554;

Interlock interlock;

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

  lockStatusA.begin(DigitalInput::DI2);
  lockStatusB.begin(DigitalInput::DI6);

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
    lockStatusA,
    lockA,
    pilotLampRedA,
    pilotLampGreenA);

  doorB.begin(
    pushButtonB,
    lockStatusB,
    lockB,
    pilotLampRedB,
    pilotLampGreenB);

  // Interlock
  interlock.begin(doorA, doorB);

  // init safe state
  doorA.lock();
  doorB.lock();

  Serial.println("interlock init");
  Serial.println("state :");
  // Serial.println(getStateName(interlock.getState()));
}

void loop() {
  // update physical input

  pushButtonA.readState();
  pushButtonB.readState();

  lockStatusA.readState();
  lockStatusB.readState();

  Serial.println(lockStatusA.isLocked());

  interlock.update();
}
