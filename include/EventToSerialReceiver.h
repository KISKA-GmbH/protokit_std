//
// Created by f.wimmer on 7/11/2024.
//

#ifndef PROTOKIT_STD_EVENTTOSERIALRECEIVER_H
#define PROTOKIT_STD_EVENTTOSERIALRECEIVER_H


#include "OneEventRegister.h"

/**
 * Write a message to the serial port when an event is set
 */
class EventToSerialReceiver {
public:
    explicit EventToSerialReceiver(EventStoreReadable<bool> &eventRegister, char* message);

    void loop();


private:
    EventStoreReadable<bool> &eventRegister;
    char *message;

};


#endif //PROTOKIT_STD_EVENTTOSERIALRECEIVER_H
