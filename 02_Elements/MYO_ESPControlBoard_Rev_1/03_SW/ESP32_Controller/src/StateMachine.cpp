#include "StateMachine.h"
#include "Constants.h"


/******************************************************************************/
/* PUBLIC METHODS                                                             */
/******************************************************************************/

void StateMachine::start(){

  logger.debug((char*)"STM::start\n");

  state = State();
  transition = Transition();

}
 
void StateMachine::reset(){

  logger.debug((char*)"STM::reset\n");

  state.reset();
  transition.reset();
}
  

void StateMachine::executeTransition(){

    logger.debug((char*)"STM::executeTrans\n");
    
    int transitionToPeform = transition.getTransitionToPerform(state);

    logger.debug((char*)"STM::executeTrans: %i\n", transitionToPeform);

    switch(transitionToPeform){

      case INVALID_TRANSITION:
      break;

      case TRANSITION_TO_INACTIVE:
        transition.transitionToInactive();
        state.setCurrentState(STATE_INACTIVE);
      break;

      case TRANSITION_TO_IDLE:
        transition.transitionToIdle();
        state.setCurrentState(STATE_IDLE);
      break;

      case TRANSITION_TO_TONGS:
        if(state.getCurrentState() != STATE_INACTIVE){
          transition.transitionToTongs();
          state.setCurrentState(STATE_TONGS);
        }
      break;

      case TRANSITION_TO_FINGER:
        if(state.getCurrentState() != STATE_INACTIVE){
          transition.transitionToFinger();
          state.setCurrentState(STATE_FINGER);
        }
      break;

      case TRANSITION_TO_CLOSE:
        if(state.getCurrentState() != STATE_INACTIVE){
          transition.transitionToClose();
          state.setCurrentState(STATE_CLOSE);
        }
      break;

      case TRANSITION_TO_FIST:
        if(state.getCurrentState() != STATE_INACTIVE){
          transition.transitionToFist();
          state.setCurrentState(STATE_FIST);
        }
      break;

      default:
      break;

    }
}



