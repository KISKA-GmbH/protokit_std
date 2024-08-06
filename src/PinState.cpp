//
// Created by f.wimmer on 7/11/2024.
//

#include <Arduino.h>
#include "PinState.h"

// Default constructor
PinState::PinState(int pin, PinMode mode) : pin{pin} {
    // get requested pin pull mode
    uint8_t inputType = INPUT;
    if (mode == PinMode::PullDown) {
#if defined(ESP32)
        inputType = INPUT_PULLDOWN;
#endif
    } else if (mode == PinMode::PullUp) {
        inputType = INPUT_PULLUP;
    }

#if defined(ARDUINO_ARCH_STM32F1)
    pinMode(pin, (WiringPinMode)inputType);
#else
    pinMode(pin, inputType);
#endif

    // Initialize the pin state to a default value
    state = digitalRead(pin);
}

void PinState::loop() {
    auto currentState = digitalRead(pin);

    if (currentState != this->state) {
        stableCounter++;
    } else if (stableCounter > 0) {
        stableCounter--;
    }

    if (stableCounter < 5) {
        return;
    }
    stableCounter = 0;

    if (state == 1 && currentState == 0) {
        lastChangeState = ChangeState::falling;
    } else if (state == 0 && currentState == 1) {
        lastChangeState = ChangeState::rising;
    } else {
        lastChangeState = ChangeState::none;
    }
    state = currentState;
}

void PinState::resetChangeState() {
    this->lastChangeState = ChangeState::none;
}

ChangeState PinState::getChangeState() const {
    return lastChangeState;
}

int PinState::getState() const {
    return this->state;
}
