#ifndef INPUT_OUTPUT_UTILS_H
#define INPUT_OUTPUT_UTILS_H

#include "Constants.h"
#include "StateMachine.h"
#include "Test.h"
//#include "myo.h"



class InputOutputUtils{

  private:

	int potForefingerValue;
	int potThumbValue;

    // Handles potentiometer
	void initPotValue(int potId);
    int  getPotValue(int potId);

    // Motor Control method
    void motorControl(int motorID, int motorDir, int motorSpeed);

	// Finger control methods
	void fingerControl(int motorId, int motorDir, int controlId);



  public:

    /*************************************************************************/
    /* INPUT METHODS                                                         */
    /*************************************************************************/

    // State to retrieve current finger's position
    StateMachine stateMachine;
    
    // Test controller
    Test test;

    // Myo Arm brand controller
    //myo myoUtils;

    // Initialization of INPUT sensors
    void initIO();
    
    // Reset INPUT/OUTPUT elements
    void resetIO();

	// Identifies the state selected by user from input elements feedback
    // An interpretation and treatment of readed data from sensors will be  
	// needed to perform the required transition to get the selected state 
  	// without  ambiguity
    // returns: Transition value
    void executeTransition();
    
    // Goes to innactive state depending on the current one
    void transitionToInactive();
	// Goes to idle state depending on the current one
    void transitionToIdle();
	// Goes to tongs state depending on the current one
    void transitionToTongs();

    // Detects thumb position from output elements feedback
    // returns: OPEN|CLOSE
	// TODO: Two solutions for fingers position
    //  - Detect where the finger is
    //  - Trust where the state says we are
    // What happens if finger position is diferent to current position?
    int getThumbPosition();

    // Detects forefinger position from output elements feedback
    // returns: OPEN|CLOSE
	// TODO: Two solutions for fingers position
    //  - Detect where the finger is
    //  - Trust where the state says we are
    // What happens if finger position is diferent to current position?
    int getForefingerPosition();

};

#endif
