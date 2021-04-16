#include <Arduino.h>
#include "WiFi.h"

#include "Constants.h"
#include "Logging.h"

#include "InputOutputUtils.h"
#include "StateMachine.h"
#include "MyoUtils.h"

int counter = 0;

StateMachine stateMachine;
InputOutputUtils inputOutputUtils;

const char* ssid = "MASMOVIL_Ry5F";
const char* password =  "Fx3up9dqPk2C";

void setup() {
  
	logger.init(LOGLEVEL, 115200);
  delay(5000);

  logger.info((char*)"---> Setup");

  // Start state machine
  stateMachine = StateMachine();
  stateMachine.start();

  // Start control board
  inputOutputUtils = InputOutputUtils();
	inputOutputUtils.initializeInputElements();
	inputOutputUtils.initializeOutputElements();

	// Wifi connection
  // TODO 4
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    logger.info((char*)"Setup --> Connecting to WiFi..");
  }
  logger.info((char*)"Setup --> Connected to the WiFi network");

  // Bluetooth initialization
  // TODO 5

}

void loop() {

  logger.info((char*)"\n---> Loop (%d)\n", counter);
	counter++;
	stateMachine.executeTransition();

}

