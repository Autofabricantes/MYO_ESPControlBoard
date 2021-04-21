#include <PID_v1.h>
#include "InputOutputUtils.h"


/******************************************************************************/
/* INITIALIZATION INPUT METHODS                                               */
/******************************************************************************/

InputOutputUtils::InputOutputUtils(){}

void InputOutputUtils::initIO() {

	logger.debug((char*)"IOUTILS::initializeInputElements\n");

	// Initialize switch pinout
	pinMode(PIN_SW_0, INPUT);

	// Initialize motors pinout	
	pinMode(PIN_MOT_EN_0,  OUTPUT);
	pinMode(PIN_MOT_A_0,   OUTPUT);
	pinMode(PIN_MOT_B_0,   OUTPUT);
	pinMode(PIN_MPOT_0,    OUTPUT);

	pinMode(PIN_MOT_EN_1,  OUTPUT);
	pinMode(PIN_MOT_A_1,   OUTPUT);
	pinMode(PIN_MOT_B_1,   OUTPUT);
	pinMode(PIN_MPOT_1,    OUTPUT);
	
	// Potentiometers initialization
	initPotValue(PIN_MPOT_0);
	initPotValue(PIN_MPOT_1);

	// Myo connection
	myoUtils.connect();

	// Init testing class
	test = Test();

}

// Posiblemente pueda reutilizar INIT pero mantenemos esta por si necesito activar solo algunos elementos.
void InputOutputUtils::resetIO() {

	logger.debug((char *)"IOUTILS::resetIO\n");

	// Reset potentiometers
	initPotValue(PIN_MPOT_0);
	initPotValue(PIN_MPOT_1);
	
}

/******************************************************************************/
/* FINGERS POSITION                                                           */
/******************************************************************************/	
// TODO
// Ahora mismo simplemente recuperamos la posición de los dedos de la máquina 
// de estados.
// Tenedremos que revisar en que posicion se encuentar el dedo realmente para
// restaurar la posicion si es necesario.
int InputOutputUtils::getThumbPosition() {

	int thumbPosition = currentState.getThumbPosition();
	logger.debug((char*)"IOUTILS::getThumbPos: %i\n", thumbPosition);

	return thumbPosition;
}
int InputOutputUtils::getForefingerPosition() {

	int forefingerPosition = currentState.getForefingerPosition();
	logger.debug((char*)"IOUTILS::getForefingerPos: %i\n", forefingerPosition);

	return forefingerPosition;
}



/******************************************************************************/
/* TRANSITIONS                                                                */
/******************************************************************************/

// INPUT: Action received
int InputOutputUtils::getTransitionToPerform(State state) {

	logger.debug((char*)"IOUTILS::getTransitionToPerform\n");

	currentState = state;

	int transitionTo = 0;

	if (mode == TEST_MODE_TRANSITIONS)
		transitionTo = test.getKeyboardTransition();
	else
		transitionTo = myoUtils.getMyoTransition();

	return transitionTo;
	
}

// OUTPUT:  Action to perform

void InputOutputUtils::openThumb() {

	logger.info((char*)"IOUTILS::openThumb\n");

	if(getThumbPosition() == CLOSE){
		logger.info((char*)"IOUTILS::openThumb-OPEN\n");
		fingerControl(THUMB, OPEN, PIN_MPOT_1);
	}

}

void InputOutputUtils::closeThumb() {

	logger.info((char*)"IOUTILS::closeThumb\n");

	if(getThumbPosition() == CLOSE){
		logger.info((char*)"IOUTILS::closeThumb-CLOSE\n");
	if (mode != TEST_MODE_TRANSITIONS)
		fingerControl(THUMB,CLOSE, PIN_MPOT_0);
	}
}

void InputOutputUtils::openForefinger() {

	logger.debug((char*)"IOUTILS::openForefinger\n");

	if(getForefingerPosition() == CLOSE){
		logger.info((char*)"IOUTILS::openForefinger-OPEN\n");
		fingerControl(FOREFINGER, OPEN, PIN_MPOT_1);
	}
}

void InputOutputUtils::closeForefinger() {

	logger.debug((char*)"IOUTILS::closeForefinger\n");

	if(getForefingerPosition() == OPEN){
		logger.info((char*)"IOUTILS::closeForefinger-CLOSE\n");
		fingerControl(FOREFINGER, CLOSE, PIN_MPOT_1);
	}
}


/******************************************************************************/
/* PCB CONTROLS                                                               */
/******************************************************************************/

// TODO 
// Tener en cuenta las posibles conversiones/ajustes
// Necesito saber que potenciómetros son
void InputOutputUtils::initPotValue(int potId){
	logger.info((char*)"IOUTILS::setPotValue\n");

}

// TODO
// Tener en cuenta las posibles conversiones/ajustes
// Necesito saber que potenciómetros son
int InputOutputUtils::getPotValue(int potId){

	logger.info((char*)"IOUTILS::getPotValue\n");
	return 0;

}

// TODO 
void InputOutputUtils::fingerControl(int motor, int motorDir, int pot){

	logger.info((char*)"IOUTILS::fingerControl\n");

	// Control PID
	// Llamada a motors control

}

// TODO 
// Manejo motores con libreria ESP32Servo
// https://www.st.com/en/automotive-analog-and-power/vnh7100as.html
void InputOutputUtils::motorControl(int motorID, int motorDir, int motorSpeed) {

   logger.info((char*)"IOUTILS::motorControl\n");

	if (motorDir) { 
		logger.info((char*)"IOUTILS::motorControl - forward direction - CLOSE\n");
		 
	} else {
		logger.info((char*)"IOUTILS::motorControl - backward direction - OPEN\n");
		
	}
}
