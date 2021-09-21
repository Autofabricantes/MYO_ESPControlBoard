#include "Arduino.h"
#include"MYO_Motor.h"

MYO_Motor::MYO_Motor(int pinEn,int pinA, int pinB, int pinPot, int pinSen)
{
  // Pin Configuration
  pinMode(pinEn, OUTPUT);
  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(pinPot, INPUT);
  digitalWrite(pinEn, LOW);
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, LOW);
  _pinEn = pinEn;
  _pinA = pinA;
  _pinB = pinB;
  _pinPot = pinPot;
  _pinSen = pinSen;
  _setSpeed = MOTORSPEED_DEFAULT;
  _currentPosition = map(analogRead(pinPot),0,1024,POSITION_MIN,POSITION_MAX);
  _tolerance = TOLERANCE_DEFAULT;
  _delay = DELAY_DEFAULT;
}

int MYO_Motor::getPosition(){
  _currentPosition = map(analogRead(_pinPot),0,1024,POSITION_MIN,POSITION_MAX);
  return _currentPosition;
}

int MYO_Motor::getMotorSpeed(){
  return _setSpeed;
}

int MYO_Motor::setMotorSpeed(int aimedMotorSpeed){
  if(aimedMotorSpeed < MOTORSPEED_MIN){_setSpeed = MOTORSPEED_MIN;}
  else if(aimedMotorSpeed > MOTORSPEED_MAX){_setSpeed = MOTORSPEED_MAX;}
  else{_setSpeed = aimedMotorSpeed;}
  return aimedMotorSpeed;
}

int MYO_Motor::getTolerance(){
  return _tolerance;
}

int MYO_Motor::setTolerance(int aimedTolerance){
  if(aimedTolerance < TOLERANCE_MIN){_tolerance = TOLERANCE_MIN;}
  else if(aimedTolerance > TOLERANCE_MAX){_tolerance = TOLERANCE_MAX;}
  else{_tolerance = aimedTolerance;}
  return aimedTolerance;
}

int MYO_Motor::getDelay(){
  return _delay;
}

int MYO_Motor::setDelay(int aimedDelay){
  if(aimedDelay < DELAY_MIN){_delay = DELAY_MIN;}
  else if(aimedDelay > DELAY_MAX){_delay = DELAY_MAX;}
  else{_delay = aimedDelay;}
  return aimedDelay;
}

void MYO_Motor::goToPosition(int aimedPosition){
  while(!inPosition(aimedPosition)){
    setDirection(aimedPosition);
    setEnable();
    delay(_delay);
  }
  stopHalt();
}

bool MYO_Motor::setEnable(){
  // Here the PWM COntrol
  digitalWrite(_pinEn, HIGH);
  return true;
}

bool MYO_Motor::setDirection(int aimedPosition){
  if(aimedPosition > _currentPosition){
    digitalWrite(_pinA, HIGH);
    digitalWrite(_pinB, LOW);
    return true;
  }else{
    digitalWrite(_pinA, LOW);
    digitalWrite(_pinB, HIGH);
    return false;
  }
}

bool MYO_Motor::inPosition(int aimedPosition){
   _currentPosition = map(analogRead(_pinPot),0,1024,POSITION_MIN,POSITION_MAX);
  if((_currentPosition <= (aimedPosition - _tolerance)) || (_currentPosition >= (aimedPosition + _tolerance))){
    return false;
  }else{
    return true;
  }
}

void MYO_Motor::stopHalt(){
  digitalWrite(_pinA, HIGH);
  digitalWrite(_pinB, HIGH);
  digitalWrite(_pinEn, HIGH);
}

void MYO_Motor::stopLiberate(){
  digitalWrite(_pinA, LOW);
  digitalWrite(_pinB, LOW);
  digitalWrite(_pinEn, LOW);
}
