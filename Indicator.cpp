#include "Indicator.h"

bool Indicator::begin(TCA9554 &tca9554, DigitalOutput output);
bool Indicator::on();
bool Indicator::off();
bool Indicator::isOn() const;