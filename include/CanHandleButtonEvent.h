#pragma once

#include <Arduino.h>
#include <ButtonEventHandler.h>
#include <ButtonEventType.h>

class CanHandleButtonEvent {
    public:
        virtual void handleButtonEvent(char key, ButtonEventType type);
};