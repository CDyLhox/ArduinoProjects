/*  ============================            ZE CONTROLLER BOARD     (1)        ==================================      
  
                          ░▒▓███████▓▒░ ░▒▓██████▓▒░░▒▓█▓▒░░▒▓█▓▒░    ▒▓█▓▒░▒▓█▓▒░ 
                          ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░    ▒▓█▓▒░▒▓█▓▒░ 
                          ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░    ▒▓█▓▒░▒▓█▓▒░ 
                          ░▒▓███████▓▒░░▒▓████████▓▒░▒▓███████▓▒░░    ▒▓█▓▒░▒▓█▓▒░ 
                          ░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░    ▒▓█▓▒░▒▓█▓▒░ 
                          ░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░    ▒▓█▓▒░▒▓█▓▒░ 
                          ░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░    ▒▓█▓▒░▒▓█▓▒░ 
                          ░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░    ▒▓█▓▒░▒▓█▓▒░ 
                          ░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░    ▒▓█▓▒░▒▓█▓▒░ 



                                                                                                          */
#include "DFRobot_RGBLCD1602.h"
#include <WiFi.h>     // board WiFi
#include <esp_now.h>  // ESP-NOW
// #include <elapsedmillis>

// Variables to store BME280 readings to be sent
float temperature;
float humidity;
float pressure;

// Variables to store incoming readings
float incomingTemp;
float incomingHum;
float incomingPres;
int incomingpotM;

// Variables for sending/receiving messages
String aMessage;
String incomingMessage;
int messagenumber = 0;



// Structure example to send data
// Must match the receiver structure
typedef struct struct_message {
  float temp;
  float hum;
  float pres;
  char aMessage[32];  // Use fixed-size char array for compatibility
  int potM;
} struct_message;

// Create a struct_message to hold sensor readings
struct_message pakCom;

// Create a struct_message to hold incoming sensor readings
struct_message incomingReadings;

uint8_t broadcastAddress[] = { 0xD0, 0xEF, 0x76, 0x48, 0x01, 0x44 };  // Target ESP MAC Address

DFRobot_RGBLCD1602 lcd(/*RGBAddr*/ 0x2D, /*lcdCols*/ 16, /*lcdRows*/ 2);  // 16 characters and 2 lines

// Callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

// Callback when data is received
void OnDataRecv(const esp_now_recv_info *recv_info, const uint8_t *incomingData, int len) {
  // Extract MAC address from recv_info if needed
  const uint8_t *mac = recv_info->src_addr;

  // Copy incoming data into the structure
  memcpy(&incomingReadings, incomingData, sizeof(incomingReadings));

  // Parse incoming data
  incomingTemp = incomingReadings.temp;
  incomingHum = incomingReadings.hum;
  incomingPres = incomingReadings.pres;
  incomingMessage = String(incomingReadings.aMessage);
  incomingpotM = incomingReadings.potM;

  // Debug output
  // Serial.print("Bytes received: ");
  // Serial.println(len);
  // Serial.print("From MAC: ");
  for (int i = 0; i < 6; i++) {
    Serial.printf("%02X", mac[i]);
    // if (i < 5) Serial.print(":");
  }
  // Serial.println();
  // Serial.println("Incoming Message: " + incomingMessage);
}


void setup() {
  Serial.begin(115200);

  // Initialize WiFi in station mode
  WiFi.mode(WIFI_STA);

  // Initialize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Register send callback
  esp_now_register_send_cb(OnDataSent);

  // Register peer
  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }

  // Register receive callback
  esp_now_register_recv_cb(OnDataRecv);

  // Initialize LCD
  lcd.init();
  lcd.print("PAK_II^");
}

void getReadings() {
  temperature = 25.0;  // Example values
  humidity = 50.0;
  pressure = 1013.25;

  aMessage = "frog " + String(incomingMessage);

}

void loop() {
  getReadings();

  // Populate struct for sending
  pakCom.temp = temperature;
  pakCom.hum = humidity;
  pakCom.pres = pressure;
  strncpy(pakCom.aMessage, aMessage.c_str(), sizeof(pakCom.aMessage) - 1);
  pakCom.aMessage[sizeof(pakCom.aMessage) - 1] = '\0';  // Null-terminate


  // Send data
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)&pakCom, sizeof(pakCom));
  if (result == ESP_OK) {
    // Serial.println("Sent with success");
  } else {
    Serial.println("Error sending the data");
  }

  // Change LCD RGB color and display the message
  static int colorStep = 0;
  int r = 150 + (colorStep % 105);
  int g = (colorStep % 150);
  int b = 255 - (colorStep % 105);
  lcd.setRGB(r, g, b);
  lcd.clear();
  lcd.print("PAK_II^  ");

  lcd.setCursor(0, 0);
  lcd.print(aMessage);

  lcd.setCursor(0,1);
  lcd.print(incomingpotM);

  if (aMessage.toInt() %10 == 5){
    Serial.print("haha im high");
    digitalWrite(5, HIGH);
  }

  colorStep++;
  delay(100);
}
