//
// Created by f.wimmer on 7/11/2024.
//

#ifndef PROTOKIT_STD_SIGNALEVENT_H
#define PROTOKIT_STD_SIGNALEVENT_H


#include "OneEventRegister.h"

/**
 * A signal that can be set and is auto cleared as soon as it is read.
 */
class SignalEvent : public EventStoreReadable<bool>, public OneEventStoreWritable {
public:
    bool collect() override {
        auto wasSet = _isSet;
        clear();
        return wasSet;
    }

    void set() override {
        _isSet = true;
    }

    void clear() override {
        _isSet = false;
    }

private:
    bool _isSet = false;
};


#endif //PROTOKIT_STD_SIGNALEVENT_H
