#include <PID_v1.h>
#include "InputOutputUtils.h"

/******************************************************************************/
/* INITIALIZATION INPUT METHODS                                               */
/******************************************************************************/

void InputOutputUtils::initializeInputElements() {

	//logger.debug((char*)"IOUTILS::initializeInputElements\n");

	relativePotMittenValue = 0;
	relativePotForefingerValue = 0;
	relativePotThumbValue = 0;

	//initializeRelativePotsValue();

	//int input = map(multiplexorRead(CONTROL_INPUT_POTENTIOMETER_MITTEN), 0, 1024, MOTOR_SPEED_MIN, MOTOR_SPEED);

	//logger.info((char*)"IOUTILS::initializeInputElements - Initial position for mittem %i\n", input);


}

void InputOutputUtils::resetInputElements() {

	logger.debug((char *)"IOUTILS::resetInput\n");

	relativePotMittenValue = 0;
	relativePotForefingerValue = 0;
	relativePotThumbValue = 0;

	//initializeRelativePotsValue();

	// TOREMEMBER
	//myowareSensorController1.calibration();
	//myowareSensorController2.calibration();

}

/******************************************************************************/
/* INITIALIZATION OUTPUT METHODS                                              */
/******************************************************************************/

void InputOutputUtils::initializeOutputElements() {


	logger.info((char*)"IOUTILS::initOutput\n");

	// Initialize motors pinout
	pinMode(MUX_A, OUTPUT);
	pinMode(MUX_B, OUTPUT);
	pinMode(MUX_C, OUTPUT);
  
	// Initialize motors pinout
	pinMode(PIN_OUTPUT_MOTOR_MITTEN_PWM, OUTPUT);
	pinMode(PIN_OUTPUT_MOTOR_MITTEN, OUTPUT);
	pinMode(PIN_OUTPUT_MOTOR_FOREFINGER_PWM, OUTPUT);
	pinMode(PIN_OUTPUT_MOTOR_FOREFINGER, OUTPUT);
	pinMode(PIN_OUTPUT_MOTOR_THUMB_PWM, OUTPUT);
	pinMode(PIN_OUTPUT_MOTOR_THUMB, OUTPUT);
  
}

void InputOutputUtils::resetOutputElements() {

	//logger.debug((char*)"IOUTILS::resetOutput\n");

	initializeOutputElements();

}


/******************************************************************************/
/* FINGERS POSITION                                                           */
/******************************************************************************/

int InputOutputUtils::getMittenPosition() {

	// TODO: What happens if finger position is diferent to current position?
	// Tenedremos que revisar en que posicion se encuentar el dedo realmente para
	// restaurar la posicion si es necesario.
	int mittenPosition = currentState.getMittenPosition();

	logger.info((char*)"IOUTILS::getMittenPosition: %i\n", mittenPosition);

	return mittenPosition;

}

int InputOutputUtils::getForefingerPosition() {

	// TODO: What happens if finger position is diferent to current position?
	// Tenedremos que revisar en que posicion se encuentar el dedo realmente para
	// restaurar la posicion si es necesario.
	int forefingerPosition = currentState.getForefingerPosition();

	//logger.debug((char*)"IOUTILS::getForefingerPos: %i\n", forefingerPosition);

	return forefingerPosition;
}

int InputOutputUtils::getThumbPosition() {

	// TODO: What happens if finger position is diferent to current position?
	// Tenedremos que revisar en que posicion se encuentar el dedo realmente para
	// restaurar la posicion si es necesario.
	int thumbPosition = currentState.getThumbPosition();

	//logger.debug((char*)"getThumbPos: %i\n", thumbPosition);

	return thumbPosition;

}

/******************************************************************************/
/* TRANSITIONS                                                                */
/******************************************************************************/

int InputOutputUtils::getTransitionToPerform(State state) {

	logger.debug((char*)"IOUTILS::getTrans\n");

	currentState = state;

	// TOREMEMBER
	//boolean activation1 = myowareSensorController1.activation();
	//logger.info((char*)"IOUTILS::myowareSensorController1 - activation: %d\n", activation1);
	//boolean activation2 = myowareSensorController2.activation();
	//logger.info((char*)"IOUTILS::myowareSensorController2 - activation: %d\n", activation2);

	int transitionTo = 0;

	// Secuencial
	// ROSA
	static int i = 0;
	transitionTo = ((i++)%STATES_NUMBER);
	delay(10000);

	// Menu
	transitionTo = test.testInputForTransition();

	return transitionTo;
	
}


