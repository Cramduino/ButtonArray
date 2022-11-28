#include <Arduino.h>
#include <ButtonArray.h>

ButtonArray buttons = ButtonArray(
    (char[12]){ '1', '2', '3', '4', '5', '6', '7', '8', '9', 'H', 'A', 'B' }, 12,
    (uint8_t[4]){ 5, 4, 3, 2 }, 4,
    (uint8_t[3]){ 6, 8, 7 }, 3 );

class HandlerClass : CanHandleButtonEvent {
    public:
        void handleButtonEvent(char key, ButtonEventType type) {
            Serial.print("HandlerClass: ");
            Serial.print("KEY: "); Serial.print(key);

            switch (type) {
                case ButtonEventType::PRESS:
                    Serial.print(" EVENT: PRESS");
                    break;
                case ButtonEventType::PRESS_AND_HOLD:
                    Serial.print(" EVENT: PRESS_AND_HOLD");
                    break;
                case ButtonEventType::RELEASE:
                    Serial.print(" EVENT: RELEASE");
                    break;
                case ButtonEventType::PRESS_AND_RELEASE:
                    Serial.print(" EVENT: PRESS_AND_RELEASE");
                    break;
                case ButtonEventType::HOLD_AND_RELEASE:
                    Serial.print(" EVENT: HOLD_AND_RELEASE");
                    break;
                default:
                    Serial.print(" EVENT: UNKNOWN");
                    break;
            }
            
            Serial.println();
        }
};
HandlerClass handlerClass;

void handleButton(char key, ButtonEventType type) {
    Serial.print("HandlerFunction: ");
    Serial.print("KEY: "); Serial.print(key);

    switch (type) {
        case ButtonEventType::PRESS:
            Serial.print(" EVENT: PRESS");
            break;
        case ButtonEventType::PRESS_AND_HOLD:
            Serial.print(" EVENT: PRESS_AND_HOLD");
            break;
        case ButtonEventType::RELEASE:
            Serial.print(" EVENT: RELEASE");
            break;
        case ButtonEventType::PRESS_AND_RELEASE:
            Serial.print(" EVENT: PRESS_AND_RELEASE");
            break;
        case ButtonEventType::HOLD_AND_RELEASE:
            Serial.print(" EVENT: HOLD_AND_RELEASE");
            break;
        default:
            Serial.print(" EVENT: UNKNOWN");
            break;
    }

    Serial.println();
}

void setup() {
    Serial.begin(115200);
    buttons.setHandlerFunction((ButtonEventHandler)handleButton);
    buttons.setHandlerClass((CanHandleButtonEvent*)&handlerClass);
    buttons.begin();
}

void loop() {
    buttons.loop();
}