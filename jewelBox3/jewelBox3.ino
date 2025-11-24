#include <Arduino.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// Audio objects
AudioPlaySdWav playWav1;
AudioOutputI2S audioOutput;
AudioConnection patchCord1(playWav1, 0, audioOutput, 0);
AudioConnection patchCord2(playWav1, 1, audioOutput, 1);
AudioControlSGTL5000 sgtl5000_1;

// SD card pins for Teensy Audio Shield
#define SDCARD_CS_PIN 10
#define SDCARD_MOSI_PIN 11
#define SDCARD_SCK_PIN 13

//ldr init
#define LDRPIN 14
float ldrRead = 0;

//ONBUTTON
#define  ONBUTTON 15
bool onState = 1;

//LEDPIN
#define LEDPIN 16


// Storage for wav filenames
String wavFiles[50];
int wavCount = 0;

// ----------------------------------------------------------------
// SCAN SD FOR WAV FILES
// ----------------------------------------------------------------
void scanWavFiles() {
  File root = SD.open("/");
  wavCount = 0;

  pinMode(LDRPIN, INPUT);

  File entry = root.openNextFile();
  while (entry) {
    if (!entry.isDirectory()) {
      String name = entry.name();
      name.toUpperCase();
      if (name.endsWith(".WAV")) {
        wavFiles[wavCount] = entry.name();
        wavCount++;
        Serial.print("Found WAV: ");
        Serial.println(entry.name());
      }
    }
    entry.close();
    entry = root.openNextFile();
  }

  Serial.print("Total WAV files: ");
  Serial.println(wavCount);
}

// ----------------------------------------------------------------
// PLAY WAV FILE
// ----------------------------------------------------------------
void playRandomWav() {
  if (wavCount == 0) {
    Serial.println("No WAV files found!");
    delay(2000);
    return;
  }

  int index = random(0, wavCount);
  String filename = wavFiles[index];

  Serial.print("Playing: ");
  Serial.println(filename);

  // Stop anything currently playing
  playWav1.stop();
  delay(5);

  playWav1.play(filename.c_str());
  delay(50);  // allow WAV header to load

  while (playWav1.isPlaying()) {
    ldrRead = analogRead(LDRPIN);
    Serial.println(ldrRead);
    if (ldrRead < 600){
  playWav1.stop();
  return;
    }
    delay(10);
  }

  playWav1.stop();   // ensure buffers close
  Serial.println("Done.");
}

// ----------------------------------------------------------------
// SETUP
// ----------------------------------------------------------------
void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));

  AudioMemory(60);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.8);

  pinMode(ONBUTTON, INPUT_PULLUP);
  pinMode(LEDPIN, OUTPUT);

  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);

  if (!SD.begin(SDCARD_CS_PIN)) {
    Serial.println("SD init failed!");
    while (1);
  }

  scanWavFiles();
}

// ----------------------------------------------------------------
// LOOP — play random WAV forever
// ----------------------------------------------------------------
void loop() {
  onState = digitalRead(ONBUTTON);  // <<< you forgot this

  if (onState == LOW) {
    // button is pressed
    digitalWrite(LEDPIN, LOW);
    Serial.println("its off");
    playWav1.stop();
    return;
  }

  // button not pressed = ON
  digitalWrite(LEDPIN, HIGH);

  ldrRead = analogRead(LDRPIN);
  if (ldrRead < 600) {
    playWav1.stop();
  } else {
    playRandomWav();
  }

  Serial.println(ldrRead);
  delay(500);
}

