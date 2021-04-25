#include <Arduino.h>

// OTA Libraries
//#include <ESPAsyncWebServer.h>
//#include <AsyncElegantOTA.h>

// BLE Libraries
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

// My libraries
//#include "include/Constants.h"
//#include "../include/Logging.h"
//#include "../include/InputOutputUtils.h"
//#include "../include/StateMachine.h"

int counter = 0;

//StateMachine stateMachine;
//InputOutputUtils inputOutputUtils;

//AsyncWebServer server(80);

// STATUS: Se puede cargar nuevo software en la ESP32 de manera remota (https://randomnerdtutorials.com/esp32-ota-over-the-air-arduino/)
//          * 192.168.1.157/update
 //         * Seleccionamos firmware.
 //         * Se sube el nuevo .bin generado.
 //
 //         * Ver trazas de ejecución desde el mismo equipo (https://www.megunolink.com/articles/wireless/talk-esp32-over-wifi/)
 //         * Solucionar el problema del espacio. Ahora mismo no se puede cargar el webserver en la ESP32.
 //           https://community.home-assistant.io/t/esp32cam-ble-error-the-program-size-is-greater-than-maximum-allowed/158313
 //           https://gitter.im/espressif/arduino-esp32?at=5e2f0581f196225bd66957fd
// void activateOTA();

// TODELETE:  Parece que no es mecesario    
// STATUS:    Ahora se ve el servidor de bluetooth en el movil
//            Tendremos que crear la conexión con la Myo Armband
//            https://randomnerdtutorials.com/esp32-bluetooth-low-energy-ble-arduino-ide/
// void activateBLE();



void setup() {
    
	//logger.init(LOGLEVEL, 115200);
  delay(5000);

  log_e("Aquí estoy");

  //log_e("---> Setup");

  // OTA activation
  //activateOTA();
  
  // Bluetooth activation
  //activateBLE();

  // Start state machine
  //stateMachine.start();

  // Start control board
	//inputOutputUtils.initIO();

}

void loop() {

  //AsyncElegantOTA.loop();

  /*
  log_e("\n---> Loop (%d)", counter);
	counter++;

  if (mode == TEST_MODE_BOARD)
    inputOutputUtils.test.testingBoard();
  else
    stateMachine.executeTransition();
    */

}


// void activateOTA(){

//   WiFi.mode(WIFI_STA);
//   WiFi.begin(SSID, PASSWORD);

//   // Wait for connection
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(500);
//     log_e(".");
//   }
//   log_e("");
//   log_e("Connected to ");
//   log_e(SSID);
//   log_e("IP address: ");
//   log_e(WiFi.localIP());

//   server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
//     request->send(200, "text/plain", "Hi! I am ESP32.");
//   });

//   // Start ElegantOTA
//   AsyncElegantOTA.begin(&server);   
//   server.begin();
//   log_e("HTTP server started");

// }

// void activateBLE(){

//   log_e("Starting BLE work!");

//   BLEDevice::init("My ESP32");
//   BLEServer *pServer = BLEDevice::createServer();
//   BLEService *pService = pServer->createService(SERVICE_UUID);
//   BLECharacteristic *pCharacteristic = pService->createCharacteristic(
//                                          CHARACTERISTIC_UUID,
//                                          BLECharacteristic::PROPERTY_READ |
//                                          BLECharacteristic::PROPERTY_WRITE
//                                        );

//   pCharacteristic->setValue("Hello World says Rosa");
//   pService->start();
//   // this still is working for backward compatibility
//   // BLEAdvertising *pAdvertising = pServer->getAdvertising();  
//   BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
//   pAdvertising->addServiceUUID(SERVICE_UUID);
//   pAdvertising->setScanResponse(true);
//   // functions that help with iPhone connections issue
//   pAdvertising->setMinPreferred(0x06);  
//   pAdvertising->setMinPreferred(0x12);
//   BLEDevice::startAdvertising();
//   log_e("Characteristic defined! Now you can read it in your phone!");

// }
