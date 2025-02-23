#include "Arduino.h"
#include "motorclass.h"

motorclass::motorclass(int pinA, int pinB){
  pinMode(pinA, OUTPUT);
  pinMode(pinA, OUTPUT);

  _pinA = pinA;
  _pinB = pinB;
}

void motorclass::motorspeed(int Ms){
  if (b1read == 0 && drumdivb == true) {
    digitalWrite(_pinA, HIGH);  // Set direction
    digitalWrite(_pinB, LOW);   // Set direction
    analogWrite(_pinA, Ms);     // Set speed (0 to 255)
  }
    // digitalWrite(_pinC, HIGH);  // Set direction
    // digitalWrite(_pinD, LOW);   // Set direction
    // analogWrite(_pinC, Ms);     // Set speed (0 to 255)

    // digitalWrite(motor3_in1, HIGH);  // Set direction
    // digitalWrite(motor3_in2, LOW);   // Set direction
    // analogWrite(motor3_in1, 95);     // Set speed (0 to 255)

    // digitalWrite(motor4_in3, HIGH);  // Set direction
    // digitalWrite(motor4_in4, LOW);   // Set direction
    // analogWrite(motor4_in3, 95);     // Set speed (0 to 255)

}