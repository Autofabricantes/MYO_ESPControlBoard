#include <Arduino.h>

// My libraries
#include "Constants.h"
#include "InputOutputUtils.h"
#include "Test.h"
#include "MyoOTA.h"

// Constants
int counter = 0;
InputOutputUtils inputOutputUtils;
Test tester;
MyoOTA myoOTA;

void handleWebServer(){

  log_i("OTA Web Server running (Port %d)", xPortGetCoreID());

  log_i("Time to load...");
  int counter = 60;

  while(counter > 0){
    counter--;
    log_i("Countdown %d", counter);
    myoOTA.handleClient();
    vTaskDelay(1000);
  }

}

void setup() {

  // Start serial interface for debugging
  Serial.begin(115200);       

  log_i(">> Setup .......");

  // OTA handling
  // myoOTA.startOTA();
  // handleWebServer();

  // Setting  execution mode
  if(mode == TEST_MODE_MYO_EMG_OUTPUT || mode == TEST_MODE_MYO_STATES  || mode == OPERATION_MODE){
	    inputOutputUtils.initIO();
      inputOutputUtils.connectMyo();
  }else if(mode ==  TEST_MODE_BOARD || TEST_MODE_TRANSITIONS){
      inputOutputUtils.initIO();
  }
  if(TEST_MODE_BOARD){
      tester.setIoUtils(&inputOutputUtils);
  }

  
}

void loop() {

  log_i("Myo running...", xPortGetCoreID());

  counter++;
  
  log_i("Into the loop %i", counter);
  log_i("Execution mode :%i", mode);

  if(mode == TEST_MODE_BOARD){
    tester.testingBoard();
  }else if(mode == TEST_MODE_TRANSITIONS){
    inputOutputUtils.executeTransition();
  }else{

    inputOutputUtils.myoUtils.detectDisconnect();

    if(mode == TEST_MODE_MYO_STATES){
      inputOutputUtils.myoUtils.getMyoStateToGet();
    }else if(mode == TEST_MODE_MYO_EMG_OUTPUT){
      inputOutputUtils.myoUtils.getMyoEMG();
    }else if(mode == OPERATION_MODE){
      inputOutputUtils.executeTransition();
    }      
  } 
  
  vTaskDelay(5000);

}
