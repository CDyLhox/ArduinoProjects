#include <Arduino.h>

#include "AudioFileSourcePROGMEM.h"
#include "AudioGeneratorWAV.h"

// VIOLA sample taken from https://ccrma.stanford.edu/~jos/pasp/Sound_Examples.html
#include "viola.h"

#define I2S_BCK_PIN 22   // BCK -> GPIO 22
#define I2S_LRCK_PIN 15  // LRCK -> GPIO 15
#define I2S_DIN_PIN 23   // DIN -> GPIO 23

AudioGeneratorWAV *wav;
AudioFileSourcePROGMEM *file;
AudioOutputI2S *out;  // Change this to AudioOutputI2S

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.printf("WAV start\n");

  audioLogger = &Serial;
  file = new AudioFileSourcePROGMEM(viola, sizeof(viola));
  out = new AudioOutputI2S();  // Initialize AudioOutputI2S instead of AudioOutputI2SNoDAC
  wav = new AudioGeneratorWAV();

  // Debugging print
  Serial.println("Initializing WAV generator...");
  wav->begin(file, out);

  if (wav->isRunning()) {
    Serial.println("WAV is running!");
  } else {
    Serial.println("WAV did not start!");
  }
}

void loop() {
  if (wav->isRunning()) {
    if (!wav->loop()) wav->stop();
  } else {
    Serial.printf("WAV done\n");
    delay(1000);
  }
}
