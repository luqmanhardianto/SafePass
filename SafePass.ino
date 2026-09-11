#include "HardwareMap.h"
#include "PushButton.h"
#include "DoorSensor.h"

// define Input object DoorA
PushButton pushButtonA;
DoorSensor doorSensorA;

// define Input object DoorB
PushButton pushButtonB;
DoorSensor doorSensorB;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  // init Digital input to input Object DoorA
  pushButtonA.begin(DigitalInput::DI1);
  doorSensorA.begin(DigitalInput::DI2);

  pushButtonB.begin(DigitalInput::DI5);
  doorSensorB.begin(DigitalInput::DI6);
}

void loop() {
  pushButtonA.readState();
  Serial.print("buttonA:");
  Serial.print(pushButtonA.isPressed());

  doorSensorA.readState();
  Serial.print(" | doorSensorA:");
  Serial.print(doorSensorA.isClosed());

  pushButtonB.readState();
  Serial.print(" | buttonB:");
  Serial.print(pushButtonB.isPressed());

  doorSensorB.readState();
  Serial.print(" | doorSensorB:");
  Serial.println(doorSensorB.isClosed());
}
