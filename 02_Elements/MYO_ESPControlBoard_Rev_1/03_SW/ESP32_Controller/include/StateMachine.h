#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include "State.h"
#include "Transition.h"

class StateMachine{

    public:
	
	// Starts state machine
    void start();

    // Resets state machine
	void reset();

    // Execute a transition
    void executeTransition();
    
   private:
   
	// State machine's state
    State state;
	// State machine's transition
    Transition transition;

   

};

#endif
