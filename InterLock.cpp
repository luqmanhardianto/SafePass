#include "InterLock.h"
#include "Config.h"

void Interlock::begin(Door &doorA, Door &doorB);

void Interlock::update();
Interlock::State Interlock::getState() const;
bool Interlock::isFault() const;