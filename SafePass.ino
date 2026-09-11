#include "HardwareMap.h"
#include "PushButton.h"
#include "DoorSensor.h"

// define Input object
PushButton pushButtonA;
DoorSensor doorSensorA;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(500);

  // init Digital input to inputObject
  pushButtonA.begin(DigitalInput::DI1);
  doorSensorA.begin(DigitalInput::DI2);
}

void loop() {
  pushButtonA.readState();
  Serial.print("buttonA:");
  Serial.print(pushButtonA.isPressed());

  doorSensorA.readState();
  Serial.print(" | doorSensorA:");
  Serial.println(doorSensorA.isLocked());
}
