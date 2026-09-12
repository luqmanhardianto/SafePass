#include "HardwareMap.h"
#include "PushButton.h"
#include "DoorSensor.h"
#include "Lock.h"

// define Input object DoorA
PushButton pushButtonA;
DoorSensor doorSensorA;
Lock lockA;

// define Input object DoorB
PushButton pushButtonB;
DoorSensor doorSensorB;
Lock lockB;

// Bench test state machine for the shared TCA9554 outputs.
// 0: A locked, B unlocked
// 1: A locked, B locked
// 2: A unlocked, B locked
// 3: A unlocked, B unlocked
uint8_t lockTestStep = 0;
unsigned long lastLockTestTime = 0;
constexpr unsigned long LOCK_TEST_INTERVAL_MS = 2000;

void runLockTest() {
  const unsigned long now = millis();

  if ((now - lastLockTestTime) < LOCK_TEST_INTERVAL_MS) {
    return;
  }

  lastLockTestTime = now;

  switch (lockTestStep) {
    case 0:
      lockA.lock();
      lockB.unlock();
      Serial.println("TEST: A=LOCKED  B=UNLOCKED");
      break;

    case 1:
      lockA.lock();
      lockB.lock();
      Serial.println("TEST: A=LOCKED  B=LOCKED");
      break;

    case 2:
      lockA.unlock();
      lockB.lock();
      Serial.println("TEST: A=UNLOCKED  B=LOCKED");
      break;

    case 3:
      lockA.unlock();
      lockB.unlock();
      Serial.println("TEST: A=UNLOCKED  B=UNLOCKED");
      break;
  }

  lockTestStep = (lockTestStep + 1) % 4;
}

void setup() {
  Serial.begin(115200);

  // Init digital inputs.
  pushButtonA.begin(DigitalInput::DI1);
  doorSensorA.begin(DigitalInput::DI2);

  pushButtonB.begin(DigitalInput::DI5);
  doorSensorB.begin(DigitalInput::DI6);

  // Init two Lock objects using two bits of the same TCA9554.
  lockA.begin(DigitalOutput::DO1);
  lockB.begin(DigitalOutput::DO2);

  Serial.println("SafePass Lock/TCA9554 test started");
}

void loop() {
  pushButtonA.readState();
  doorSensorA.readState();
  pushButtonB.readState();
  doorSensorB.readState();

  // runLockTest();
}