void InputOutputUtils::openMitten() {

	//logger.debug((char*)"IOUTILS::openMitten\n");

    if(getMittenPosition() == CLOSE){
		  logger.info((char*)"IOUTILS::openMitten-OPEN\n");
		  fingerControl(MITTEN, OPEN, CONTROL_INPUT_POTENTIOMETER_MITTEN);
	  }

}

void InputOutputUtils::closeMitten() {

	logger.debug((char*)"IOUTILS::closeMitten\n");

	if(getMittenPosition() == OPEN){
		logger.info((char*)"IOUTILS::closeMitten-CLOSE\n");
		fingerControl(MITTEN, CLOSE, CONTROL_INPUT_POTENTIOMETER_MITTEN);
	}
}

void InputOutputUtils::openForefinger() {

	logger.debug((char*)"IOUTILS::openForefinger\n");

	if(getForefingerPosition() == CLOSE){
		logger.info((char*)"IOUTILS::openForefinger-OPEN\n");
		fingerControl(FOREFINGER, OPEN, CONTROL_INPUT_POTENTIOMETER_FOREFINGER);
	}
}

void InputOutputUtils::closeForefinger() {

	//logger.debug((char*)"IOUTILS::closeForefinger\n");

	if(getForefingerPosition() == OPEN){
		logger.info((char*)"IOUTILS::closeForefinger-CLOSE\n");
		fingerControl(FOREFINGER, CLOSE,CONTROL_INPUT_POTENTIOMETER_FOREFINGER);
	}
}

void InputOutputUtils::openThumb() {

	logger.info((char*)"IOUTILS::openThumb\n");

	if(getThumbPosition() == CLOSE){
		logger.info((char*)"IOUTILS::openThumb-OPEN\n");
		fingerControl(THUMB, OPEN, CONTROL_INPUT_POTENTIOMETER_THUMB);
	}

}

void InputOutputUtils::closeThumb() {

	//logger.info((char*)"IOUTILS::closeThumb\n");

	if(getThumbPosition() == CLOSE){
		logger.info((char*)"IOUTILS::closeThumb-CLOSE\n");
		fingerControl(THUMB,CLOSE,CONTROL_INPUT_POTENTIOMETER_THUMB);
	}

}


/******************************************************************************/
/* PCB CONTROLS                                                               */
/******************************************************************************/



void InputOutputUtils::initializeRelativePotsValue() {

	relativePotMittenValue = initializePotMultiplexorRead(CONTROL_INPUT_POTENTIOMETER_MITTEN);
	relativePotForefingerValue = initializePotMultiplexorRead(CONTROL_INPUT_POTENTIOMETER_FOREFINGER);
	relativePotThumbValue = initializePotMultiplexorRead(CONTROL_INPUT_POTENTIOMETER_THUMB);

}


int InputOutputUtils::getRelativePotValue(int controlId, int currentValue) {

	int relativeValue = 0;

	 if(controlId == CONTROL_INPUT_POTENTIOMETER_MITTEN)
		 relativeValue = currentValue - relativePotMittenValue;
	  else if (controlId == CONTROL_INPUT_POTENTIOMETER_FOREFINGER)
		 relativeValue = currentValue - relativePotForefingerValue;
	 else if  (controlId == CONTROL_INPUT_POTENTIOMETER_THUMB)
		 relativeValue = currentValue - relativePotThumbValue;


	 if (relativeValue < 0)
		 relativeValue = 1024 - relativeValue;

	 return relativeValue;

}


void InputOutputUtils::initialFingerControl(int motorId,  int controlId){

	//initialFingerControlTime(motorId, controlId);
	initialFingerControlPID(motorId, controlId);
}

void InputOutputUtils::initialFingerControlTime(int motorId,  int controlId){

	//logger.info((char*)"IOUTILS::initialFingerControlTime\n");

	int initialPosition = multiplexorRead(controlId);
	int finalPosition = initialPosition;
	logger.info((char*)"IOUTILS::initialFingerControlTime-initialPos: %d\n", initialPosition);

	if(finalPosition < 200){
		while(finalPosition < 200){
			motorControl(motorId, CLOSE, 100);
			delay(100);
			finalPosition = multiplexorRead(controlId);
		}
	}

	if(finalPosition > 800){
		while(finalPosition > 800){
			motorControl(motorId, OPEN, 100);
			delay(100);
			finalPosition = multiplexorRead(controlId);
		}
	}

	logger.info((char*)"IOUTILS::initialFingerControlTime-finalPos: %d\n", finalPosition);

}

