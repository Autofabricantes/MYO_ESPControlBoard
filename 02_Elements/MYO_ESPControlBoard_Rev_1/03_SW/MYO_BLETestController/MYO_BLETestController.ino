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
      String serialMessage = SerialBT.readString();
      if (serialMessage.length() > 0) {
        SerialBT.print("CMD Recieved: ");
        for (int i = 0; i < serialMessage.length(); i++){
          SerialBT.print(serialMessage[i]);
          
        }
        //SerialBT.println("");
        if(((serialMessage[0] == 'A')||(serialMessage[0] == 'B')) && (serialMessage.length()==7)){
          if(serialMessage[1] == 'P'){
            readCommandForMotorPosition(serialMessage);
          }else if(serialMessage[1] == 'S'){
            readCommandForMotorSpeed(serialMessage);
          }  
        }else if(serialMessage.substring(0,4).equals("STOP")){
          LED.fadeColor(BLUE_LOW, BLUE_HIGH, 500);
          MOT_0.stopLiberate();
          MOT_1.stopLiberate();
          LED.fadeColor(BLUE_LOW, BLUE_HIGH, 500);
        }else{
          SerialBT.println("Message Not Supported");
          LED.fadeColor(RED_LOW, RED_HIGH, 500);
        }
      }
    }
};

void setup() {
  LED.init();
  LED.setColor(CYAN_LOW);
  MOT_0.stopLiberate();
  MOT_1.stopLiberate();
  MOT_0.goToPosition(15);
  MOT_1.goToPosition(15);
  
  Serial.begin(9600); 
  SerialBT.begin("MYO_ATF"); //Bluetooth device name
  Serial.println("Waiting a client connection to notify...");
}

void loop() {
  // put your main code here, to run repeatedly:
  readSerialCommand();
  delay(10);
}

void readCommandForMotorPosition(String serialMessage){
  // First Check the message is correct (supported values between 0 and 100
  if(((serialMessage[2]== '0') || (serialMessage[2]== '1')) &&
     (((serialMessage[3]>= '0') && (serialMessage[3] <= '9')) &&
     ((serialMessage[4]>= '0') && (serialMessage[4] <= '9')))){
        int aimedPosition = (serialMessage[2] - 48)*100 + (serialMessage[3] - 48)*10 + (serialMessage[4] - 48)*1;
        if(aimedPosition > 100){
          aimedPosition = 100;
        }
        if(serialMessage[0] == 'A'){
          SerialBT.print("Motor A to position: ");
          SerialBT.println(aimedPosition);
          LED.fadeColor(BLUE_LOW, BLUE_HIGH, 500);
          MOT_0.goToPosition(map(aimedPosition, 0, 100, 15, 85));
        }else{
          SerialBT.print("Motor B to position: ");
          SerialBT.println(aimedPosition);
          LED.fadeColor(BLUE_LOW, BLUE_HIGH, 500);
          MOT_1.goToPosition(map(aimedPosition, 0, 100, 15, 85));
        }
  }else{
    SerialBT.print("Serial Message Incorrect: ");
    SerialBT.print(serialMessage);
    SerialBT.println(" .Use a notation with APXXX o BPXXX with values 000-100");
    LED.fadeColor(RED_LOW, RED_HIGH, 500);
  }
}

void readCommandForMotorSpeed(String serialMessage){
    // First Check the message is correct (supported values between 0 and 100
  if(((serialMessage[2]== '0') || (serialMessage[2]== '1')) &&
     (((serialMessage[3]>= '0') && (serialMessage[3] <= '9')) &&
     ((serialMessage[4]>= '0') && (serialMessage[4] <= '9')))){
        int aimedSpeed = (serialMessage[2] - 48)*100 + (serialMessage[3] - 48)*10 + (serialMessage[4] - 48)*1;
        if(aimedSpeed > 100){
          aimedSpeed = 100;
        }
        if(serialMessage[0] == 'A'){
          SerialBT.print("Motor A to speed: ");
          SerialBT.println(aimedSpeed);
          LED.fadeColor(TURQOUISE_LOW, TURQOUISE_HIGH, 500);
          MOT_0.setMotorSpeed(aimedSpeed);
        }else{
          SerialBT.print("Motor B to speed: ");
          SerialBT.println(aimedSpeed);
          LED.fadeColor(TURQOUISE_LOW, TURQOUISE_HIGH, 500);
          MOT_1.setMotorSpeed(aimedSpeed);
        }
  }else{
    SerialBT.print("Serial Message Incorrect: ");
    SerialBT.print(serialMessage);
    SerialBT.println(" .Use a notation with ASXXX o BSXXX with values 000-100");
    LED.fadeColor(RED_LOW, RED_HIGH, 500);
  }
}
