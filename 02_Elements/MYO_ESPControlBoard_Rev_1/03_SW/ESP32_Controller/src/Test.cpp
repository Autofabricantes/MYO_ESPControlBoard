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


int Test::getKeyboardTransition(){
	int transition = 0;
	
	log_e("Transition to: ");
	log_e(" (0) Transition to STATE_INACTIVE");
	log_e(" (1) Transition to STATE_IDLE");
	log_e(" (2) Transition to STATE_TONGS");

	// send data only when you receive data
	while(!Serial.available());

	// read the incoming byte
	transition = Serial.parseInt();
	Serial.flush();

	log_e("Input value: %d", transition);

	return transition;
}

void Test::testingBoard(){

	log_e("Testing board: ");

	log_e(" (0) Close thumb");
	log_e(" (1) Open thumb");
	log_e(" (2) Close forefinger");
	log_e(" (3) Open forefinger");
	log_e(" (4) Get potentiometer thumb value");
	log_e(" (5) Get potentiometer thumb value");
	
	log_e(" (6) Switch");

	log_e(" (7) Get myo transition");
	log_e(" (8) Get myo samples/serial plot");

	log_e("(9) EXIT");

	// send data only when you receive data
	while(!Serial.available());

	// read the incoming byte
	int option = Serial.parseInt();
	Serial.flush();

	log_e("Input value: %d", option);

	switch(option){

		case 0:
			ioUtils->fingerControl(THUMB, CLOSE, PIN_MPOT_0);
		break;

		case 1: 
			ioUtils->fingerControl(THUMB, OPEN, PIN_MPOT_0);
		break;

		case 2:
			ioUtils->fingerControl(FOREFINGER, CLOSE, PIN_MPOT_1);
		break;

		case 3: 
			ioUtils->fingerControl(FOREFINGER, OPEN, PIN_MPOT_1);
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

		case 7: 
			ioUtils->getMyoTransitionTesting();
		return; 

		case 8: 
			ioUtils->getMyoSerialTesting();
		return; 

		case 9: 
		default:
		return; 
	}

}

void Test::switchLedRGB(){

	// if(swActiveMomentary()){
    // 	log_e("PUSH!");
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


