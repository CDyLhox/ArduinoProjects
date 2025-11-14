#include <Arduino.h>
#include <BluetoothA2DPSink.h>  // Bluetooth A2DP Sink library
#include <driver/i2s.h>         // Direct I2S driver for ESP32

BluetoothA2DPSink a2dp_sink;

// Define I2S pins for ESP32
#define I2S_BCK_PIN 22   // BCK -> GPIO 15
#define I2S_LRCK_PIN 15   // LRCK -> GPIO 2
#define I2S_DIN_PIN 23   // DIN -> GPIO 23

void setup() {
  Serial.begin(115200);
  Serial.println("Setting up Bluetooth Audio and I2S...");

  // Configure I2S settings with further reduced parameters
  i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),  // Master mode, transmit only
    .sample_rate = 44100,                                 // 44.1 kHz sample rate
    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,         // 16-bit per sample audio
    .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,         // Stereo format
    .communication_format = I2S_COMM_FORMAT_STAND_I2S,    // Standard I2S format
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,             // Interrupt level
    .dma_buf_count = 2,                                   // Minimized DMA buffer count
    .dma_buf_len = 16                                     // Minimized DMA buffer length
  };

  // I2S pin configuration (no change needed)
  i2s_pin_config_t pin_config = {
    .bck_io_num = I2S_BCK_PIN,
    .ws_io_num = I2S_LRCK_PIN,
    .data_out_num = I2S_DIN_PIN,
    .data_in_num = I2S_PIN_NO_CHANGE
  };

  // Install and start I2S driver
  i2s_driver_install(I2S_NUM_0, &i2s_config, 0, nullptr);
  i2s_set_pin(I2S_NUM_0, &pin_config);

  // Configure Bluetooth A2DP Sink
  a2dp_sink.set_stream_reader(i2s_write_sample, true);  // Set stream reader to write samples to I2S
  a2dp_sink.start("ESP32 Audio Stream");                // Start the Bluetooth stream
}

void loop() {
  // Bluetooth handles data automatically in the background
}

// Write samples received over Bluetooth to I2S
void i2s_write_sample(const uint8_t *data, uint32_t length) {
  size_t bytes_written;
  i2s_write(I2S_NUM_0, data, length, &bytes_written, portMAX_DELAY);
}
