#include "State.h"

/******************************************************************************/
/* PUBLIC METHODS                                                             */
/******************************************************************************/

State::State(){

	logger.debug((char*)"STATE::State\n");

	currentState = STATE_IDLE;
}

int State::getCurrentState(){

	logger.debug((char*)"STATE::getCurrentState: %d\n", currentState);

	return currentState;
}

void State::setCurrentState(int state){

	logger.info((char*)"STATE::setCurrentState: %d\n", state);

	currentState = state;
}

void State::reset(){

	logger.debug((char*)"STATE::reset\n");

	currentState = STATE_IDLE;
}


// int State::getMittenPosition(){
		
// 	int fingerPosition   = FINGER_POSITION_MATRIX[currentState][MITTEN];
// 	logger.debug((char*)"STATE::getMittenPos - State[%i] - Pos[%i]\n", currentState, fingerPosition);

// 	return fingerPosition;

// }

int State::getForefingerPosition(){
  
	int fingerPosition   = FINGER_POSITION_MATRIX[currentState][FOREFINGER];
	logger.debug((char*)"STATE::getForefingerPos - State[%i] - Pos[%i]\n", currentState, fingerPosition);

	return fingerPosition;

}

int State::getThumbPosition(){
  
	int fingerPosition   = FINGER_POSITION_MATRIX[currentState][THUMB];
	logger.debug((char*)"STATE::getThumbPos - State[%i] - Pos[%i]\n", currentState, fingerPosition);

	return fingerPosition;

}
