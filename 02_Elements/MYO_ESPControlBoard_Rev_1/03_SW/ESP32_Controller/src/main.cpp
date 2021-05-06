#include <Arduino.h>

// My libraries
#include "Constants.h"
#include "InputOutputUtils.h"
#include "Test.h"

int counter = 0;
InputOutputUtils inputOutputUtils;
Test tester;

void setup() {

  // Start serial interface for debugging
  Serial.begin(115200);                            
  log_e(">> Setup.......");

  // Start control board
  inputOutputUtils.initIO();
  
  if(mode == OPERATION_MODE || mode == TEST_MODE_TRANSITIONS)
	  inputOutputUtils.initIO();
  else if(mode ==  TEST_MODE_BOARD)
    tester.setIoUtils(&inputOutputUtils);

}

void loop() {

  counter++;

  log_e("Into the loop %i", counter);

  log_e("Execution mode :%i", mode);

  if(mode == OPERATION_MODE || mode == TEST_MODE_TRANSITIONS)
    inputOutputUtils.executeTransition();
  else if(mode == TEST_MODE_BOARD)
    tester.testingBoard();

  vTaskDelay(1000);
  //delay(1000);
  
}