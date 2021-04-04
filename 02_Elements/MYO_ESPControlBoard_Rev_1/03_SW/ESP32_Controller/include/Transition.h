#ifndef TRANSITION_H
#define TRANSITION_H

#include "InputOutputUtils.h"

class Transition{

	private:

	State currentState;
    InputOutputUtils inputOutputUtils;
	
	public:

	// Constructor
    Transition();
    Transition(InputOutputUtils inputOutputUtils);
    
	// Resets state
    void reset();

	// Gets the state selected by user from input elements feedback
    int getTransitionToPerform(State state);

	// Goes to innactive state depending on the current one
    void transitionToInactive();
	// Goes to idle state depending on the current one
    void transitionToIdle();
	// Goes to tongs state depending on the current one
    void transitionToTongs();
	// Goes to finger state depending on the current one
    void transitionToFinger();
	// Goes to close state depending on the current one
    void transitionToClose();
	// Goes to fist state depending on the current one
    void transitionToFist();

  };

#endif
