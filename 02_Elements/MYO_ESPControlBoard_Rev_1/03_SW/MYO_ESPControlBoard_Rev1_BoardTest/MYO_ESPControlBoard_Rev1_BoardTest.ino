
#include <Adafruit_NeoPixel.h>

// Pin Definition
const int pMOT_EN_0     = 4;
const int pMOT_A_0      = 18;
const int pMOT_B_0      = 19;
const int pMPOT_0       = 27;

const int pMOT_EN_1     = 5;
const int pMOT_A_1      = 25;
const int pMOT_B_1      = 14;
const int pMPOT_1       = 32;

const int pMSEN_0       = 12;
const int pMSEN_1       = 33;

const int pLED_RGB      = 17;

const int pSW_0         = 16;

const int pSDA          = 21;
const int pSCL          = 22;


Adafruit_NeoPixel ledRGB = Adafruit_NeoPixel(1, pLED_RGB, NEO_RGB + NEO_KHZ800);

//Adafruit_NeoPixel pixels = Adafruit_NeoPixel(1, pLED_RGB, NEO_GRB + NEO_KHZ800);

bool memorySW = false;

void setup() {
  Serial.begin(115200);
  ledRGB.begin();
  ledRGB.setPixelColor(0, 255, 0, 255); // Moderately bright green color.
  ledRGB.show(); // This sends the updated pixel color to the hardware.
  delay(500); // Delay for a period of time (in milliseconds).
  pinMode(pMOT_EN_0,  OUTPUT);
  pinMode(pMOT_A_0,   OUTPUT);
  pinMode(pMOT_B_0,   OUTPUT);
  pinMode(pMOT_EN_1,  OUTPUT);
  pinMode(pMOT_A_1,   OUTPUT);
  pinMode(pMOT_B_1,   OUTPUT);
  pinMode(pSW_0,      INPUT);
  digitalWrite(pMOT_EN_0,  LOW);
  digitalWrite(pMOT_A_0,  LOW);
  digitalWrite(pMOT_B_0,  LOW);
  digitalWrite(pMOT_EN_1,  LOW);
  digitalWrite(pMOT_A_1,  LOW);
  digitalWrite(pMOT_B_1,  LOW);

}

void loop() {
  if(swActiveMomentary()){
    Serial.println("");
    Serial.println("PUSH!");
    ledRGB.setPixelColor(0, random(0,100), random(0,100), random(0,100)); // Moderately bright green color.
  }
  Serial.print(".");
  ledRGB.show(); // This sends the updated pixel color to the hardware.
  delay(10);
}

bool swActiveMomentary(){
  bool newSW = digitalRead(pSW_0);
  if((memorySW)&&(!newSW)){
    memorySW = newSW;
    return true;
  }else{
    memorySW = newSW;
    return false;
  }
}
