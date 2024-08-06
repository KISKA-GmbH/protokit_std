//
// Created by f.wimmer on 7/11/2024.
//

#ifndef PROTOKIT_STD_ONBUTTONREGISTER_H
#define PROTOKIT_STD_ONBUTTONREGISTER_H


#include "OneEventRegister.h"
#include "ArduinoButton.h"
#include "SignalEvent.h"

/**
 * Takes a Button event and makes it readable as a SignalEvent
 */
class OnButtonRegister : public ButtonReceiver, public SignalEvent {
public:
    explicit OnButtonRegister(ArduinoButton &button, TriggerType triggerType);

    ~OnButtonRegister() override;

    void onButtonEvent(ArduinoButton *button, TriggerType event) override;


private:
    ArduinoButton &button;
    TriggerType triggerType;
};


#endif //PROTOKIT_STD_ONBUTTONREGISTER_H
