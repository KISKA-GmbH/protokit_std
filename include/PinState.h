//
// Created by f.wimmer on 7/11/2024.
//

#ifndef PROTOKIT_STD_PINSTATE_H
#define PROTOKIT_STD_PINSTATE_H

/* small because otherwise C++ complained. */
enum class ChangeState {
    rising,
    falling,
    none
};

/**
 * A class to keep track of the state of a pin. Including if it rises or falls.
 */
class PinState {
public:
    enum class PinMode {
        No,
        PullUp,
        PullDown,
    };

    // Constructor
    explicit PinState(int pin, PinMode pinMode = PinMode::PullUp);

    // Destructor
    ~PinState() = default;

    void loop();

    ChangeState getChangeState() const;

    void resetChangeState();

    int getState() const;

private:
    int state; // The state of the pin
    int pin;
    int stableCounter = 0;

    ChangeState lastChangeState;
};


#endif //PROTOKIT_STD_PINSTATE_H
