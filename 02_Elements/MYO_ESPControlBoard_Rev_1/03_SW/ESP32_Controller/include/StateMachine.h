#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include "State.h"
#include "Transition.h"
#include "Test.h"

class StateMachine{

    public:
	
	// Starts state machine
    void start();
	// Execute a transition
    void executeTransition();
    void reset();

   private:
   
	// State machine's state
    State state;
	// State machine's transition
    Transition transition;

    // Test class
    Test test;

};

#endif
