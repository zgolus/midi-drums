#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();

const int CHANNELS = 4;
const int THRESHOLD = 30;
const int DURATION = 200;

const int pins[CHANNELS] = {A0, A1, A2, A3};
const int channels[CHANNELS] = {1, 2, 3, 4};
int durations[CHANNELS] = {0, 0, 0, 0};
unsigned long playing[CHANNELS] = {0, 0, 0, 0};

boolean debug = false;

void setup()
{
  MIDI.begin();
  Serial.begin(115200);
}

void loop()
{
  int piezoVal = 0;
  for (int i = 0; i < 3; i++) {
    if (playing[i] == 0) {
      piezoVal = analogRead(pins[i]);
      if (piezoVal > THRESHOLD) {
        noteOn(map(piezoVal, 0, 1023, 30, 127), i); 
      }
    }
    if (playing[i] != 0 && (millis() - playing[i] >= DURATION)) {
      noteOff(i);
    }
  }
}

void noteOn(int velocity, int drum) {
  MIDI.sendNoteOn(72, velocity, channels[drum]);
  if (debug) {
    Serial.print("noteOn at ");
    Serial.print(channels[drum]);
    Serial.print(" (");
    Serial.print(velocity);
    Serial.println(")");
  }
  playing[drum] = millis();
}


void noteOff(int drum) {
  MIDI.sendNoteOff(72, 0, channels[drum]);
  if (debug) {
    Serial.print("noteOff at ");
    Serial.println(channels[drum]);
  }
  playing[drum] = 0;
}

int getMaxVal(int lastVal, int pin) {
  int currentVal = analogRead(pin);
  while (currentVal > lastVal) {
    lastVal = currentVal;
    currentVal = analogRead(pin);
  }
  return lastVal;
}
