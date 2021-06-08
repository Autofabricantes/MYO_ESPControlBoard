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

// Tasks 
TaskHandle_t task1OTA;
TaskHandle_t task2Myo;

void handleWebServer(void * pvParameters){

  log_i("OTA Web Server running on Core %d...", xPortGetCoreID());

  for(;;){
    myoOTA.handleClient();
    delay(1000);
  }

}


void handleMyo(void * pvParameters){

  log_i("Myo running on Core %d...", xPortGetCoreID());

  for(;;){
 
    counter++;
  
    log_i("Into the loop %i", counter);
    log_i("Execution mode :%i", mode);
     
    inputOutputUtils.myoUtils.detectDisconnect();
    if(mode == OPERATION_MODE || mode == TEST_MODE_TRANSITIONS)
      inputOutputUtils.executeTransition();
    else if(mode == TEST_MODE_MYO)
      inputOutputUtils.myoUtils.getMyoTransition();
    else if(mode == TEST_MODE_BOARD)
      tester.testingBoard();
  }
}

void setup() {

  // Start serial interface for debugging
  Serial.begin(115200);       

  log_i(">> Setup updated.......");

  // Start OTA
  myoOTA.startOTA();

  // Myo execution mode
  if(mode == OPERATION_MODE || mode == TEST_MODE_TRANSITIONS  || mode == TEST_MODE_MYO){
	    inputOutputUtils.initIO();
  }else if(mode ==  TEST_MODE_BOARD){
      inputOutputUtils.initIO();
      tester.setIoUtils(&inputOutputUtils);
  }

  // Handle Myo
  xTaskCreatePinnedToCore(
                    handleWebServer, /* Task function. */
                    "Task1",         /* name of task. */
                    10000,           /* Stack size of task */
                    NULL,            /* parameter of the task */
                    1,               /* priority of the task */
                    &task1OTA,       /* Task handle to keep track of created task */
                    0);              /* pin task to core 0 */                  

  delay(500); 
  
  xTaskCreatePinnedToCore(
                    handleMyo,   /* Task function. */
                    "Task2",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &task2Myo,   /* Task handle to keep track of created task */
                    1);          /* pin task to core 1 */
    delay(500); 

}




void loop() {

  // counter++;
  
  // log_i("Into the loop %i", counter);
  // log_i("Execution mode :%i", mode);

  //log_i("Running thread.");
  // myoOTA.handleClient();

  // inputOutputUtils.myoUtils.detectDisconnect();

  // if(mode == OPERATION_MODE || mode == TEST_MODE_TRANSITIONS)
  //   inputOutputUtils.executeTransition();
  // else if(mode == TEST_MODE_MYO)
  //   inputOutputUtils.myoUtils.getMyoTransition();
  // else if(mode == TEST_MODE_BOARD)
  //   tester.testingBoard();

  //vTaskDelay(1000);
  //delay(1000);
  
}
