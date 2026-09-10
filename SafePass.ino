#include "InputManager.h"
#include "OutputManager.h"

InputManager input;

OutputManager output;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(500);

  // set DI1-8 to input
  input.begin();

  Serial.println();
  Serial.println("OutputManager test");

  if (!output.begin()) {
    Serial.println("error : tca9554 not detected");
    return;
  }

  Serial.println("tca9554 initialized");
}

void loop() {
  // put your main code here, to run repeatedly:
  bool di_1_state = input.readInput(DigitalInput::DI1);
  output.writeOutput(DigitalOutput::DO8, true);
  delay(1000);
  output.writeOutput(DigitalOutput::DO8, false);
  delay(1000);
  Serial.println(di_1_state);
}
