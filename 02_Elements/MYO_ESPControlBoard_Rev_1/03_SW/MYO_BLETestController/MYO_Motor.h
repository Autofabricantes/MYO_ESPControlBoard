
#ifndef MYO_MOTOR_H
#define MYO_MOTOR_H

#include "Arduino.h"

// Constant Definition
#define MOTORSPEED_DEFAULT  40
#define MOTORSPEED_MIN      0
#define MOTORSPEED_MAX      100

#define TOLERANCE_DEFAULT   10
#define TOLERANCE_MIN       0
#define TOLERANCE_MAX       100

#define DELAY_DEFAULT       1
#define DELAY_MIN           1
#define DELAY_MAX           100

#define POSITION_MIN        0
#define POSITION_MAX        100

class MYO_Motor
{
  public:
    MYO_Motor(int pinEn,int pinA, int pinB, int pinPot, int pinSen);
    int getPosition();
    int getMotorSpeed();
    int setMotorSpeed(int aimedMotorSpeed);
    void goToPosition(int aimedPosition);
    void stopHalt();
    void stopLiberate();
    bool inPosition(int aimedPosition);
    bool setDirection(int aimedPosition);
    bool setEnable();
    int setDelay(int aimedDelay);
    int getDelay();
    int setTolerance(int aimedTolerance);
    int getTolerance();
  private:
    int _pinEn;
    int _pinA;
    int _pinB;
    int _pinPot;
    int _pinSen;
    int _currentPosition;
    int _speed;
    int _tolerance;
    int _delay;
    int _pwmCh;
};

#endif