void InputOutputUtils::initialFingerControlPID(int motorId,  int controlId){

	logger.info((char*)"IOUTILS::initialFingerControlPID\n");

	double setpoint, input, output;
	int motorDir;

	input = map(multiplexorRead(controlId), 0, 1024, MOTOR_SPEED_MIN, MOTOR_SPEED);
	//input = multiplexorRead(controlId);
	logger.info((char*)"IOUTILS::initialFingerControlPID - input: %f\n", input);

	setpoint = 0;
	logger.info((char*)"IOUTILS::initialFingerControlPID - initialization setpoint: %f\n", setpoint);

	PID pid = PID(&input, &output, &setpoint, PID_KP, PID_KI, PID_KD, REVERSE);
	motorDir = OPEN;

	//Turn on the PID loop
	pid.SetMode(AUTOMATIC);
	pid.SetOutputLimits(0,MOTOR_SPEED);

	while(abs(input - setpoint) >  PID_LIMITS){

		input = map(multiplexorRead(controlId), 0, 1024, MOTOR_SPEED_MIN, MOTOR_SPEED);
		//input = multiplexorRead(controlId);

		pid.Compute();

		motorControl(motorId, motorDir, round(output));

		input = map(multiplexorRead(controlId), 0, 1024, MOTOR_SPEED_MIN, MOTOR_SPEED);
		//input = multiplexorRead(controlId);
		logger.info((char*)"IOUTILS::initialFingerControlPID - loop input: %f\n", input);
		logger.info((char*)"IOUTILS::initialFingerControlPID - loop output: %f\n", output);

	}

	logger.info((char*)"IOUTILS::initialFingerControlPID - Stop motor \n");
	motorControl(motorId, motorDir, MOTOR_SPEED_MIN);

}


void InputOutputUtils::fingerControl(int motorId, int motorDir, int controlId){

	logger.info((char*)"IOUTILS::fingerControl\n");

	//fingerControlTime(motorId, motorDir, controlId);
	fingerControlPID(motorId, motorDir, controlId);

}

void InputOutputUtils::fingerControlTime(int motorId, int motorDir, int controlId){

	logger.info((char*)"IOUTILS::fingerControlTime\n");

	int initialPosition = multiplexorRead(controlId);
	int finalPosition = initialPosition;
	logger.info((char*)"IOUTILS::fingerControlTime-Initial pos: %d\n", initialPosition);

	if((finalPosition < 200) || (finalPosition > 800)){

		initialFingerControl(motorId, controlId);
		logger.info((char*)"IOUTILS::fingerControlTime-Execute again finger control");
		fingerControl(motorId, motorDir, controlId);

	}else if((finalPosition) > 200 && (motorDir == OPEN)){

		motorControl(motorId, OPEN , MOTOR_SPEED);
		delay(100);
		motorControl(motorId, OPEN, MOTOR_SPEED_MIN);
		finalPosition = multiplexorRead(controlId);

	}else if ((finalPosition < 800) && (motorDir == CLOSE)){
		motorControl(motorId, CLOSE , MOTOR_SPEED);
		delay(100);
		motorControl(motorId, CLOSE, MOTOR_SPEED_MIN);
		finalPosition = multiplexorRead(controlId);

	}

	logger.info((char*)"IOUTILS::fingerControlTime-Final pos: %d\n", finalPosition);
      
}

