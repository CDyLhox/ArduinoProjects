// Define pins for motor control
const int motor1_in1 = 0;
const int motor1_in2 = 1;
const int motor2_in3 = 2;
const int motor2_in4 = 3;

int pot1 = 21;
int pot1last;

const int b1 = 33;
const int b2 = 34;
const int b3 = 35;
const int b4 = 36;

elapsedMillis drumDiv;
bool drumdivb;
int dDiv = 15;

void setup() {
  // Initialize motor control pins as outputs
  pinMode(motor1_in1, OUTPUT);
  pinMode(motor1_in2, OUTPUT);
  pinMode(motor2_in3, OUTPUT);
  pinMode(motor2_in4, OUTPUT);

  pinMode(b1, INPUT_PULLUP);
  pinMode(b2, INPUT_PULLUP);
  pinMode(b3, INPUT_PULLUP);
  pinMode(b4, INPUT_PULLUP);
}

void loop() {

    int pot1read (analogRead(pot1));
    int b1read (digitalRead(b1));
    int b2read (digitalRead(b2));
    int b3read (digitalRead(b3));
    int b4read (digitalRead(b4));

  //   if (pot1read > pot1last+2 || pot1read < pot1last-2){
  // // usbMIDI.sendNoteOn(map(pot1read, 0, 1024, 0, 127), 127, 1);
  // delay(60);
  // // usbMIDI.sendNoteOff(map(pot1read, 0, 1024, 0, 127), 127, 1);

  // pot1last = pot1read;
  //   }
    // Serial.println(map(pot1read, 0, 1024, 0, 127));
      Serial.print("b1 ");
      Serial.println(b1read);

      Serial.print("b2 ");
      Serial.println(b2read);

      Serial.print("b3 ");
      Serial.println(b3read);

      Serial.print("b4 ");
      Serial.println(b4read);

      // Serial.println(digitalRead(b2));
      // Serial.println(digitalRead(b3));
  // Example: set motor 1 to rotate forward at half speed

  dDiv = map(pot1read, 0, 1024, 0, 255);
  if(drumDiv > dDiv){
    drumdivb = true;
    drumDiv = 0;
  }
  else{
    drumdivb = false;
  }

      Serial.print("drumDiv ");
      Serial.println(drumDiv);
      Serial.print("dDiv ");
      Serial.println(dDiv);

  // 4 knopjes voor motor 1
  if(b1read == 0 && drumdivb == true){
    //motor1
  digitalWrite(motor1_in1, HIGH);   // Set direction
  digitalWrite(motor1_in2, LOW);    // Set direction
  analogWrite(motor1_in1, 125);  // Set speed (0 to 255)

// Serial.println("waarde 1 is waar(de)");

  // digitalWrite(motor1_in1, HIGH);   // Set direction
  // digitalWrite(motor1_in2, LOW);    // Set direction
  // analogWrite(motor1_in1, 0);  // Set speed (0 to 255)
  //motor2
  // digitalWrite(motor2_in3, HIGH);   // Set direction
  // digitalWrite(motor2_in4, LOW);    // Set direction
  // analogWrite(motor2_in3, 125);

  // analogWrite(motor1_in1, map(pot1read, 0, 1024, 0, 255));  // Set speed (0 to 255)
  }
  else if(b2read == 0 && drumdivb == true){
  digitalWrite(motor1_in1, HIGH);   // Set direction
  digitalWrite(motor1_in2, LOW);    // Set direction
  analogWrite(motor1_in1, 140);  // Set speed (0 to 255)
  // analogWrite(motor1_in1, map(pot1read, 0, 1024, 0, 255));  // Set speed (0 to 255)
  }
  else if(b3read == 0 && drumdivb == true){
  digitalWrite(motor1_in1, HIGH);   // Set direction
  digitalWrite(motor1_in2, LOW);    // Set direction
  analogWrite(motor1_in1, 160);  // Set speed (0 to 255)
  // analogWrite(motor1_in1, map(pot1read, 0, 1024, 0, 255));  // Set speed (0 to 255)
  }
  else if(b4read == 0 && drumdivb == true){
  digitalWrite(motor1_in1, HIGH);   // Set direction
  digitalWrite(motor1_in2, LOW);    // Set direction
  analogWrite(motor1_in1, 180);  // Set speed (0 to 255)
  // analogWrite(motor1_in1, map(pot1read, 0, 1024, 0, 255));  // Set speed (0 to 255)
  }

  //2 knopjes tegelijk?

  else if(b1read == 0 && b2read == 0){
  digitalWrite(motor1_in1, HIGH);   // Set direction
  digitalWrite(motor1_in2, LOW);    // Set direction
  analogWrite(motor1_in1, 125);  // Set speed (0 to 255)


  digitalWrite(motor2_in4, HIGH);   // Set direction
  digitalWrite(motor2_in3, LOW);    // Set direction
  analogWrite(motor2_in3, map(pot1read, 0, 1024, 0, 127));  // Set speed (0 to 255)
  }


  // niks 
  else{
    //motor1
  digitalWrite(motor1_in1, HIGH);   // Set direction
  digitalWrite(motor1_in2, LOW);    // Set direction
  analogWrite(motor1_in1, 0);  // Set speed (0 to 255)

    // motor2 
  digitalWrite(motor2_in3, HIGH);   // Set direction
  digitalWrite(motor2_in4, LOW);    // Set direction
  analogWrite(motor2_in3, 0);  // Set speed (0 to 255)
  }


  delay(1);  // Adjust delay as needed
}
