#include "Test.h"

/******************************************************************************/
/* PUBLIC METHODS                                                             */
/******************************************************************************/

// TODO 1
// Probra que no hay referencias cruzadas ejecutando por comandos las transiciones

int Test::getKeyboardTransition()
{
	int transition = 0;
	
	logger.info((char*)"Transition to: \n");
	logger.info((char*)" (0) STATE_INACTIVE\n");
	logger.info((char*)" (1) STATE_IDLE\n");
	logger.info((char*)" (2) STATE_TONGS\n");
	logger.info((char*)" (3) STATE_FINGER\n");
	logger.info((char*)" (4) STATE_CLOSE\n");
	logger.info((char*)" (5) STATE_FIST\n");
		
	logger.info((char*)"(10) EXIT\n");

	// send data only when you receive data
	while(!Serial.available());

	// read the incoming byte
	transition = Serial.parseInt();

	logger.info((char*)" Input value: %d\n", transition);

	return transition;
  
}

