const int ledPins[] = {18, 17, 16};
const int numLeds = sizeof(ledPins) / sizeof(ledPins[0]);

void setup() {
    randomSeed(analogRead(0)); // Seed random number generator
    for (int i = 0; i < numLeds; i++) {
        pinMode(ledPins[i], OUTPUT);
        digitalWrite(ledPins[i], LOW);
    }
}

void loop() {
    // Turn all LEDs off
    for (int i = 0; i < numLeds; i++) {
        digitalWrite(ledPins[i], LOW);
    }
    
    // Pick a random number of LEDs to turn on (between 1 and 8)
    int numOn = random(1, 9);
    
    // Turn on random LEDs
    for (int i = 0; i < numOn; i++) {
        int ledIndex = random(numLeds);
        digitalWrite(ledPins[ledIndex], HIGH);
    }
    
    delay(5000); // Wait 5 seconds before changing LEDs
}
