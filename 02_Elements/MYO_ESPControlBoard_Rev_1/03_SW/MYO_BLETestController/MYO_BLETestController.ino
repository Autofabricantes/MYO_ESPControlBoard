/*  MYO_BLETestController
 * 
 * 
 * 
 */

#include <driver/dac.h>
#include "BluetoothSerial.h"
#include "MYO_Motor.h"
#include "MYO_LED.h"
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Pin Definition
#define MOT_EN_0    4   // GPIO 4
#define MOT_A_0     18  // GPIO 18
#define MOT_B_0     19  // GPIO 19
#define MPOT_0      27  // GPIO 27
#define MSEN_0      33  // GPIO 33

#define MOT_EN_1    5   // GPIO 5
#define MOT_A_1     25  // GPIO 25
#define MOT_B_1     14  // GPIO 14
#define MPOT_1      32  // GPIO 32
#define MSEN_1      34  // GPIO 34

#define SW_0        16  // GPIO 16

#define LED_RGB     17  // GPIO17

BluetoothSerial SerialBT;
MYO_LED   LED(LED_RGB);
MYO_Motor MOT_0(MOT_EN_0, MOT_A_0, MOT_B_0, MPOT_0, MSEN_0);
MYO_Motor MOT_1(MOT_EN_1, MOT_A_1, MOT_B_1, MPOT_1, MSEN_1);

void readSerialCommand(){
    if (SerialBT.available()) {
      //String value =  SerialBT.read());
      String value=SerialBT.readString();
      if (value.length() > 0) {
        for (int i = 0; i < value.length(); i++){
          Serial.print(value[i]);
        }
        if(value[0] == 'A'){
            
        }else if(value[0] == 'B'){

        }else if(value[0] == 'C'){

        }else{

        }
      }
    }
};

void setup() {

  MOT_0.stopLiberate();
  MOT_1.stopLiberate();
  LED.init();
  // LED Initialization
  for(int i = 0; i < 21; i++){
    LED.setColor(i);
    delay(500);
  }

  for(int i = 0; i < 19; i++){
    LED.blinkColor(i,500);
  }

  for(int i = 0; i < 19; i++){
    LED.fadeColor(i,i+1,500);
  }

  for(int i = 0; i < 19; i++){
    LED.fadeandOffColor(i,i+1,500);
    delay(500);
  }


  

  MOT_0.stopLiberate();
  MOT_1.stopLiberate();

  delay(2000);

  MOT_0.setDirection(0);
  MOT_1.setDirection(100);
  MOT_0.setEnable();
  MOT_1.setEnable();

  delay(2000);

  MOT_0.setDirection(0);
  MOT_1.setDirection(100);
  MOT_0.setEnable();
  MOT_1.setEnable();

  delay(2000);

  MOT_0.stopLiberate();
  MOT_1.stopLiberate();

  Serial.begin(9600); 
  SerialBT.begin("MYO_ATF"); //Bluetooth device name
  Serial.println("Waiting a client connection to notify...");
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(200);
  SerialBT.print("Looking good girl!\n");
  readSerialCommand();
  
}
