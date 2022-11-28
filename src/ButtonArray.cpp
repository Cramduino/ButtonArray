#include <ButtonArray.h>

void ButtonArray::_fireEvent(char key, ButtonEventType type) {
    if (this->_handler_class) this->_handler_class->handleButtonEvent(key, type);
    if (this->_handler_func) this->_handler_func(key, type);
}

ButtonArray::ButtonArray(
    char* buttons, uint8_t num_buttons, 
    uint8_t* x_pins, uint8_t x_pins_count, 
    uint8_t* y_pins, uint8_t y_pins_count) {

    this->_buttons = buttons;
    this->_num_buttons = num_buttons;
    this->_x_pins = x_pins;
    this->_x_pins_count = x_pins_count;
    this->_y_pins = y_pins;
    this->_y_pins_count = y_pins_count;
    
}

void ButtonArray::begin() {
    this->_keypad = new Keypad(
        makeKeymap(this->_buttons), 
        this->_x_pins, 
        this->_y_pins, 
        this->_x_pins_count, 
        this->_y_pins_count);
    this->_keypad->setHoldTime(1000);
}

void ButtonArray::loop() {
    char key = this->_keypad->getKey();
    if (key) { this->_key = key; }

    KeyState state = this->_keypad->getState();
    if (state != this->_state) {
        this->_state = state;
        switch (this->_state) {
            case KeyState::PRESSED:
                this->_fireEvent(this->_key, ButtonEventType::PRESS);
                this->_held = false;
                break;
            case KeyState::HOLD:
                this->_fireEvent(this->_key, ButtonEventType::PRESS_AND_HOLD);
                this->_held = true;
                break;
            case KeyState::RELEASED:
                this->_fireEvent(this->_key, ButtonEventType::RELEASE);
                if (this->_held) this->_fireEvent(this->_key, ButtonEventType::HOLD_AND_RELEASE);
                else this->_fireEvent(this->_key, ButtonEventType::PRESS_AND_RELEASE);
                break;
            default: break;
        }
    }
}

void ButtonArray::setHandlerClass(CanHandleButtonEvent* handler) {
    this->_handler_class = handler;
}

void ButtonArray::setHandlerFunction(ButtonEventHandler handler) {
    this->_handler_func = handler;
}