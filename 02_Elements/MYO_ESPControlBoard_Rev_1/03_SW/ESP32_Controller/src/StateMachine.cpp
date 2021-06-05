#include <Arduino.h>

#include "Constants.h"
#include "StateMachine.h"

void StateMachine::start(){

  log_i(">> start");

  currentState = STATE_INACTIVE;

}
 
void StateMachine::reset(){

  log_i(">> reset");

  currentState = STATE_INACTIVE;

}
  

int StateMachine::getTransitionToPerform(int state){
    
    log_i(">> getTransitionToPerform - state: %i", state);

    int transitionToPerform = TRANSITION_TO_NOTHING;

    switch(state){

    // TODO: Encontar un modo de bloqueo por el que si estamos inactivos
    //       aunque llevemos acabo acciones no hay entrada de estados.
    //       Podríamos definir un movimeinto de muñeca.
    case STATE_INACTIVE:
      if(currentState != STATE_INACTIVE && state != TRANSITION_TO_TONGS){
        transitionToPerform = TRANSITION_TO_INACTIVE;
        currentState = STATE_INACTIVE;
      }
    break;

    case STATE_IDLE:
	    if(currentState != TRANSITION_TO_IDLE){	
        transitionToPerform = TRANSITION_TO_IDLE;
        currentState = STATE_IDLE;
      }
      break;

      case STATE_TONGS:
        if(state != TRANSITION_TO_TONGS && state != STATE_INACTIVE){
          transitionToPerform = TRANSITION_TO_TONGS;
          currentState = STATE_TONGS;
        }
      break;

      default:
      break;

    }

    log_i(">> getTransitionToPerform - state: %i", transitionToPerform);

    return transitionToPerform;
}

int StateMachine::getState(){

	log_i(">> getState: %d", currentState);
	return currentState;
}

void StateMachine::setState(int currentState){

	log_i(">> setState: %d", currentState);

	currentState = currentState;
}


int StateMachine::getForefingerPosition(){
  
	int fingerPosition   = FINGER_POSITION_MATRIX[currentState][FOREFINGER];
	log_i(">> getForefingerPosition - State[%i] - Pos[%i]", currentState, fingerPosition);

	return fingerPosition;

}

int StateMachine::getThumbPosition(){
  
	int fingerPosition   = FINGER_POSITION_MATRIX[currentState][THUMB];
	log_i(">> getThumbPosition - State[%i] - Pos[%i]", currentState, fingerPosition);

	return fingerPosition;

}

