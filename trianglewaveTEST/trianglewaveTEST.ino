#include <Wire.h>
#include <Adafruit_MCP4725.h>

Adafruit_MCP4725 dac;

void setup(void) {
  Serial.begin(9600);
  Serial.println("Hello!");

  Wire.begin(19, 18);  // SDA = D23, SCL = D22
  dac.begin(0x62);  // Default I2C address for MCP4725
  
  Serial.println("Generating a triangle wave");
}

void loop(void) {
    uint32_t counter;
    // Run through the full 12-bit scale for a triangle wave
    for (counter = 0; counter < 4095; counter++) {
      Serial.println(counter);  // Debugging line to check progress
      dac.setVoltage(counter, true);  // Update DAC immediately
    }
    for (counter = 4095; counter > 0; counter--) {
      Serial.println(counter);  // Debugging line to check progress
      dac.setVoltage(counter, true);  // Update DAC immediately
    }
}
