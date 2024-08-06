
// Created by f.wimmer on 7/11/2024.
//

#include "OnButtonRegister.h"

OnButtonRegister::OnButtonRegister(ArduinoButton &button, TriggerType triggerType) : button(button),
                                                                                     triggerType(triggerType) {
    button.addReceiver(this);
}

void OnButtonRegister::onButtonEvent(ArduinoButton *button, TriggerType event) {
    if (event == triggerType) {
        this->set();
    }
}

OnButtonRegister::~OnButtonRegister() {
    button.removeReceiver(this);
}
