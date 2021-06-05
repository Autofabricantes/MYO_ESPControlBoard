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
  log_i(">> Setup.......");

  // Start control board
  if(mode == OPERATION_MODE || mode == TEST_MODE_TRANSITIONS  || mode == TEST_MODE_MYO){
	    inputOutputUtils.initIO();
  }else if(mode ==  TEST_MODE_BOARD){
      inputOutputUtils.initIO();
      tester.setIoUtils(&inputOutputUtils);
  }
}

void loop() {

  counter++;

  log_i("Into the loop %i", counter);
  Serial.print(counter);

  log_i("Execution mode :%i", mode);

  if(mode == OPERATION_MODE || mode == TEST_MODE_TRANSITIONS)
    inputOutputUtils.executeTransition();
  else if(mode == TEST_MODE_MYO)
    inputOutputUtils.myoUtils.getMyoTransition();
  else if(mode == TEST_MODE_BOARD)
    tester.testingBoard();

  vTaskDelay(1000);
  //delay(1000);
  
}