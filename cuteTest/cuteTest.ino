#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

AudioPlaySdWav playWav1;
AudioOutputI2S audioOutput;
AudioConnection cord1(playWav1, 0, audioOutput, 0);
AudioConnection cord2(playWav1, 1, audioOutput, 1);
AudioControlSGTL5000 sgtl5000;

#define SDCARD_CS 10

void setup() {
  Serial.begin(9600);

  AudioMemory(12);
  sgtl5000.enable();
  sgtl5000.volume(0.8);

  SPI.setMOSI(11);
  SPI.setSCK(13);
  SD.begin(SDCARD_CS);

  Serial.println("Playing test file");
  playWav1.play("RUBRBNDG.WAV");
  delay(25);
}

void loop() {
  // do nothing
}

