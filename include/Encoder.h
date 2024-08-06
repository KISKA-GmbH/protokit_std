//
// Created by f.wimmer on 7/11/2024.
//

#ifndef PROTOKIT_STD_ENCODER_H
#define PROTOKIT_STD_ENCODER_H

#include "PinState.h"
#include "OneEventRegister.h"

typedef enum {
    Left,
    Right,
    None
} RotationDirection;

typedef enum{
    /* Both edges are used to detect a rotation */
    SingleEdge,
    /* Only one edge is used to detect a rotation */
    DoubleEdge
}EdgeType;

/**
 * The encoder class is used to detect the rotation of an encoder.
 */
class Encoder {
public:
    void loop();

    Encoder(PinState &pin1, PinState &pin2, EdgeType edgeType, OneEventStoreWritable &left, OneEventStoreWritable &right);

    RotationDirection getDirection() const;


    /**
     * @brief Resets the direction of the encoder to None
     */
    void resetDirection();

private:
    typedef enum {
        None,
        FirstFell,
        SecondFell,
        FirstRise,
        SecondRise
    } EncoderState;

    // Class members and methods go here

    EncoderState encoderState = EncoderState::None;
    PinState &pin1;
    PinState &pin2;

    RotationDirection lastDirection = RotationDirection::None;

    /**
     * @brief This function updates the internal state of the encoder after one of the pins changed.
     * @returns true if the state update resultet in a rotation, false otherwise.
     */
    bool updateStateAfterOneChanged(ChangeState firstChange, int pinStateOfFirst, ChangeState changeStateOfSecond);

    /**
     * @brief This function sets the last direction of the encoder
     */
    void setLastDirection(RotationDirection direction);

    /**
     * @brief This function changes the state of the encoder to the given state
     *          The function should be used instead of writing directly to the variable
     */
    void setState(EncoderState state);

    OneEventStoreWritable &leftEvent;
    OneEventStoreWritable &rightEvent;

    EdgeType edgeType;
};


#endif //PROTOKIT_STD_ENCODER_H
