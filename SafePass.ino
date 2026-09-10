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
  if (di_1_state) {
    output.writeOutput(DigitalOutput::DO1, !di_1_state);
  } else {
    output.writeOutput(DigitalOutput::DO1, !di_1_state);
  }
  Serial.print("DI1 : ");
  Serial.print(di_1_state);
  Serial.print(" | DO1 : ");
  Serial.println(output.readOutput(DigitalOutput::DO1));
}
