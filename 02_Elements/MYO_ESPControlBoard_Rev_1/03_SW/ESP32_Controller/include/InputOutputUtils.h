#ifndef INPUT_OUTPUT_UTILS_H
#define INPUT_OUTPUT_UTILS_H

#include "Constants.h"
#include "StateMachine.h"

class Test;

//#include "myo.h"

class Test;

class InputOutputUtils{

  private:

	int potForefingerValue;
	int potThumbValue;

    // Motor Control method
    void motorControl(int motorID, int motorDir, int motorSpeed);


  public:

    /*************************************************************************/
    /* INPUT METHODS                                                         */
    /*************************************************************************/

    // State to retrieve current finger's position
    StateMachine stateMachine;
    
    // Test controller
    Test  * test;

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

    // TODO: Ahora confiamos en dónde se supe sque está el dedo
    // según la máquina de estados. Deberíamos ser capaces de 
    // determinar dónde está el dedo realmente y
    // restaurar la posicion si es necesario.

    // Detects thumb position from output elements feedback
    // returns: OPEN|CLOSE
    int getThumbPosition();

    // Detects forefinger position from output elements feedback
    // returns: OPEN|CLOSE
    int getForefingerPosition();

    // Handles potentiometer
	void initPotValue(int potId);
    int  getPotValue(int potId);

	// Finger control methods
	void fingerControl(int motorId, int motorDir, int controlId);

};

#endif
