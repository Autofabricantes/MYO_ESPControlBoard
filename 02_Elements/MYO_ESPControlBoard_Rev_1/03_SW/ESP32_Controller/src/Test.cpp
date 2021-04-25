#include <Arduino.h>

#include "Test.h"

/******************************************************************************/
/* PUBLIC METHODS                                                             */
/******************************************************************************/


void Test::initTestingElements(){

	log_e(">> initTestingElements");
 	
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
	log_e(" (3) Transition to STATE_FINGER");
	log_e(" (4) Transition to STATE_CLOSE");
	log_e(" (5) Transition to STATE_FIST");

	log_e("(10) EXIT");

	// send data only when you receive data
	while(!Serial.available());

	// read the incoming byte
	transition = Serial.parseInt();

	log_e("Input value: %d", transition);

	return transition;
}

void Test::testingBoard(){

	// if(swActiveMomentary()){
    // 	log_e("PUSH!");
    // 	ledRGB.setPixelColor(0, random(0,100), random(0,100), random(0,100)); // Moderately bright green color.
  	// }
	// // This sends the updated pixel color to the hardware.
  	// ledRGB.show();
  	// delay(10);
}

	
bool Test::swActiveMomentary(){
//   bool newSW = digitalRead(PIN_SW_0);
//   if((memorySW)&&(!newSW)){
//     memorySW = newSW;
//     return true;
//   }else{
//     memorySW = newSW;
//     return false;
//   }

return false;

}


