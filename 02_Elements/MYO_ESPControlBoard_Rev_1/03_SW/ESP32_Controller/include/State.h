#ifndef STATE_H
#define STATE_H

#include "Constants.h"
#include "State.h"

class State{

	private:

	// Current state
    int currentState;

	public:

	// Constructor
    State();
	
	// Resets state
    void reset();

	// Getters and setters
    int  getCurrentState();
    void setCurrentState(int state);

	// Detects mitten position from
	// current state
    int getMittenPosition();

	// Detects forefinger position from
	// current state
    int getForefingerPosition();

	// Detects thumb position from
    // current state
    int getThumbPosition();

  };

#endif
