#include <Wire.h>
#include <ESP8266Audio.h>
#include "audiofile.h"  // Include your audio data here, stored as a byte array in PROGMEM
#include <driver/i2s_std.h>  // Correct I2S header for ESP32
#include "driver/i2s.h"


// I2S Pin Definitions
#define I2S_BCK_PIN 22   // BCK -> GPIO 22
#define I2S_LRCK_PIN 15  // LRCK -> GPIO 15
#define I2S_DIN_PIN 23   // DIN -> GPIO 23

AudioFileSourcePROGMEM *file;        // Audio file source
AudioGeneratorWAV *wav;              // WAV decoder

void setupI2S() {
  // Configure I2S settings
  i2s_std_config_t i2s_config = {
      .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),  // Correct I2S mode
      .sample_rate = 44100,  // Match WAV file sample rate
      .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT, // 16-bit data
      .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT, // Stereo
      .communication_format = I2S_COMM_FORMAT_I2S,  // I2S communication format
      .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1 // Interrupt level
  };

  i2s_std_pin_config_t pin_config = {
      .bck_pin = I2S_BCK_PIN,      // Bit clock pin
      .ws_pin = I2S_LRCK_PIN,      // Word select (LRCK) pin
      .data_out_pin = I2S_DIN_PIN, // Data output pin
      .data_in_pin = I2S_PIN_NO_CHANGE // No input pin for this example
  };

  // Install the driver
  ESP_ERROR_CHECK(i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL));
  ESP_ERROR_CHECK(i2s_set_pin(I2S_NUM_0, &pin_config));
}

void setup() {
  Serial.begin(115200);
  delay(2000); // Allow some time for serial monitor to open

  Serial.println("Initializing I2S...");
  setupI2S();

  Serial.println("Initializing audio components...");
  file = new AudioFileSourcePROGMEM(audiofile, sizeof(audiofile));
  if (file == nullptr) {
    Serial.println("Failed to create file source.");
    return;
  }

  wav = new AudioGeneratorWAV();
  if (wav == nullptr) {
    Serial.println("Failed to create WAV generator.");
    return;
  }

  if (!wav->begin(file, nullptr)) {  // No output object; we’ll write directly to I2S
    Serial.println("Failed to start WAV playback.");
    return;
  }
  Serial.println("Setup complete.");
}

void loop() {
  // Play the WAV audio
  if (wav->isRunning()) {
    if (wav->loop()) {
      // Use a method to read the samples, if available
      int16_t left_sample, right_sample;
      wav->readU8(left_sample); // Assuming `readU8` is the right method to read a sample

      int16_t stereo_samples[2] = {left_sample, right_sample};

      // Write samples to I2S
      size_t bytes_written;
      i2s_write(I2S_NUM_0, stereo_samples, sizeof(stereo_samples), &bytes_written, portMAX_DELAY);
    } else {
      wav->stop();
    }
  } else {
    Serial.println("WAV playback finished.");
    delay(1000);  // Optional delay before restarting or stopping completely
  }
}
