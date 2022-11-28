#pragma once

#include <Arduino.h>
#include <Keypad.h>
#include <ButtonEventHandler.h>
#include <CanHandleButtonEvent.h>

class ButtonArray {

    private:
        char*    _buttons;
        uint8_t  _num_buttons;
        uint8_t* _x_pins;
        uint8_t  _x_pins_count;
        uint8_t* _y_pins;
        uint8_t  _y_pins_count;

        Keypad*  _keypad;

        char     _key;
        KeyState _state;

        CanHandleButtonEvent* _handler_class = nullptr;
        ButtonEventHandler _handler_func = nullptr;

        void _fireEvent(char key, ButtonEventType type);
        bool _held;

    public:
        ButtonArray(
            char* buttons, uint8_t num_buttons, 
            uint8_t* x_pins, uint8_t x_pins_count, 
            uint8_t* y_pins, uint8_t y_pins_count);
        
        void begin();
        void loop();

        void setHandlerClass(CanHandleButtonEvent* handler);
        void setHandlerFunction(ButtonEventHandler handler);

};