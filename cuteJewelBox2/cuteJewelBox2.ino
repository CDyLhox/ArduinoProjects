#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Arduino.h>

AudioPlaySdWav playWav1;
AudioOutputI2S audioOutput;
AudioConnection patchCord1(playWav1, 0, audioOutput, 0);
AudioConnection patchCord2(playWav1, 1, audioOutput, 1);
AudioControlSGTL5000 sgtl5000_1;

#define SDCARD_CS_PIN 10
#define SDCARD_MOSI_PIN 11//7
#define SDCARD_SCK_PIN 13//14



int ldr = A1;
int ldrRead;
int onbutton = 15;
int onButtonRead;
int lastButtonState = HIGH;
bool onBool = true; //should be false

elapsedMillis miliTimer;

void listWavFiles(File dir) {
  while (true) {
    File entry = dir.openNextFile();
    if (!entry) break;  // no more files

    if (entry.isDirectory()) {
      listWavFiles(entry);  // recurse into subdirectories
    } else {
      String filename = entry.name();
      if (filename.endsWith(".WAV") || filename.endsWith(".wav")) {
        Serial.println(filename);  // Print the filename
      }
    }
    entry.close();
  }
}

void setup() {
  randomSeed(analogRead(2));
  Serial.begin(9600);
  while (!Serial) ;  // Wait for PC USB connection

  Serial.println("cuteJeweryBox");

  pinMode(ldr, INPUT);
  pinMode(onbutton, INPUT_PULLUP);

  AudioMemory(16);
  sgtl5000_1.enable();
  sgtl5000_1.volume(1);

  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  if (!(SD.begin(SDCARD_CS_PIN))) {
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }

  // List files on the SD card
  File root = SD.open("/");
  listWavFiles(root);  // Print all WAV files on the SD card
}

void playFile(const char *filename) {
  Serial.print("Playing file: ");
  Serial.println(filename);

  playWav1.play(filename);
  delay(25);  // Brief delay to allow the WAV file to start playing

  while (playWav1.isPlaying()) {
    // Read sensor and button states
    ldrRead = analogRead(ldr);
    //onButtonRead = digitalRead(onbutton);

    // Check if the device should turn off
    /*if (!deviceStatus()) {  // If turned off
      Serial.println("Stopping playback due to device off state.");
      playWav1.stop();
      break;  // Exit the loop
    }

    // Light sensor logic to stop playback if LDR exceeds threshold
    if (ldrRead > 7300) {
      Serial.println("LDR threshold exceeded. Stopping playback.");
      playWav1.stop();
      break;  // Exit the loop
    }*/

    // Debugging information
    Serial.print("ldr: ");
    Serial.println(ldrRead);

    // Update last button state
    //lastButtonState = onButtonRead;

    delay(10);  // Small delay for loop stability
  }
  Serial.println("Playback loop exited.");
}


String getRandomWavFile() {
  File root = SD.open("/");
  String files[10];  // Array to hold up to 10 WAV files
  int fileCount = 0;

  // Populate the files array with WAV files
  while (true) {
    File entry = root.openNextFile();
    if (!entry) break;  // No more files

    if (entry.isDirectory()) {
      continue;  // Skip directories
    }

    String filename = entry.name();
    if (filename.endsWith(".WAV") || filename.endsWith(".wav")) {
      files[fileCount] = filename;  // Store the file name
      fileCount++;
    }
    entry.close();
  }

  // Debugging: print the file count and file names
  Serial.print("Found ");
  Serial.print(fileCount);
  Serial.println(" files.");
  for (int i = 0; i < fileCount; i++) {
    Serial.println(files[i]);
  }

  if (fileCount == 0) {
    return "";  // No WAV files found
  }

  // Select a random file from the array
  int randomIndex = random(0, fileCount);

  Serial.print("Random index: ");
  Serial.println(randomIndex);  // Print the selected random index

  // Serial.println(files[randomIndex]);

  return files[randomIndex];  // Return the random filename
}

bool deviceStatus() {
  if (lastButtonState == HIGH && onButtonRead == LOW) {  // Detect button press (state change)
    onBool = !onBool;                                    // Toggle the state
    if (onBool) {
      Serial.println("Turning ON!");
    } else {
      Serial.println("Turning OFF!");
    }
    delay(50);  // Debounce delay
  }
  return onBool;  // Return the current state
}


void loop() {
  onButtonRead = digitalRead(onbutton);
  // Serial.print("onbutton ");
  // Serial.println(onButtonRead);
  Serial.print("isturned on?  ");
  Serial.println(onBool);
  //deviceStatus();



  if (onBool == 1) {

    // If turned on, handle playback logic
    
    //ldrRead = analogRead(ldr);
    Serial.print("ldr: ");
    Serial.println(ldrRead);

    /*if (ldrRead > 700) {  // Light-dependent behavior
      delay(0.001);       // Mimic original code's intention
    } else {
      String randomSong = getRandomWavFile();
      if (randomSong != "" && miliTimer > 150) {
        playFile(randomSong.c_str());  // Play the randomly selected song
      }
    }*/

  }

  //lastButtonState = onButtonRead;

  delay(10);

  // Try manually testing some files
   playFile("RBRBNDGL.wav");
   delay(15000);  // Wait for the file to finish
  // playFile("HARVESTT.wav");
  // delay(15000);  // Wait for the file to finish
}
