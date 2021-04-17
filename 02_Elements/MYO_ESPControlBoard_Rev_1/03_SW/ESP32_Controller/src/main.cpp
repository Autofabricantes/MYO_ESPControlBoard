#include <Arduino.h>

// OTA Libraries
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>

// BLE Libraries
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

// My libraries
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
AsyncWebServer server(80);

// STATUS: Se puede cargar nuevo software en la ESP32 de manera remota (https://randomnerdtutorials.com/esp32-ota-over-the-air-arduino/)
//         * 192.168.1.157/update
 //         * Seleccionamos firmware.
 //         * Se sube el nuevo .bin generado.
 // TODO: 
 //         * Ver trazas de ejecución desde el mismo equipo (https://www.megunolink.com/articles/wireless/talk-esp32-over-wifi/)
 //         * Solucionar el problema del espacio. Ahora mismo no se puede cargar el webserver en la ESP32.
void activateOTA();

// STATUS: Ahora se ve el servidor de bluetooth en el movil,
//         tendremos que crear la conexión con la Myo Armband
// https://randomnerdtutorials.com/esp32-bluetooth-low-energy-ble-arduino-ide/
void activateBLE();

void setup() {
  
	logger.init(LOGLEVEL, 115200);
  delay(5000);

  logger.info((char*)"---> Setup\n");

  // OTA activation
  //activateOTA();
  
  // Bluetooth activation
  activateBLE();

  // Start state machine
  stateMachine = StateMachine();
  stateMachine.start();

  // Start control board
  inputOutputUtils = InputOutputUtils();
	inputOutputUtils.initializeInputElements();
	inputOutputUtils.initializeOutputElements();

}

void loop() {

  AsyncElegantOTA.loop();

  logger.info((char*)"\n---> Loop (%d)\n", counter);
	counter++;

  stateMachine.executeTransition();

}

void activateOTA(){

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", "Hi! I am ESP32.");
  });

  // Start ElegantOTA
  AsyncElegantOTA.begin(&server);   
  server.begin();
  Serial.println("HTTP server started");

}

void activateBLE(){

  Serial.println("Starting BLE work!");

  BLEDevice::init("My ESP32");
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );

  pCharacteristic->setValue("Hello World says Rosa");
  pService->start();
  // this still is working for backward compatibility
  // BLEAdvertising *pAdvertising = pServer->getAdvertising();  
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  // functions that help with iPhone connections issue
  pAdvertising->setMinPreferred(0x06);  
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
  Serial.println("Characteristic defined! Now you can read it in your phone!");

}