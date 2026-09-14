#include "HardwareMap.h"
#include "PushButton.h"
#include "DoorSensor.h"
#include "Lock.h"
#include "TCA9554.h"

// define Input object DoorA
PushButton pushButtonA;
DoorSensor doorSensorA;

// define Input object DoorB
PushButton pushButtonB;
DoorSensor doorSensorB;


// define TCA9554
TCA9554 tca9554;

void setup() {
  Serial.begin(115200);
  delay(500);
  // Init digital inputs.
  pushButtonA.begin(DigitalInput::DI1);
  doorSensorA.begin(DigitalInput::DI2);

  pushButtonB.begin(DigitalInput::DI5);
  doorSensorB.begin(DigitalInput::DI6);

  // init tca9554
  if (tca9554.begin()) {
    Serial.println("tca9554 ok");
  } else {
    Serial.println("tca9554 error");
  }

  Serial.println("SafePass Lock/TCA9554 test started");
}

void loop() {

}
