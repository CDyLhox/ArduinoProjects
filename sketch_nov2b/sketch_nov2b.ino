#include <Arduino.h>
#include "AudioFileSourcePROGMEM.h"
#include "AudioGeneratorMP3.h"
#include "AudioOutputPWM.h"

// Include your MP3 data stored in PROGMEM
#include "Stijn.h"

AudioGeneratorMP3 *mp3;
AudioFileSourcePROGMEM *file;
AudioOutputPWM *out;

void setup() {
  Serial.begin(115200);
  Serial.println("Starting MP3 playback...");

  // Initialize audio source, output, and MP3 generator
  file = new AudioFileSourcePROGMEM(Stijn, sizeof(Stijn));
  out = new AudioOutputPWM();
  mp3 = new AudioGeneratorMP3();
  mp3->begin(file, out);
}

void loop() {
  if (mp3->isRunning()) {
    if (!mp3->loop()) mp3->stop();
  } else {
    Serial.println("MP3 playback finished.");
    delay(1000);  // Optional delay before restarting or stopping completely
  }
}
