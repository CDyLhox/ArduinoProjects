int Button = 4;
int bPrev;
int bAvg;
int light = 0;
elapsedMillis buttonWait;

void setup() {
  // put your setup code here, to run once:
  pinMode(1, OUTPUT);
  pinMode(Button, INPUT_PULLUP);
}

void loop() {

  // int bVal = digitalRead(Button);
  // put your main code here, to run repeatedly:

  Serial.println(digitalRead(Button));
  delay(1);



  // switch(if (digitalRead(button) == 1){
  //   case 1:
  //   digitalWrite(1, HIGH);
  //   break;
  //   case 2:
  //   digitalWrite(1,LOW);
  //   break;
  // }

  if (buttonWait > 30 && bPrev == 1) {

    if (digitalRead(Button) == 0 && light == 1) {
      digitalWrite(1, LOW);
      light = 0;
      buttonWait = 0;

    } else if (digitalRead(Button) == 0 && light == 0) {
      digitalWrite(1, HIGH);
      light = 1;
      buttonWait = 0;
    }
  }
    bPrev = digitalRead(Button);
}
