#ifndef motorclass_h
#define motorclass_h

#inculde "Arduino.h"

class motorclass {
  public:
    motorclass(int pinA, int pinB);
  void motorspeed(int Ms);
  private:
    int _pinA;
    int _pinB;
};


#endif
