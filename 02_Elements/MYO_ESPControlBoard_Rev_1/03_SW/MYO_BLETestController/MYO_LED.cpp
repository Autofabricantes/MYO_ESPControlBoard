#include "Arduino.h"
#include"MYO_LED.h"
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
/*                    
class MYO_LED
{
  public:
    MYO_LED(int pinEn);
    void setColor(int colorCode);
    void setOff();
    void blinkColor(int colorCode, int blinkDuration);
    void fadeColor(int initColorCode, int endColorCode, int fadeDuration);
    void fadeandOffColor(int initColorCode, int endColorCode, int fadeDuration);
  private:
    int _pinLed;
    int _nowR;
    int _nowG;
    int _nowB;
};
*/

MYO_LED::MYO_LED(int pinLed)
{
  // Pin Configuration
  _pinLed = pinLed;
  _nowR = 0;
  _nowG = 0;
  _nowB = 0;
}

void MYO_LED::init()
{
  // Pin Configuration
  _LED = Adafruit_NeoPixel(1, _pinLed, NEO_GRB + NEO_KHZ800);
  _LED.begin();                    // INITIALIZE NeoPixel strip object
  _LED.show();
  _LED.setPixelColor(0, 0, 0, 0);
  _LED.show();
}

void MYO_LED::setColor(int colorCode){
  _LED.setPixelColor(0, gamma8[COL[colorCode][0]], gamma8[COL[colorCode][1]], gamma8[COL[colorCode][2]]);
  _LED.show();
  _nowR = COL[colorCode][0];
  _nowG = COL[colorCode][1];
  _nowB = COL[colorCode][2];
}

void MYO_LED::setOff(){
  _LED.setPixelColor(0, 0, 0, 0);
  _LED.show();
  _nowR = 0;
  _nowG = 0;
  _nowB = 0;
}

void MYO_LED::blinkColor(int colorCode, int blinkDuration){
  setColor(colorCode);
  delay(blinkDuration);
  setOff();
}

void MYO_LED::fadeColor(int initColorCode, int endColorCode, int fadeDuration){
  int fadeInterval = fadeDuration / NSTEPS; // in ms
  int fadeR = (COL[endColorCode][0] - COL[initColorCode][0]) / NSTEPS; // in ms
  int fadeG = (COL[endColorCode][1] - COL[initColorCode][1]) / NSTEPS; // in ms
  int fadeB = (COL[endColorCode][2] - COL[initColorCode][2]) / NSTEPS; // in ms
  for(int i = 0; i < NSTEPS; i++){
     _LED.setPixelColor(0, gamma8[COL[initColorCode][0] + (i+1)*fadeR], gamma8[COL[initColorCode][1] + (i+1)*fadeG], gamma8[COL[initColorCode][2] + (i+1)*fadeB]);
     _LED.show();
     delay(fadeInterval);
  }
  _nowR = COL[endColorCode][0];
  _nowG = COL[endColorCode][1];
  _nowB = COL[endColorCode][2];
}
    
void MYO_LED::fadeandOffColor(int initColorCode, int endColorCode, int fadeDuration){
  fadeColor(initColorCode, endColorCode, fadeDuration/2);
  fadeColor(endColorCode, initColorCode, fadeDuration/2);
  setOff();
}
