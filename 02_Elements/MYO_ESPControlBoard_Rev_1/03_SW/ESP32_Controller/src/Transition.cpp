#include "Transition.h"


/******************************************************************************/
/* PUBLIC METHODS                                                             */
/******************************************************************************/

Transition::Transition(){}

Transition::Transition(InputOutputUtils inputOutputUtils){
	logger.debug("TRANS::Transition\n");
	this->inputOutputUtils = inputOutputUtils;
}

void Transition::reset(){

	logger.debug("TRANS::reset\n");
	this->inputOutputUtils = inputOutputUtils;
}

int Transition::getTransitionToPerform(State state){

	logger.debug("TRANS::getTrans2Perform\n");

	currentState = state;
	return inputOutputUtils.getTransitionToPerform(state);
}

void Transition::transitionToInactive(){

	logger.debug("TRANS::trans2Inactive\n");

	inputOutputUtils.openMitten();
	inputOutputUtils.openForefinger();
	inputOutputUtils.openThumb();
}

void Transition::transitionToIdle(){

	logger.debug("TRANS::trans2Idle\n");

	if(currentState.getCurrentState() == STATE_INACTIVE){

		logger.info("IOUTILS::trans2Idle - Initialize mitten\n");
		inputOutputUtils.initialFingerControl(MITTEN, CONTROL_INPUT_POTENTIOMETER_MITTEN);

		logger.info("IOUTILS::trans2Idle-Init forefinger\n");
		inputOutputUtils.initialFingerControl(FOREFINGER, CONTROL_INPUT_POTENTIOMETER_FOREFINGER);

		logger.info("IOUTILS::trans2Idle-Init thumb\n");
		inputOutputUtils.initialFingerControl(THUMB, CONTROL_INPUT_POTENTIOMETER_THUMB);

	}else{

		inputOutputUtils.openMitten();
		inputOutputUtils.openForefinger();
		inputOutputUtils.openThumb();

	}
}

void Transition::transitionToTongs(){

	logger.debug("TRANS::trans2Tongs\n");

	inputOutputUtils.openMitten();
	inputOutputUtils.closeForefinger();
	inputOutputUtils.closeThumb();
}

void Transition::transitionToFinger(){

	logger.debug("TRANS::trans2Finger\n");

	inputOutputUtils.closeMitten();
	inputOutputUtils.openForefinger();
	inputOutputUtils.closeThumb();
}

void Transition::transitionToClose(){

	logger.debug("TRANS::trans2Close\n");

	inputOutputUtils.closeMitten();
	inputOutputUtils.closeForefinger();
	inputOutputUtils.openThumb();
}

void Transition::transitionToFist(){

	logger.debug("TRANS::trans2Fist\n");

	inputOutputUtils.closeMitten();
	inputOutputUtils.closeForefinger();
	inputOutputUtils.closeThumb();
}

