#include <Arduino.h>

#include "Constants.h"
#include "StateMachine.h"

void StateMachine::start(){

  log_e(">> start");

  state = STATE_INACTIVE;
  transition = TRANSITION_TO_INACTIVE;

}
 
void StateMachine::reset(){

  log_e(">> reset");

  state = STATE_INACTIVE;
  transition = TRANSITION_TO_INACTIVE;
}
  

int StateMachine::getTransitionToPerform(int transition){
    

    log_e(">> getTransitionToPerform: %i", transition);

    int transitionToPerform = TRANSITION_TO_NOTHING;

    switch(transition){

    // TODO: Encontar un modo de bloqueo por el que si estamos inactivos
    //       aunque llevemos acabo acciones no hay entrada de estados.
    case TRANSITION_TO_INACTIVE:
        transitionToPerform = TRANSITION_TO_INACTIVE;
        state = STATE_INACTIVE;
    break;

    case TRANSITION_TO_IDLE:
	    if(state != TRANSITION_TO_IDLE){	
        transitionToPerform = TRANSITION_TO_IDLE;
        state = STATE_IDLE;
      }
      break;

      case TRANSITION_TO_TONGS:
        if(state != STATE_INACTIVE && state != TRANSITION_TO_TONGS){
          transitionToPerform = TRANSITION_TO_TONGS;
          state = STATE_TONGS;
        }
      break;

      default:
      break;

    }

    return transitionToPerform;
}

int StateMachine::getState(){

	log_e(">> getState: %d", state);

	return state;
}

void StateMachine::setState(int currentState){

	log_e(">> setState: %d", state);

	state = currentState;
}


int StateMachine::getForefingerPosition(){
  
	int fingerPosition   = FINGER_POSITION_MATRIX[state][FOREFINGER];
	log_e(">> getForefingerPosition - State[%i] - Pos[%i]", state, fingerPosition);

	return fingerPosition;

}

int StateMachine::getThumbPosition(){
  
	int fingerPosition   = FINGER_POSITION_MATRIX[state][THUMB];
	log_e(">> getThumbPosition - State[%i] - Pos[%i]", state, fingerPosition);

	return fingerPosition;

}

