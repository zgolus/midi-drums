#include <MIDI.h>
#include <Keypad.h>

// Created and binds the MIDI interface to the default hardware Serial port
MIDI_CREATE_DEFAULT_INSTANCE();

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3','4'},
  {'5','6','7','8'},
  {'9','a','b','c'},
  {'d','e','f','g'}
};
byte rowPins[ROWS] = {5, 4, 2, 3}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {6, 7, 8, 9}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup()
{
    MIDI.begin(MIDI_CHANNEL_OMNI);  // Listen to all incoming messages
    Serial.begin(115200);
    keypad.addEventListener(keypadEvent);
}

void loop()
{
    
}

void keypadEvent(KeypadEvent key){
    switch (keypad.getState()){
    case PRESSED:
        if (key == '9') {
            // kick
            MIDI.sendNoteOn(72, 60, 1);
        }
        if (key == 'a') {
            // snare
            MIDI.sendNoteOn(72, 60, 2);
        }
        if (key == 'b') {
            // closed hi-hat
            MIDI.sendNoteOn(72, 60, 3);
        }
        if (key == 'c') {
            // open hi-hat
            MIDI.sendNoteOn(72, 60, 4);
        }
        break;

    case RELEASED:
        if (key == '9') {
            MIDI.sendNoteOff(72, 0, 1);
        }
        if (key == 'a') {
            MIDI.sendNoteOn(72, 0, 2);
        }
        if (key == 'b') {
            MIDI.sendNoteOn(72, 0, 3);
        }
        if (key == 'c') {
            MIDI.sendNoteOn(72, 0, 4);
        }
        break;

    case HOLD:
        break;
    }
}
