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
    vTaskDelay(100);
  }

}

void handleMyo(void * pvParameters){

  log_i("Myo running on Core %d...", xPortGetCoreID());

  for(;;){
 
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

    vTaskDelay(1000);
  }
}

void setup() {

  // Start serial interface for debugging
  Serial.begin(115200);       

  log_i(">> Setup custom1");

  // Start OTA
  // ACTIVATE OTA
  myoOTA.startOTA();

  // Myo execution mode
  if(mode == TEST_MODE_MYO_EMG_OUTPUT || mode == TEST_MODE_MYO_STATES  || mode == OPERATION_MODE){
	    inputOutputUtils.initIO();
      inputOutputUtils.connectMyo();
  }else if(mode ==  TEST_MODE_BOARD || TEST_MODE_TRANSITIONS){
      inputOutputUtils.initIO();
  }

  if(TEST_MODE_BOARD){
      tester.setIoUtils(&inputOutputUtils);
  }

  // Handle Myo
  // ACTIVATE OTA
  xTaskCreatePinnedToCore(
                  handleWebServer, /* Task function. */
                  "Task1",         /* name of task. */
                  10000,           /* Stack size of task */
                  NULL,            /* parameter of the task */
                  1,               /* priority of the task */
                  &task1OTA,       /* Task handle to keep track of created task */
                  0);              /* pin task to core 0 */                  

  vTaskDelay(1000);
  
  xTaskCreatePinnedToCore(
                  handleMyo,   /* Task function. */
                  "Task2",     /* name of task. */
                  10000,       /* Stack size of task */
                  NULL,        /* parameter of the task */
                  2,           /* priority of the task */
                  &task2Myo,   /* Task handle to keep track of created task */
                  1);          /* pin task to core 1 */
  vTaskDelay(1000);

}

//void loop() {
//
//}
