#include "Test.h"

/******************************************************************************/
/* PUBLIC METHODS                                                             */
/******************************************************************************/


Test::Test(){
	logger.info((char*)"Init test........................\n");
 	
	memorySW = false;

	ledRGB = Adafruit_NeoPixel(1, PIN_LED_RGB, NEO_RGB + NEO_KHZ800);
	ledRGB.begin();
	// Moderately bright green color.
 	ledRGB.setPixelColor(0, 255, 0, 255); 
	 // This sends the updated pixel color to the hardware.
  	ledRGB.show(); 
    // Delay for a period of time (in milliseconds).
	delay(500); 

}

int Test::getKeyboardTransition(){
	int transition = 0;
	
	logger.info((char*)"Transition to: \n");
	logger.info((char*)" (0) Transition to STATE_INACTIVE\n");
	logger.info((char*)" (1) Transition to STATE_IDLE\n");
	logger.info((char*)" (2) Transition to STATE_TONGS\n");
	logger.info((char*)" (3) Transition to STATE_FINGER\n");
	logger.info((char*)" (4) Transition to STATE_CLOSE\n");
	logger.info((char*)" (5) Transition to STATE_FIST\n");

	logger.info((char*)"(10) EXIT\n");

	// send data only when you receive data
	while(!Serial.available());

	// read the incoming byte
	transition = Serial.parseInt();

	logger.info((char*)" Input value: %d\n", transition);

	return transition;
  
}

void Test::testingBoard(){
	if(swActiveMomentary()){
    	Serial.println("");
    	Serial.println("PUSH!");
    	ledRGB.setPixelColor(0, random(0,100), random(0,100), random(0,100)); // Moderately bright green color.
  	}
  	Serial.print(".");
	// This sends the updated pixel color to the hardware.
  	ledRGB.show();
  	delay(10);
}

	
bool Test::swActiveMomentary(){
  bool newSW = digitalRead(PIN_SW_0);
  if((memorySW)&&(!newSW)){
    memorySW = newSW;
    return true;
  }else{
    memorySW = newSW;
    return false;
  }
}


