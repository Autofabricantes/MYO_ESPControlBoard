#ifndef INPUT_OUTPUT_UTILS_H
#define INPUT_OUTPUT_UTILS_H

#include "Constants.h"
#include "MyoUtils.h"
#include "State.h"
#include "Test.h"


class InputOutputUtils{

  private:

	int potForefingerValue;
	int potThumbValue;

	// State to retrieve current finger's position
    State currentState;

    // Motor Control method
    void motorControl(int motorID, int motorDir, int motorSpeed);

	// Finger control methods
	void fingerControl(int motorId, int motorDir, int controlId);



  public:

    /*************************************************************************/
    /* INPUT METHODS                                                         */
    /*************************************************************************/

    InputOutputUtils();
    
    // Test controller
    Test test;

    // Myo Arm brand controller
    MyoUtils myoUtils;

    // Initialization of INPUT sensors
    void initIO();
    
    // Reset INPUT/OUTPUT elements
    void resetIO();

    // Handles potentiometer
	void initPotValue(int potId);
    int  getPotValue(int potId);

	// Identifies the state selected by user from input elements feedback
    // An interpretation and treatment of readed data from sensors will be  
	// needed to perform the required transition to get the selected state 
  	// without  ambiguity
    // returns: Transition value
    int getTransitionToPerform(State state);

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


    /**************************************************************************/
    /* OUTPUT METHODS                                                         */
    /**************************************************************************/


    // Moves thumb to OPEN postion if necesary
    void openThumb();

    // Moves mitten to CLOSE postion if necesary
    void closeThumb();

    // Moves forefinger to OPEN postion if necesary
    void openForefinger();

    // Moves forefinger to CLOSE postion if necesary
    void closeForefinger();


};

#endif
