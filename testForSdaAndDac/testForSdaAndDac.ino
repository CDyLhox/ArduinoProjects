#include <Wire.h>

void setup() {
  Wire.begin(19,18);
  Serial.begin(9600);
  Serial.println("Scanning for I2C devices...");
  for (byte addr = 1; addr < 127; addr++) {
    Wire.beginTransmission(addr);
    Serial.print("not it");
    if (Wire.endTransmission() == 0) {
      Serial.print("Found I2C device at address 0x");
      Serial.println(addr, HEX);
    }
  }
}

void loop() {}
