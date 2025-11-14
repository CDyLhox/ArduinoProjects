#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

AudioInputI2S i2s1;      //xy=119,52
AudioAnalyzePeak peak1;  //xy=379,43
AudioConnection patchCord1(i2s1, 0, peak1, 0);

float peakVal;
int counter;
int prevAmp;
bool blo = false;
int bloprev = 0;
int blocount = 0;
float peakAvg; 
bool clap = false;
elapsedMillis timer;



void setup() {
  // put your setup code here, to run once:
  AudioMemory(4);
  Serial.begin(9600);
  Serial.print("ver 12");
}

void loop() {
  // put your main code here, to run repeatedly:

  if (peak1.available()) {
    peakVal = peak1.read();
  }

  counter = 0;
  while (peakVal > 0.1) {
    counter++;

    // if (counter < 50) {
    //   clap = true;
    // } else {
    //   clap = false;
    // }

    // if (counter >= 100) {
    //   blo = true;
    //   clap = false;
    // }
  if (peakVal <= 0.1) {
    // counter = 0;
    blo = false;
    clap = false;
    break;
  }
    
  } 
  if (counter < 30) {
    clap = true;
  }
  else if (counter >30){
    blo = true;
  }
  if (blo == 1 && blo != bloprev) {
    // Serial.println("jippie!");
    blocount++;
  }
  // Serial.println(prevAmp - peakVal);
  // if ((prevAmp - peakAvg) <= -0.3 && timer > 300) {

    if (clap == true && blo == false) {
      digitalWrite(13, HIGH);

      // Serial.println("clap"  + clap);
      // Serial.println("nu klap ik");
    }
    timer = 0;
  // }
  // Serial.print("'peakVal'");
  // Serial.println(peakVal);




  if (blocount >= 3) {
    digitalWrite(13, LOW);
    blocount = 0;
  }
  delay(1);
  bloprev = blo;
  if (timer > 5) {
  prevAmp = peakVal;
  timer = 0;
  peakAvg = peakAvg * 0.5 + peakVal * 0.5;
  Serial.println (peakAvg);
  }

}