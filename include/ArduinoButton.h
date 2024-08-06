//
// Created by f.wimmer on 7/11/2024.
//

#ifndef PROTOKIT_STD_ARDUINOBUTTON_H
#define PROTOKIT_STD_ARDUINOBUTTON_H

#include <Arduino.h>
#include "Bounce2.h"
#include "List.h"

class ArduinoButton;

enum class TriggerType {
    Rising = 1,
    Falling = 2,
    Press = 4,
    LongPress = 8
};

/**
 * Interface for the button receiver
 */
class ButtonReceiver {
public:
    virtual void onButtonEvent(ArduinoButton *button, TriggerType event) = 0;

    virtual ~ButtonReceiver() = default;
};

/**
 * Button class for handling button events.
 * Requires: Bounce 2 (platformio library: thomasfredericks/Bounce2 @ ^2.57)
 */
class ArduinoButton {
public:
    /**
     * Trigger typ of the button, can be combined
     */
    typedef uint8_t TriggerTypeIntEqual;

    enum class PinMode {
        No,
        PullUp,
        PullDown,
    };

    typedef void(*ButtonCallback)(ArduinoButton *, TriggerType);

    /**
     * @param pin   Number of the pin to which the button is connected
     * @param mode  pull-up, pull-down, nothing
     * @param trigger   Which events should be forwarded to the cb
     * @param shortPressDuration    Duration of the short press in milliseconds
     * @param longPressDuration     Duration of the long press in milliseconds
     */
    ArduinoButton(uint8_t pin, PinMode mode, TriggerType trigger,
                  uint32_t shortPressDuration = 20,
                  uint32_t longPressDuration = 250);

    /**
     *
     * @param shortPressDuration    Duration of the short press in milliseconds
     * @param longPressDuration     Duration of the long press in milliseconds
     */
    ArduinoButton(uint32_t shortPressDuration = 20,
                  uint32_t longPressDuration = 250);

    /**
     *
     * @param pin   Number of the pin to which the button is connected
     * @param mode  pull-up, pull-down, nothing
     * @param trigger   Which events should be forwarded to the cb
     */
    void configure(uint8_t pin, PinMode mode, TriggerType trigger);

    /**
     * Set the function which is called if a button event appears
     * @param buttonCb
     */
    void setButtonCallback(ButtonCallback buttonCb);

    /**
     * Loop of the button, it is important to execute this on a continuous base
     */
    void loop();

    /**
     *
     * @return pin of this button
     */
    uint8_t getPin() const;

    /**
     * Set the duration how long the button needs to be pressed for a short press
     * @param value
     */
    void setShortPressDuration(uint32_t value);

    /**
     * Set the duration how long the button needs to be pressed for a long press
     * @param value
     */
    void setLongPressDuration(uint32_t value);

    /**
     * Add a receiver to the button
     * @param receiver
     */
    void addReceiver(ButtonReceiver *receiver);

    void removeReceiver(ButtonReceiver *receiver);

private:

    static const int sDebounceIntervall = 5;
    TriggerTypeIntEqual _trigger;
    uint8_t _pin = -1;
    Bounce2::Button _button;

    uint32_t _buttonDownTimestamp = 0;
    bool _isButtonDown = false;
    uint32_t _shortPressDuration = 20;
    uint32_t _longPressDuration = 2000;

    ButtonCallback _buttonCb = nullptr;
    List<ButtonReceiver> _receivers;

    void onEvent(TriggerType event);
};

/**
 * Enable binary & operator for this enum
 * @param first
 * @param second
 * @return
 */
ArduinoButton::TriggerTypeIntEqual operator&(TriggerType first, TriggerType second);

/**
 * Enable binary & operator for this enum
 * @param first
 * @param second
 * @return
 */
ArduinoButton::TriggerTypeIntEqual
operator&(ArduinoButton::TriggerTypeIntEqual first, TriggerType second);

/**
 * Enable binary | operator for this enum
 * @param first
 * @param second
 * @return
 */
ArduinoButton::TriggerTypeIntEqual operator|(TriggerType first, TriggerType second);


#endif //PROTOKIT_STD_ARDUINOBUTTON_H
