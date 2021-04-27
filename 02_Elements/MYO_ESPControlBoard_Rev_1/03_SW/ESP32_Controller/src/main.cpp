#include <Arduino.h>
#include <WiFi.h>

// My libraries
#include "Constants.h"
#include "InputOutputUtils.h"
#include "Test.h"

#include "myo.h"

// Conseguir verbose mode

int counter = 0;
InputOutputUtils inputOutputUtils;
Test tester;

myo myo;

bool FirstTime = 0;

void notifyCallback(BLERemoteCharacteristic* pBLERemoteCharacteristic, uint8_t* pData, size_t length, bool isNotify) {
  log_e("Battery: %i", pData[0]);
}

void notifyCallback0(BLERemoteCharacteristic* pBLERemoteCharacteristic, uint8_t* pData, size_t length, bool isNotify) {
  int k;
  for(k=0; k<=length; k++) {
    log_e("Value [%i] : %i", k, pData[k]);
  }
}

void setup() {

  log_e(">> Setup.......");

  Serial.begin(115200);


  Serial.print("ESP Board MAC Address:  ");
  Serial.println(WiFi.macAddress());

  // Start control board
  inputOutputUtils.initIO();
  if(mode == OPERATION_MODE || mode == TEST_MODE_TRANSITIONS)
	  inputOutputUtils.initIO();
  else if(mode ==  TEST_MODE_BOARD)
    tester.setIoUtils(&inputOutputUtils);

}

// LOOP LLAMADA MYO
void loop() {

	counter++;

  log_e("Into the loop %i", counter);

  log_e("Execution mode :%i", mode);


  if(mode == OPERATION_MODE || mode == TEST_MODE_TRANSITIONS)
    inputOutputUtils.executeTransition();
  else if(mode == TEST_MODE_BOARD)
    tester.testingBoard();

  // Testin MYO
  // TODO: Imposible establecer la conexión bluetooth
  // log_e("Conecting.....");
  // myo.connect();

  // log_e("Getting all data.....");
  // myo.getAllData();

  // if(!FirstTime) {
  //   myo.pClient->getService(BLEUUID("0000180f-0000-1000-8000-00805f9b34fb"))->getCharacteristic(BLEUUID("00002a19-0000-1000-8000-00805f9b34fb"))->registerForNotify(notifyCallback); 
  //   //myo.pClient->getService(BLEUUID("d5060005-a904-deb9-4748-2c7f4a124842"))->getCharacteristic(BLEUUID("d5060105-a904-deb9-4748-2c7f4a124842"))->registerForNotify(notifyCallback0); 
  //   FirstTime = 1;     
  // }  
  
  // log_e("Getting EMG notigfication.....");
  // //myo.EMGNotify();

  // log_e("Getting battery notigfication.....");
  // myo.BATTNotify();
  
  
  // if(myo.connected && myo.initDo) {

  //   myo.getFirmwareVersion();

  //   log_e("i", myo.fw_major);
  //   log_e("i", myo.fw_minor);
  //   log_e("i", myo.fw_patch);
  //   log_e("i", myo.fw_hardware_rev);
    
  //   myo.initDo = false;
  // }
  

 
  // if(myo.connected && myo.initDo) {
  //   myo.getMyoInfo();

  //   log_e("i", myo.fw_serial_number[0]);
  //   log_e("i", myo.fw_serial_number[1]);
  //   log_e("i", myo.fw_serial_number[2]);
  //   log_e("i", myo.fw_serial_number[3]);
  //   log_e("i", myo.fw_serial_number[4]);
  //   log_e("i", myo.fw_serial_number[5]);
  //   log_e("i", myo.fw_serial_number[6]);
  //   log_e("i", myo.fw_unlock_pose);
  //   log_e("i", myo.fw_active_classifier_type);
  //   log_e("i", myo.fw_active_classifier_index);
  //   log_e("i", myo.fw_has_custom_classifier);
  //   log_e("i", myo.fw_stream_indicating);
  //   log_e("i", myo.fw_sku);
  //   log_e("i", myo.fw_reserved[0]);
  //   log_e("i", myo.fw_reserved[1]);
  //   log_e("i", myo.fw_reserved[2]);
  //   log_e("i", myo.fw_reserved[3]);
  //   log_e("i", myo.fw_reserved[4]);
  //   log_e("i", myo.fw_reserved[5]);
  //   log_e("i", myo.fw_reserved[6]);
  //   log_e("i", myo.fw_reserved[7]);
    
  //   myo.initDo = false;
  // }
  
  delay(1000);
  
}

