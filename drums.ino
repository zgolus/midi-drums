#include <MIDI.h>
#include <Keypad.h>

MIDI_CREATE_DEFAULT_INSTANCE();

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1', '2', '3', '4'},
  {'5', '6', '7', '8'},
  {'9', 'a', 'b', 'c'},
  {'d', 'e', 'f', 'g'}
};
byte rowPins[ROWS] = {5, 4, 3, 2};
byte colPins[COLS] = {6, 7, 8, 9};

Keypad kpd = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup()
{
  MIDI.begin(MIDI_CHANNEL_OMNI);
  Serial.begin(115200);
}

void loop()
{
  if (kpd.getKeys()) {
    for (int i = 0; i < LIST_MAX; i++) {
      if ( kpd.key[i].stateChanged ) {
        switch (kpd.key[i].kstate) {
          case PRESSED:
            if (kpd.key[i].kchar == 'd') {
              // kick
              MIDI.sendNoteOn(72, 60, 1);
            }
            if (kpd.key[i].kchar == 'e') {
              // snare
              MIDI.sendNoteOn(72, 60, 2);
            }
            if (kpd.key[i].kchar == 'f') {
              // closed hi-hat
              MIDI.sendNoteOn(72, 60, 3);
            }
            if (kpd.key[i].kchar == 'g') {
              // open hi-hat
              MIDI.sendNoteOn(72, 60, 4);
            }
            if (kpd.key[i].kchar == '1') {
              // sample 1
              MIDI.sendNoteOn(72, 60, 5);
            }
            if (kpd.key[i].kchar == '2') {
              // sample 2
              MIDI.sendNoteOn(72, 60, 6);
            }
            if (kpd.key[i].kchar == '3') {
              // sample 3
              MIDI.sendNoteOn(72, 60, 7);
            }
            if (kpd.key[i].kchar == '4') {
              // sample 4
              MIDI.sendNoteOn(72, 60, 8);
            }
            break;
          case HOLD:
            break;
          case RELEASED:
            if (kpd.key[i].kchar == 'd') {
              MIDI.sendNoteOff(72, 0, 1);
            }
            if (kpd.key[i].kchar == 'e') {
              MIDI.sendNoteOn(72, 0, 2);
            }
            if (kpd.key[i].kchar == 'f') {
              MIDI.sendNoteOn(72, 0, 3);
            }
            if (kpd.key[i].kchar == 'g') {
              MIDI.sendNoteOn(72, 0, 4);
            }
            if (kpd.key[i].kchar == '1') {
              MIDI.sendNoteOn(72, 0, 5);
            }
            if (kpd.key[i].kchar == '2') {
              MIDI.sendNoteOn(72, 0, 6);
            }
            if (kpd.key[i].kchar == '3') {
              MIDI.sendNoteOn(72, 0, 7);
            }
            if (kpd.key[i].kchar == '4') {
              MIDI.sendNoteOn(72, 0, 8);
            }
            break;
          case IDLE:
            break;
        }
      }
    }
  }
}
