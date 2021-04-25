#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H


class StateMachine{

    public:
	
	// Starts state machine
    void start();

    // Resets state machine
	void reset();

    // Gets the state selected by user from input elements feedback
    int getTransitionToPerform(int transition);

    // Getters and setters
    int  getState();
    void setState(int state);

	// Detects forefinger position from
	// current state
    int getForefingerPosition();

	// Detects thumb position from
    // current state
    int getThumbPosition();

    
   private:

    // Current state
    int state;
    int transition;

};

#endif
