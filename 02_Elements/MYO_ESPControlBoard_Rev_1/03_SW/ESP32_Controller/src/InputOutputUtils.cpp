#include <Arduino.h>

#include "InputOutputUtils.h"

/******************************************************************************/
/* INITIALIZATION INPUT METHODS                                               */
/******************************************************************************/

void InputOutputUtils::initIO() {

	log_e(">> initIO");

	stateMachine.start();

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

	//Init testing class
	//test = Test();

}

// Posiblemente pueda reutilizar INIT pero mantenemos esta por si necesito activar solo algunos elementos.
void InputOutputUtils::resetIO() {

	log_e(">> resetIO");

	// Reset potentiometers
	initPotValue(PIN_MPOT_0);
	initPotValue(PIN_MPOT_1);
	
}


/******************************************************************************/
/* TRANSITIONS                                                                */
/******************************************************************************/

// INPUT: Action received
void InputOutputUtils::executeTransition() {

	log_e(">> executeTransition");

	int inputTransition = TRANSITION_TO_NOTHING;
	int transtionToPerform = TRANSITION_TO_NOTHING;

	if (mode == TEST_MODE_TRANSITIONS)
		inputTransition = test.getKeyboardTransition();
	else
		inputTransition = test.getKeyboardTransition(); //myoUtils.getMyoTransition();

	transtionToPerform = stateMachine.getTransitionToPerform(inputTransition);

    if(transtionToPerform == TRANSITION_TO_INACTIVE)
        transitionToInactive();
    else if(transtionToPerform == TRANSITION_TO_IDLE)
        transitionToIdle();
    else if (transtionToPerform == TRANSITION_TO_TONGS)
        transitionToTongs();

	// TODO
	// Tendríamos que contralar de alguna manera que si ha habido un problema 
	// para ejecutar la transición debemos mantenernos en el estado que estábamos	
}

void InputOutputUtils::transitionToInactive(){

	log_e(">> transitionToInactive");

	// Open thumb + Open forefinger
	fingerControl(THUMB, OPEN, PIN_MPOT_1);	
	fingerControl(FOREFINGER, OPEN, PIN_MPOT_1);
}

void InputOutputUtils::transitionToIdle(){

	log_e("transitionToIdle");
	
	// Open thumb + Open forefinger
	fingerControl(THUMB, OPEN, PIN_MPOT_1);
	fingerControl(FOREFINGER, OPEN, PIN_MPOT_1);
}

void InputOutputUtils::transitionToTongs(){

	log_e(">> transitionToTongs");

	// Close thumb + Close forefinger
	fingerControl(THUMB,CLOSE, PIN_MPOT_0);
	fingerControl(FOREFINGER, CLOSE, PIN_MPOT_1);

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

	int thumbPosition = stateMachine.getThumbPosition();
	log_e(">> getThumbPosition: %i", thumbPosition);

	return thumbPosition;
}
int InputOutputUtils::getForefingerPosition() {

	int forefingerPosition = stateMachine.getForefingerPosition();
	log_e(">> getForefingerPosition: %i", forefingerPosition);

	return forefingerPosition;
}



/******************************************************************************/
/* PCB CONTROLS                                                               */
/******************************************************************************/

// TODO 
// Tener en cuenta las posibles conversiones/ajustes
// Necesito saber que potenciómetros son
void InputOutputUtils::initPotValue(int potId){
	log_e(">> initPotValue");

}

// TODO
// Tener en cuenta las posibles conversiones/ajustes
// Necesito saber que potenciómetros son
int InputOutputUtils::getPotValue(int potId){

	log_e(">> getPotValue");
	return 0;

}

// TODO 
void InputOutputUtils::fingerControl(int motor, int motorDir, int pot){

	log_e(">> fingerControl");

	// Control PID
	// Llamada a motors control

}

// TODO 
// Manejo motores con libreria ESP32Servo
// https://www.st.com/en/automotive-analog-and-power/vnh7100as.html
void InputOutputUtils::motorControl(int motorID, int motorDir, int motorSpeed) {

   log_e(">> motorControl");

	if (motorDir) { 
		log_e("motorControl - forward direction - CLOSE");
		 
	} else {
		log_e("motorControl - backward direction - OPEN");
		
	}
}
