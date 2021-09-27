#include "Arduino.h"
#include"MYO_Motor.h"

MYO_Motor::MYO_Motor(int pinEn,int pinA, int pinB, int pinPot, int pinSen)
{
  // Pin Configuration
  //pinMode(pinEn, OUTPUT);
  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(pinPot, INPUT);
  //digitalWrite(pinEn, LOW);
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, LOW);
  _pinEn = pinEn;
  _pinA = pinA;
  _pinB = pinB;
  _pinPot = pinPot;
  _pinSen = pinSen;
  _speed = MOTORSPEED_DEFAULT;
  _currentPosition = map(analogRead(pinPot),0,4095,POSITION_MIN,POSITION_MAX);
  _tolerance = TOLERANCE_DEFAULT;
  _delay = DELAY_DEFAULT;
  if(_pinEn == 4){
    _pwmCh = 0;
  }else if(_pinEn == 4){
    _pwmCh = 1;
  }
  ledcAttachPin(_pinEn, _pwmCh);
  ledcSetup(_pwmCh, 1000, 8);
  ledcWrite(_pwmCh, 0);
}

int MYO_Motor::getPosition(){
  _currentPosition = map(analogRead(_pinPot),0,4095,POSITION_MIN,POSITION_MAX);
  return _currentPosition;
}

int MYO_Motor::getMotorSpeed(){
  return _speed;
}

int MYO_Motor::setMotorSpeed(int aimedMotorSpeed){
  if(aimedMotorSpeed < MOTORSPEED_MIN){_speed = MOTORSPEED_MIN;}
  else if(aimedMotorSpeed > MOTORSPEED_MAX){_speed = MOTORSPEED_MAX;}
  else{_speed = aimedMotorSpeed;}
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
  delay(DELAY_MAX); // This stop is to avoid power noise that could turn off the LED
}

bool MYO_Motor::setEnable(){
  // Here the PWM COntrol
  //digitalWrite(_pinEn, HIGH);
  //ledcSetup(_pwmCh, map(_speed,MOTORSPEED_MIN,MOTORSPEED_MAX,0,254), 0);
  ledcWrite(_pwmCh, map(_speed,MOTORSPEED_MIN,MOTORSPEED_MAX,0,255));
  return true;
}

bool MYO_Motor::setDirection(int aimedPosition){
  if(aimedPosition > _currentPosition){
    digitalWrite(_pinA, LOW);
    digitalWrite(_pinB, HIGH);
    return true;
  }else{
    digitalWrite(_pinA, HIGH);
    digitalWrite(_pinB, LOW);
    return false;
  }
}

bool MYO_Motor::inPosition(int aimedPosition){
   _currentPosition = map(analogRead(_pinPot),0,4095,POSITION_MIN,POSITION_MAX);
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
