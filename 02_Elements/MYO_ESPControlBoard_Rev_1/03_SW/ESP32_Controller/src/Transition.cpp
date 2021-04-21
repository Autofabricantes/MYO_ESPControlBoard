#include "Transition.h"


/******************************************************************************/
/* PUBLIC METHODS                                                             */
/******************************************************************************/

Transition::Transition(){}

Transition::Transition(InputOutputUtils inputOutputUtils){
	logger.debug((char*)"TRANS::Transition\n");
	this->inputOutputUtils = inputOutputUtils;
}

void Transition::reset(){

	logger.debug((char*)"TRANS::reset\n");
	this->inputOutputUtils = inputOutputUtils;
}

int Transition::getTransitionToPerform(State state){

	logger.debug((char*)"TRANS::getTrans2Perform\n");

	currentState = state;
	return inputOutputUtils.getTransitionToPerform(state);
}

void Transition::transitionToInactive(){

	logger.debug((char*)"TRANS::trans2Inactive\n");

	inputOutputUtils.openForefinger();
	inputOutputUtils.openThumb();
}

void Transition::transitionToIdle(){

	logger.debug((char*)"TRANS::trans2Idle\n");

	if(currentState.getCurrentState() == STATE_INACTIVE){

		// TODO
		// Aquí tendríamos que diferenciar un paso de apagado a activo
		inputOutputUtils.openThumb();
		inputOutputUtils.openForefinger();

	}else{

		inputOutputUtils.openThumb();
		inputOutputUtils.openForefinger();

	}
}

void Transition::transitionToTongs(){

	logger.debug((char*)"TRANS::trans2Tongs\n");

	//inputOutputUtils.openMitten();
	inputOutputUtils.closeForefinger();
	inputOutputUtils.closeThumb();
}

// void Transition::transitionToFinger(){

// 	logger.debug((char*)"TRANS::trans2Finger\n");

// 	inputOutputUtils.closeMitten();
// 	inputOutputUtils.openForefinger();
// 	inputOutputUtils.closeThumb();
// }

// void Transition::transitionToClose(){

// 	logger.debug((char*)"TRANS::trans2Close\n");

// 	inputOutputUtils.closeMitten();
// 	inputOutputUtils.closeForefinger();
// 	inputOutputUtils.openThumb();
// }

// void Transition::transitionToFist(){

// 	logger.debug((char*)"TRANS::trans2Fist\n");

// 	inputOutputUtils.closeMitten();
// 	inputOutputUtils.closeForefinger();
// 	inputOutputUtils.closeThumb();
// }

