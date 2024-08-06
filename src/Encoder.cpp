//
// Created by f.wimmer on 7/11/2024.
//

#include "Encoder.h"

void Encoder::loop() {
    pin1.loop();
    pin2.loop();

    switch (encoderState) {
        case None:
            if (pin1.getChangeState() == ChangeState::falling) {
                setState(EncoderState::FirstFell);
            } else if (pin2.getChangeState() == ChangeState::falling) {
                setState(EncoderState::SecondFell);
            } else if (edgeType == SingleEdge && pin2.getChangeState() == ChangeState::rising) {
                setState(EncoderState::SecondRise);
            } else if (edgeType == SingleEdge && pin1.getChangeState() == ChangeState::rising) {
                setState(EncoderState::FirstRise);
            }
            break;

        case FirstFell:
            if (updateStateAfterOneChanged(ChangeState::falling, pin1.getState(), pin2.getChangeState())) {
                setLastDirection(RotationDirection::Left);
            }
            break;

        case SecondFell:
            if (updateStateAfterOneChanged(ChangeState::falling, pin2.getState(), pin1.getChangeState())) {
                setLastDirection(RotationDirection::Right);
            }
            break;

        case FirstRise:
            if (updateStateAfterOneChanged(ChangeState::rising, pin1.getState(), pin2.getChangeState())) {
                setLastDirection(RotationDirection::Left);
            }
            break;
        case SecondRise:
            if (updateStateAfterOneChanged(ChangeState::rising, pin2.getState(), pin1.getChangeState())) {
                setLastDirection(RotationDirection::Right);
            }
            break;

        default:
            break;
    }

    pin1.resetChangeState();
    pin2.resetChangeState();
}

RotationDirection Encoder::getDirection() const {
    return lastDirection;
}

void Encoder::resetDirection() {
    lastDirection = RotationDirection::None;
}

bool
Encoder::updateStateAfterOneChanged(ChangeState firstChange, int pinStateOfFirst, ChangeState changeStateOfSecond) {
    int notExpectedState = firstChange == ChangeState::rising ? 0 : 1;
    if (pinStateOfFirst == notExpectedState) {
        setState(EncoderState::None);
        return false;
    }

    if (changeStateOfSecond == firstChange) {
        setState(EncoderState::None);
        return true;
    } else if (pin1.getChangeState() != ChangeState::none || pin2.getChangeState() != ChangeState::none) {
        setState(EncoderState::None);
    } else if (pin1.getState() == pin2.getState()) {
        setState(EncoderState::None);
    }
    return false;
}

void Encoder::setLastDirection(RotationDirection direction) {
    if (direction == RotationDirection::Left) {
        leftEvent.set();
    } else {
        rightEvent.set();
    }

    lastDirection = direction;
}

void Encoder::setState(EncoderState state) {
    encoderState = state;
}

Encoder::Encoder(PinState &pin1, PinState &pin2, EdgeType edgeType, OneEventStoreWritable &left,
                 OneEventStoreWritable &right)
        : pin1(
        pin1), pin2(pin2), leftEvent(left), rightEvent(right), edgeType(edgeType) {

}
