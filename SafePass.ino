#include "PushButton.h"
#include "HardwareMap.h"

PushButton buttonA;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(500);

  buttonA.begin(InputFunction::PUSHBUTTON_A);
  Serial.print("pin buttonA :");
  Serial.println(buttonA.getPin());
}

void loop() {
  buttonA.readState();
  Serial.print("buttonA:");
  Serial.println(buttonA.isPressed());
}
