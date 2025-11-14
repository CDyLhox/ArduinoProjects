// give it a name:
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>


// GUItool: begin automatically generated code
AudioInputI2S i2s1;      //xy=119,52
AudioAnalyzePeak peak1;  //xy=379,43
AudioConnection patchCord1(i2s1, 0, peak1, 0);
// GUItool: end automatically generated code


int led = 23;
float avgAmp = 0;
float prevAmp = 0;
float peakValue = 0.0;
elapsedMillis fps;
int counter = 0;
int bloCount = 0;
bool isBlow = 0;

void setup() {
  Serial.begin(9600);
  AudioMemory(4);
  pinMode(led, OUTPUT);
}

void loop() {
  // Serial.println("fps " + fps);
  //Serial.println(avgAmp);

  if (peak1.available()) {
    peakValue = peak1.read();
  }

  // Serial.println(peakValue);
  while (peakValue > 0.04) {
    if (counter < 101) {
      counter++;
    }


    // fps = 0;
    if (peakValue > 0.04 && counter > 100) {
      isBlow = 1;
      delay(1);
    }
    if (isBlow == 1) {
      bloCount++;
      isBlow = 0;
      // ellapsedmilis ipv delay
      if (peakValue > 0.02) {
        delay(10);
      }
      else{break;}
    }
  }
  delay(1);
  avgAmp = avgAmp * 0.9;
  prevAmp = peakValue;
  delay(1);
  fps = 0;


  Serial.println(bloCount);
  if (bloCount > 3) {
    analogWrite(led, LOW);
    bloCount = 0;
  }
  if (peakValue <= 0.04 && isBlow == 1) {
    isBlow = 0;
  }
}