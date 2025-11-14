#include <Arduino.h>
#include <driver/i2s.h>

#define I2S_BCK_PIN 15     // BCK pin on ESP32 connected to BCK pin on Teensy Audio Shield
#define I2S_LRCK_PIN 2     // LRCK pin on ESP32 connected to LRCK pin on Teensy Audio Shield
#define I2S_DIN_PIN 23     // DIN pin on ESP32 connected to SDIN pin on Teensy Audio Shield

void setup() {
  Serial.begin(115200);
  Serial.println("Starting ESP32 Audio output to Teensy Audio Shield...");

  // Configure I2S for ESP32 (Master, TX only)
  i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),  // I2S Master mode, TX only
    .sample_rate = 44100,                                 // Audio sample rate (44.1kHz)
    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,          // 16-bit per sample
    .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,         // Stereo format (2 channels)
    .communication_format = I2S_COMM_FORMAT_I2S,          // I2S communication format
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,             // Interrupt priority
    .dma_buf_count = 8,                                   // Number of DMA buffers
    .dma_buf_len = 64                                     // Length of each DMA buffer
  };

  i2s_pin_config_t pin_config = {
    .bck_io_num = I2S_BCK_PIN,      // Bit clock pin
    .ws_io_num = I2S_LRCK_PIN,      // Word select (LRCK) pin
    .data_out_num = I2S_DIN_PIN,    // Data out pin
    .data_in_num = I2S_PIN_NO_CHANGE // We don't need data in for TX
  };

  // Install the I2S driver with the configuration
  i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);
  i2s_set_pin(I2S_NUM_0, &pin_config);

  Serial.println("I2S setup complete.");
}

void loop() {
  // Generate a simple sine wave or audio data here and send to the I2S bus.
  uint16_t sample_data[64]; // Example data buffer for I2S (size matches DMA buffer)

  for (int i = 0; i < 64; i++) {
    // Fill the sample data buffer with sine wave values (or other audio data)
    sample_data[i] = (uint16_t)(sin(i * 2 * PI / 64) * 32767);  // Example sine wave values
  }

  // Write the sample data to the I2S interface
  size_t bytes_written;
  i2s_write(I2S_NUM_0, sample_data, sizeof(sample_data), &bytes_written, portMAX_DELAY);

  delay(10); // Small delay between samples
}