void InputOutputUtils::fingerControlPID(int motorId, int motorDir, int controlId){

    logger.info((char*)"IOUTILS::fingerControlPID\n");

    double setpoint, input, output;

    input = map(multiplexorRead(controlId), 0, 1023, 0, MOTOR_SPEED);
	//input = multiplexorRead(controlId);

    logger.info((char*)"IOUTILS::fingerControlPID - input: %f\n", input);

    PID pid = PID(&input, &output, &setpoint, PID_KP, PID_KI, PID_KD, REVERSE);

    if (motorDir == OPEN){

    	setpoint = MOTOR_SPEED_MIN;
    	logger.info((char*)"IOUTILS::fingerControlPID - OPEN - final setpoint: %f\n", setpoint);
  
    	// Initialize PID
    	pid = PID(&input, &output, &setpoint, PID_KP, PID_KI, PID_KD, REVERSE);


    }else if (motorDir == CLOSE){

    	setpoint = MOTOR_SPEED;
    	logger.info((char*)"IOUTILS::fingerControlPID - CLOSE  - final setpoint: %f\n", setpoint);
  
    	// Initialize PID
    	pid = PID(&input, &output, &setpoint, PID_KP, PID_KI, PID_KD, DIRECT);
    }

    //Turn on the PID loop
    pid.SetMode(AUTOMATIC);
    pid.SetOutputLimits(0, MOTOR_SPEED);

    while(abs(input - setpoint) >  PID_LIMITS){

    	input = map(multiplexorRead(controlId), 0, 1024, 0, MOTOR_SPEED);
    	//input = multiplexorRead(controlId);

    	pid.Compute();
      
    	motorControl(motorId, motorDir, round(output));

      logger.info((char*)"IOUTILS::fingerControlPID - setpoint value: %f\n", setpoint);
      logger.info((char*)"IOUTILS::fingerControlPID - input value:    %f\n", input);
    	logger.info((char*)"IOUTILS::fingerControlPID - output value:   %f\n", output);

    }

    logger.info((char*)"IOUTILS::fingerControlPID - Stopping motor\n");
    motorControl(motorId, motorDir, MOTOR_SPEED_MIN);

}


void InputOutputUtils::motorControl(int motorID, int motorDir, int motorSpeed) {

   logger.info((char*)"IOUTILS::motorControl\n");

	// Forward Direction --> CLOSE --> 1
   	// 1024 --> 0 (decrements)
	if (motorDir) { 
		logger.info((char*)"IOUTILS::motorControl-forward direction-CLOSE\n");
		digitalWrite(MOTOR_CONTROL_MATRIX[motorID][1], LOW);
		//analogWrite(MOTOR_CONTROL_MATRIX[motorID][0], motorSpeed);
	// Backward Direction --> OPEN --> 0
	// 0 --> 1024 (increments)
	} else {
		logger.info((char*)"IOUTILS::motorControl-backward direction-OPEN\n");
		digitalWrite(MOTOR_CONTROL_MATRIX[motorID][1], HIGH);
		//analogWrite(MOTOR_CONTROL_MATRIX[motorID][0], (MOTOR_SPEED_MAX - motorSpeed));
	}
  
}


int InputOutputUtils::multiplexorRead(int controlId){

	// Main Multiplexer (vs Acc Multiplexer)
		
	// Lecture Sensors through 74HC4051 Multiplexer
	// Entry channel selection for 74HC4051
	
	logger.info((char*)"IOUTILS::multiplexorRead-input[%i]\n", controlId);

	int cA = controlId & 0x01;   
	int cB = (controlId>>1) & 0x01;     
	int cC = (controlId>>2) & 0x01;   
	
	digitalWrite(MUX_A, cA);
	digitalWrite(MUX_B, cB);
	digitalWrite(MUX_C, cC);
  
	int readedValue = analogRead(MUX_MAIN);

	if ((controlId == CONTROL_INPUT_POTENTIOMETER_MITTEN) || (controlId == CONTROL_INPUT_POTENTIOMETER_FOREFINGER) || (controlId == CONTROL_INPUT_POTENTIOMETER_THUMB))
		readedValue = getRelativePotValue(controlId, readedValue);

	logger.info((char*)"IOUTILS::multiplexorRead-output[%i]\n", readedValue);
	
	return readedValue;

}

int InputOutputUtils::initializePotMultiplexorRead(int controlId){

	// Main Multiplexer (vs Acc Multiplexer)

	// Lecture Sensors through 74HC4051 Multiplexer
	// Entry channel selection for 74HC4051

	logger.info((char*)"IOUTILS::initializePotMultiplexorRead-input[%i]\n", controlId);

	int cA = controlId & 0x01;
	int cB = (controlId>>1) & 0x01;
	int cC = (controlId>>2) & 0x01;

	digitalWrite(MUX_A, cA);
	digitalWrite(MUX_B, cB);
	digitalWrite(MUX_C, cC);

	int readedValue = analogRead(MUX_MAIN);

	logger.info((char*)"IOUTILS::initializePotMultiplexorRead-output[%i]\n", readedValue);

	return readedValue;

}


InputOutputUtils inputOutputUtils = InputOutputUtils();
