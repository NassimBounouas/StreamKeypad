#include "Keyboard.h"

#define KEY_COUNT 12

#define PIN_F13 14
#define PIN_F14 2
#define PIN_F15 4
#define PIN_F16 6
#define PIN_F17 8
#define PIN_F18 16
#define PIN_F19 15
#define PIN_F20 3
#define PIN_F21 5
#define PIN_F22 7
#define PIN_F23 9
#define PIN_F24 10

#define RELEASED -1
#define PRESSED 1

int key_pins[KEY_COUNT] = { PIN_F13, PIN_F14, PIN_F15, PIN_F16, PIN_F17, PIN_F18, PIN_F19, PIN_F20, PIN_F21, PIN_F22, PIN_F23, PIN_F24 };
int key_code[KEY_COUNT] = { KEY_F13, KEY_F14, KEY_F15, KEY_F16, KEY_F17, KEY_F18, KEY_F19, KEY_F20, KEY_F21, KEY_F22, KEY_F23, KEY_F24 };

int previous_status[KEY_COUNT];
int current_status[KEY_COUNT];

void initstatus(int * arr, int value)
{
    for(int i = 0; i < KEY_COUNT; i++)
    {
        arr[i] = value;
    }
}

void update(int * res, int * previous, int * current) {
    for(int i = 0; i < KEY_COUNT; i++) {
        res[i] = previous[i] - current[i];
        previous[i] = current[i];
    }
}

void setup() {
    //configure pins as inputs and enable the internal pull-up resistor
    for(int pin_index = 0; pin_index < KEY_COUNT; pin_index++) {
        pinMode(key_pins[pin_index], INPUT_PULLUP);  
    }
    //previous and current statuses set to HIGH (pull-up resistor, buttons considered as released)
    initstatus(previous_status, HIGH);
    initstatus(current_status, HIGH);
    Keyboard.begin();
}

void loop() {
    int changes[KEY_COUNT];
    while(true) {
        for(int i = 0; i < KEY_COUNT; i++) {
            current_status[i] = digitalRead(key_pins[i]);
        }
        update(changes, previous_status, current_status);
        // Apply keyboard actions on changes
        for(int i = 0; i < KEY_COUNT; i++) {
            if(changes[i] == RELEASED) {
                Keyboard.release(key_code[i]);
            } else if (changes[i] == PRESSED) {
                Keyboard.press(key_code[i]);
            }
        }
    }
}