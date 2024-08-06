//
// Created by f.wimmer on 7/11/2024.
//

#include "Arduino.h"
#include "EventToSerialReceiver.h"

EventToSerialReceiver::EventToSerialReceiver(EventStoreReadable<bool> &eventRegister, char *message) :
        eventRegister(eventRegister), message{message} {}

void EventToSerialReceiver::loop() {
    if (eventRegister.collect()) {
        Serial.println(message);
    }
}
