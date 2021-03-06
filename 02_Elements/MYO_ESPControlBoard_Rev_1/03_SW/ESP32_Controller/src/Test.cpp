#include <Arduino.h>

#include "Test.h"

/******************************************************************************/
/* PUBLIC METHODS                                                             */
/******************************************************************************/

void Test::setIoUtils(InputOutputUtils * ioUtilsClass){

	ioUtils = ioUtilsClass;

	// memorySW = false;

	// ledRGB = Adafruit_NeoPixel(1, PIN_LED_RGB, NEO_RGB + NEO_KHZ800);
	// ledRGB.begin();
	// Moderately bright green color.
 	// ledRGB.setPixelColor(0, 255, 0, 255); 
	//  This sends the updated pixel color to the hardware.
  	// ledRGB.show(); 
    // Delay for a period of time (in milliseconds).
	// delay(500); 

}


int Test::getKeyboardStateToGet(){
	int transition = 0;
	
	log_i("Transition to: ");
	log_i(" (0) Transition to STATE_INACTIVE");
	log_i(" (1) Transition to STATE_IDLE");
	log_i(" (2) Transition to STATE_TONGS");
	log_i(" (3) Do nothing");

	// send data only when you receive data
	while(!Serial.available());

	// read the incoming byte
	transition = Serial.parseInt();
	Serial.flush();

	log_i("Input value: %d", transition);

	return transition;
}

void Test::testingBoard(){

	log_i("Testing board: ");

	log_i(" (0) Close thumb");
	log_i(" (1) Open thumb");
	log_i(" (2) Close forefinger");
	log_i(" (3) Open forefinger");
	log_i(" (4) Get potentiometer thumb value");
	log_i(" (5) Get potentiometer thumb value");
	
	log_i(" (6) Switch");

	// send data only when you receive data
	while(!Serial.available());

	// read the incoming byte
	int option = Serial.parseInt();
	Serial.flush();

	log_i("Input value: %d", option);

	switch(option){

		case 0:
			ioUtils->fingerControl(THUMB, CLOSE);
		break;

		case 1: 
			ioUtils->fingerControl(THUMB, OPEN);
		break;

		case 2:
			ioUtils->fingerControl(FOREFINGER, CLOSE);
		break;

		case 3: 
			ioUtils->fingerControl(FOREFINGER, OPEN);
		break;

		case 4:
			ioUtils->getPotValue(PIN_MPOT_0);
		break;

		case 5:
			ioUtils->getPotValue(PIN_MPOT_1);
		break;

		case 6:
			switchLedRGB();
		break;

		default:
		return; 
	}

}


void Test::switchLedRGB(){

	// if(swActiveMomentary()){
    // 	log_i("PUSH!");
    // 	ledRGB.setPixelColor(0, random(0,100), random(0,100), random(0,100)); // Moderately bright green color.
  	// }
	// // This sends the updated pixel color to the hardware.
  	// ledRGB.show();
  	// delay(10);
}
	
// bool Test::swActiveMomentary(){
//   bool newSW = digitalRead(PIN_SW_0);
//   if((memorySW)&&(!newSW)){
//     memorySW = newSW;
//     return true;
//   }else{
//     memorySW = newSW;
//     return false;
//   }
//return false;
//}


