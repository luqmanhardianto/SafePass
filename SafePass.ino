#include "InputManager.h"

InputManager io;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  // set DI1-8 to input
  io.begin();
  // pinMode(4, INPUT_PULLDOWN);

  Serial.println("status inputs: ");
}

void loop() {
  // put your main code here, to run repeatedly:
  bool di_1_state = io.readInput(DigitalInput::DI1);
  Serial.println(di_1_state);
  delay(1);
}
