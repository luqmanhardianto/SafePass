#include "HardwareMap.h"
#include "PushButton.h"
#include "DoorSensor.h"
#include "Lock.h"
#include "Indicator.h"
#include "TCA9554.h"
#include "Door.h"

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
  pilotLampGreenA.begin(tca9554, DigitalOutput::DO2);
  pilotLampRedA.begin(tca9554, DigitalOutput::DO3);

  lockB.begin(tca9554, DigitalOutput::DO5);
  pilotLampGreenB.begin(tca9554, DigitalOutput::DO6);
  pilotLampRedB.begin(tca9554, DigitalOutput::DO7);

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
}

void loop() {
  pushButtonA.readState();
  doorSensorA.readState();
  Serial.print("pbA: ");
  Serial.print(doorA.isButtonPressed());

  Serial.print(" | closed: ");
  Serial.print(doorA.isClosed());

  Serial.print(" | open: ");
  Serial.print(doorA.isOpen());

  Serial.print(" | locked: ");
  Serial.println(doorA.isLocked());
}
