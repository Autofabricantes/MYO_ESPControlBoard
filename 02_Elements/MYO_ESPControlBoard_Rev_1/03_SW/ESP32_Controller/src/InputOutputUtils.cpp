#include <Arduino.h>

#include "InputOutputUtils.h"
#include "Test.h"

/******************************************************************************/
/* INITIALIZATION INPUT METHODS                                               */
/******************************************************************************/

void InputOutputUtils::initIO() {

	log_i(">> initIO");

	stateMachine.start();

	myoUtils.connect();

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

	//Myo connection
	//myoUtils.connect();

}

// Posiblemente pueda reutilizar INIT pero mantenemos esta por si necesito activar solo algunos elementos.
void InputOutputUtils::resetIO() {

	log_i(">> resetIO");

	// Reset potentiometers
	initPotValue(PIN_MPOT_0);
	initPotValue(PIN_MPOT_1);
	
}


/******************************************************************************/
/* TRANSITIONS                                                                */
/******************************************************************************/

// INPUT: Action received
void InputOutputUtils::executeTransition() {

	log_i(">> executeTransition");

	int inputTransition = TRANSITION_TO_NOTHING;
	int transtionToPerform = TRANSITION_TO_NOTHING;

	if (mode == TEST_MODE_TRANSITIONS)
		inputTransition = test->getKeyboardTransition();
	else
		inputTransition = myoUtils.getMyoTransition();

	transtionToPerform = stateMachine.getTransitionToPerform(inputTransition);

	log_i(">> executeTransition - transtion readed: %i", transtionToPerform);

    if(transtionToPerform == TRANSITION_TO_INACTIVE)
        transitionToInactive();
    else if(transtionToPerform == TRANSITION_TO_IDLE)
        transitionToIdle();
    else if (transtionToPerform == TRANSITION_TO_TONGS)
        transitionToTongs();

	// TODO: Tendríamos que contralar de alguna manera que si ha habido  
	// un problema para ejecutar la transición debemos mantenernos en 
	// un problema el estado que estábamos.	

	log_i("<< executeTransition");
}

void InputOutputUtils::transitionToInactive(){

	log_i(">> transitionToInactive");

	// Open thumb + Open forefinger
	fingerControl(THUMB, OPEN, PIN_MPOT_0);	
	fingerControl(FOREFINGER, OPEN, PIN_MPOT_1);
}

void InputOutputUtils::transitionToIdle(){

	log_i("transitionToIdle");
	
	// Open thumb + Open forefinger
	fingerControl(THUMB, OPEN, PIN_MPOT_0);
	fingerControl(FOREFINGER, OPEN, PIN_MPOT_1);
}

void InputOutputUtils::transitionToTongs(){

	log_i(">> transitionToTongs");

	// Close thumb + Close forefinger
	fingerControl(THUMB, CLOSE, PIN_MPOT_0);
	fingerControl(FOREFINGER, CLOSE, PIN_MPOT_1);

}

/******************************************************************************/
/* FINGERS POSITION                                                           */
/******************************************************************************/	
int InputOutputUtils::getThumbPosition() {

	int thumbPosition = stateMachine.getThumbPosition();
	log_i(">> getThumbPosition: %i", thumbPosition);

	return thumbPosition;
}
int InputOutputUtils::getForefingerPosition() {

	int forefingerPosition = stateMachine.getForefingerPosition();
	log_i(">> getForefingerPosition: %i", forefingerPosition);

	return forefingerPosition;
}



/******************************************************************************/
/* PCB CONTROLS                                                               */
/******************************************************************************/
void InputOutputUtils::initPotValue(int potId){

	// TODO: Reseto de pots. ¿Aplicamos una pos relativa?
	log_i(">> initPotValue(%i)", potId);

}

int InputOutputUtils::getPotValue(int potId){

	// TODO: Lectura de pots (posición relativa?)
	log_i(">> getPotValue(%i)", potId);
	return 0;

}

void InputOutputUtils::fingerControl(int motor, int motorDir, int pot){

	log_i(">> fingerControl(%i, %i, %i)", motor, motorDir, pot);

	// TODO
	// Control PID. Lectura de pot.
	// TODO: Control de los motores (llamada a motorControl).

}

// TODO: Manejo motores ¿con libreria ESP32Servo?
// https://www.st.com/en/automotive-analog-and-power/vnh7100as.html
void InputOutputUtils::motorControl(int motorID, int motorDir, int motorSpeed) {

   log_i(">> motorControl(%i, %i, %i)", motorID, motorDir, motorSpeed);

	if (motorDir) { 
		log_i("motorControl - forward direction - CLOSE");
		 
	} else {
		log_i("motorControl - backward direction - OPEN");
		
	}

	log_i("<< motorControl");
}



  void InputOutputUtils::getMyoTransitionTesting(){

	myoUtils.getMyoTransition();
	
}


  void InputOutputUtils::getMyoSerialTesting(){

	myoUtils.getMyoSerial();

}