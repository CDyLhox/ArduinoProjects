#include <Servo.h>
#include <elapsedMillis.h>

Servo myservo;   // create servo object to control a servo
Servo myservo2;  // create servo object to control a servo

int trigPin = 9;  // TRIG pin
int echoPin = 8;  // ECHO pin

int ledPin1 = 2;


int pos2, pos1;
int buzzpin = 2;

long duration;
int distance;

float duration_us, distance_cm;

elapsedMillis milisecondTimer;

// Motor A connections
int enA = 10;
int in1 = 3;
int in2 = 4;
// Motor B connections
int enB = 11;
int in3 = 12;
int in4 = 13;

void setup() {
  // begin serial port˝post
  Serial.begin(9600);

  // configure the trigger pin to output mode
  pinMode(trigPin, OUTPUT);
  // configure the echo pin to input mode
  pinMode(echoPin, INPUT);

  pinMode(buzzpin, OUTPUT);

  pinMode(ledPin1, OUTPUT);



  myservo.attach(3);
  myservo2.attach(6);

  //MOTOR INITIALISATION
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

float trackDistance() {
  // Serial.print(milisecondTimer);
  if (milisecondTimer % 15 == 0) {
    Serial.println("trackDistance::trackDistance");
    // generate 10-microsecond pulse to TRIG pin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(10);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // measure duration of pulse from ECHO pin
    duration_us = pulseIn(echoPin, HIGH);

    // calculate the distance
    distance_cm = 0.017 * duration_us;

    Serial.print("distance_cm");
    Serial.println();
  }
  return distance_cm;
}

void driveForward() {
  Serial.print("driveForward()");
  analogWrite(enA, 255);
  analogWrite(enB, 255);

  digitalWrite(in1, LOW);
  digitalWrite(in4, LOW);

  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
}
void driveBackward() {
  Serial.print("driveBackward()");
  analogWrite(enA, 255);
  analogWrite(enB, 150);

  digitalWrite(in1, HIGH);
  digitalWrite(in4, HIGH);

  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
}
void driveTurn() {
  Serial.print("driveTurn()");
  analogWrite(enA, 255);
  analogWrite(enB, 150);

  digitalWrite(in2, HIGH);
  digitalWrite(in4, HIGH);

  digitalWrite(in1, LOW);
  digitalWrite(in3, LOW);
}

void loop() {
  if (trackDistance() < 100 && trackDistance() > 0) {
    trackDistance();
    Serial.print("am angry   ");
    Serial.print("distance < 15 cm. distance is: ");
    Serial.println(distance_cm);


    driveBackward();


    pos1 = myservo.read() - 190;
    pos2 = myservo2.read() + 190;
    myservo.write(pos1);  // tell servo to go to position in variable 'pos'
    myservo2.write(pos2);

    //ACTIVATE MOTORs IN FORWARD DIRECTION


    digitalWrite(ledPin1, HIGH);





  } else if (trackDistance() > 15) {
    driveForward();
    trackDistance();
    pos1 = myservo.read();
    pos2 = myservo2.read();
    Serial.print("distance > 15 cm. distance is: ");
    Serial.println(distance_cm);

    if (milisecondTimer % 15 == 0) {
      myservo.write(90);  // tell servo to go to position in variable 'pos'

      myservo2.write(90);
    }




    // waits 15ms for the servo to reach the position
    digitalWrite(ledPin1, LOW);
    digitalWrite(buzzpin, LOW);
  } else {
    driveTurn();
  }
}
