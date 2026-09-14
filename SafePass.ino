#include "HardwareMap.h"
#include "PushButton.h"
#include "DoorSensor.h"
#include "Lock.h"
#include "TCA9554.h"

// define Input object DoorA
PushButton pushButtonA;
DoorSensor doorSensorA;
Lock lockA;

// define Input object DoorB
PushButton pushButtonB;
DoorSensor doorSensorB;
Lock lockB;

// define TCA9554
TCA9554 tca9554;

void setup() {
  Serial.begin(115200);
  delay(500);
  // init tca9554
  if (tca9554.begin()) {
    Serial.println("tca9554 ok");
  } else {
    Serial.println("tca9554 error");
  }

  // Init digital inputs.
  pushButtonA.begin(DigitalInput::DI1);
  doorSensorA.begin(DigitalInput::DI2);

  pushButtonB.begin(DigitalInput::DI5);
  doorSensorB.begin(DigitalInput::DI6);

  // init digital output
  lockA.begin(tca9554, DigitalOutput::DO1);
  lockB.begin(tca9554, DigitalOutput::DO5);

  Serial.println("SafePass Lock/TCA9554 test started");
}

void loop() {
  pushButtonA.readState();
  if (pushButtonA.isPressed()) {
    lockA.lock();
  } else {
    lockA.unlock();
  }

  pushButtonB.readState();
  if (pushButtonB.isPressed()) {
    lockB.lock();
  } else {
    lockB.unlock();
  }
}
