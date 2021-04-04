#include "State.h"

/******************************************************************************/
/* PUBLIC METHODS                                                             */
/******************************************************************************/

State::State(){

	logger.debug("STATE::State\n");

	currentState = STATE_IDLE;
}

int State::getCurrentState(){

	logger.debug("STATE::getCurrentState: %d\n", currentState);

	return currentState;
}

void State::setCurrentState(int state){

	logger.info("STATE::setCurrentState: %d\n", state);

	currentState = state;
}

void State::reset(){

	logger.debug("STATE::reset\n");

	currentState = STATE_IDLE;
}


int State::getMittenPosition(){
		
	int fingerPosition   = FINGER_POSITION_MATRIX[currentState][MITTEN];
	logger.debug("STATE::getMittenPos - State[%i] - Pos[%i]\n", currentState, fingerPosition);

	return fingerPosition;

}

int State::getForefingerPosition(){
  
	int fingerPosition   = FINGER_POSITION_MATRIX[currentState][FOREFINGER];
	logger.debug("STATE::getForefingerPos - State[%i] - Pos[%i]\n", currentState, fingerPosition);

	return fingerPosition;

}

int State::getThumbPosition(){
  
	int fingerPosition   = FINGER_POSITION_MATRIX[currentState][THUMB];
	logger.debug("STATE::getThumbPos - State[%i] - Pos[%i]\n", currentState, fingerPosition);

	return fingerPosition;

}
