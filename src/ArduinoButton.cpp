//
// Created by f.wimmer on 7/11/2024.
//

#include <Arduino.h>
#include "ArduinoButton.h"

ArduinoButton::ArduinoButton(uint32_t shortPressDuration, uint32_t longPressDuration)
        : _shortPressDuration{shortPressDuration}, _longPressDuration{longPressDuration} {
}

ArduinoButton::ArduinoButton(uint8_t pin, PinMode mode,
                             TriggerType trigger,
                             uint32_t shortPressDuration,
                             uint32_t longPressDuration)
        : ArduinoButton{shortPressDuration, longPressDuration} {
    configure(pin, mode, trigger);
}

void ArduinoButton::loop() {
    _button.update();

    if (_button.fell()) {
        // check if event on falling edge is registered
        //if (((_trigger & TriggerType::Falling) == static_cast<TriggerTypeIntEqual>(TriggerType::Falling))) {
        onEvent(TriggerType::Falling);
        //}

        // remember the timestamp to determine long press or short press later
        _buttonDownTimestamp = millis();
        _isButtonDown = true;
    } else if (_button.rose()) {
        // check if the raising edge should reported
        //if (((_trigger & TriggerType::Rising) == static_cast<TriggerTypeIntEqual>(TriggerType::Rising))) {
        onEvent(TriggerType::Rising);
        //}

        // long press or short press
        // and report the one if registered
        uint32_t currentMillis = millis();
        uint32_t downTime = (currentMillis - _buttonDownTimestamp);

        if (downTime > _shortPressDuration && downTime < _longPressDuration) {
            onEvent(TriggerType::Press);
        }
        _isButtonDown = false;
    } else if (_isButtonDown && ((millis() - _buttonDownTimestamp) > _longPressDuration)) {
        // long press
        onEvent(TriggerType::LongPress);
        _isButtonDown = false;
    }
}

void ArduinoButton::setButtonCallback(ArduinoButton::ButtonCallback buttonCb) {
    _buttonCb = buttonCb;
}

uint8_t ArduinoButton::getPin() const {
    return _pin;
}

void ArduinoButton::configure(uint8_t pin, ArduinoButton::PinMode mode, TriggerType trigger) {
    _trigger = static_cast<TriggerTypeIntEqual>(trigger);
    _pin = pin;

    // get requested pin pull mode
    uint8_t inputType = INPUT;
    if (mode == PinMode::PullDown) {
#if defined(ESP32)
        inputType = INPUT_PULLDOWN;
#endif
        _button.setPressedState(HIGH);
    } else if (mode == PinMode::PullUp) {
        inputType = INPUT_PULLUP;
        _button.setPressedState(LOW);
    }

    // configure pin and debouncing
    _button.attach(static_cast<int>(pin), static_cast<int>(inputType));
    _button.interval(sDebounceIntervall);
}

void ArduinoButton::setShortPressDuration(uint32_t value) {
    _shortPressDuration = value;
}

void ArduinoButton::setLongPressDuration(uint32_t value) {
    _longPressDuration = value;
}

ArduinoButton::TriggerTypeIntEqual operator&(TriggerType first, TriggerType second) {
    return static_cast<ArduinoButton::TriggerTypeIntEqual>(first) &
           static_cast<ArduinoButton::TriggerTypeIntEqual>(second);
}

ArduinoButton::TriggerTypeIntEqual
operator&(ArduinoButton::TriggerTypeIntEqual first, TriggerType second) {
    return first & static_cast<ArduinoButton::TriggerTypeIntEqual>(second);
}

ArduinoButton::TriggerTypeIntEqual operator|(TriggerType first, TriggerType second) {
    return static_cast<ArduinoButton::TriggerTypeIntEqual>(first) |
           static_cast<ArduinoButton::TriggerTypeIntEqual>(second);
}

void ArduinoButton::onEvent(TriggerType event) {
    if (_buttonCb != nullptr) {
        _buttonCb(this, event);
    }

    List<ButtonReceiver>::Node *current = _receivers.firstNode();
    while (current != nullptr) {
        current->item->onButtonEvent(this, event);
        current = current->next;
    }
}

void ArduinoButton::addReceiver(ButtonReceiver *receiver) {
    _receivers.add(receiver);
}

void ArduinoButton::removeReceiver(ButtonReceiver *receiver) {
    _receivers.remove(receiver);
}
