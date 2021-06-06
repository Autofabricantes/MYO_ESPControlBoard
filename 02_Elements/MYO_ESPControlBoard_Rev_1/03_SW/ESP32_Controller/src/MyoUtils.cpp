#include "MyoUtils.h" 

uint8_t MyoUtils::emg[16];

/********************************************************************************************************
    CONNECT/DISCONNECT
 ********************************************************************************************************/

void MyoUtils::connect(){

	log_i ("Connecting Myo Armband...");
	myo.connect();                               
	log_i ("Connected!!!!");
 
	//delay(100);
	vTaskDelay(100);

	myo.set_sleep_mode(myohw_sleep_mode_never_sleep);

	myo.set_myo_mode(myohw_emg_mode_send_emg,         // EMG mode
					 myohw_imu_mode_send_data,        // IMU mode
                     myohw_classifier_mode_enabled);  // Classifier mode


	//for (int i = 0; i < 16; i++) {
	//	MyoUtils::emg[i] = 0;
	//}

	//myo.battery_notification(TURN_ON)->registerForNotify(batteryCallback);
	//myo.imu_notification(TURN_ON)->registerForNotify(imuCallback);
	//myo.gesture_notification(TURN_ON)->registerForNotify((gestureCallback);
	myo.emg_notification(TURN_ON)->registerForNotify(emgCallback);

	// short vibration
	myo.vibration(myohw_vibration_short);

	myo.get_firmware();
	log_i("Firmware version: %d.%d.%d.%d", myo.fw_major, myo.fw_minor, myo.fw_patch, myo.fw_hardware_rev);

	log_i("Battery: %d", myo.battery);

	myo.get_info();
	log_i("Armband info: %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",
		   myo.fw_serial_number[0], myo.fw_serial_number[1], myo.fw_serial_number[2], 
		   myo.fw_serial_number[3], myo.fw_serial_number[4], myo.fw_serial_number[5], 
		   myo.fw_serial_number[6], myo.fw_unlock_pose, myo.fw_active_classifier_type, 
           myo.fw_active_classifier_index, myo.fw_has_custom_classifier, myo.fw_stream_indicating, 
		   myo.fw_sku, myo.fw_reserved[0], myo.fw_reserved[1], 
		   myo.fw_reserved[2], myo.fw_reserved[3], myo.fw_reserved[4], 
		   myo.fw_reserved[5], myo.fw_reserved[6], myo.fw_reserved[7]);

}

void MyoUtils::detectDisconnect(){

	if (!myo.connected) {
  
    log_i ("Device disconnected: reconnecting...");
    myo.connect();
    log_i("Reconnected!!!!!");
    myo.set_myo_mode(myohw_emg_mode_send_emg,               // EMG mode
                     myohw_imu_mode_send_data,              // IMU mode
                     myohw_classifier_mode_enabled);        // Classifier mode

	//myo.battery_notification(TURN_ON)->registerForNotify(batteryCallback);
	//myo.imu_notification(TURN_ON)->registerForNotify(imuCallback);
	//myo.gesture_notification(TURN_ON)->registerForNotify(gestureCallback);
	myo.emg_notification(TURN_ON)->registerForNotify(emgCallback);
  }

}

/********************************************************************************************************
    SET CALLBACKS WHEN RECEIVING DATA
 ********************************************************************************************************/

void MyoUtils::batteryCallback(BLERemoteCharacteristic* pBLERemoteCharacteristic, uint8_t* pData, size_t length, bool isNotify) {

	log_i(">> batteryCallback");

	myo.battery = pData[0];
	log_i("Battery: %d", myo.battery);
	
}

void MyoUtils::imuCallback(BLERemoteCharacteristic* pBLERemoteCharacteristic, uint8_t* pData, size_t length, bool isNotify) {

	log_d(">> imuCallback");

	log_d("IMU: \t");
	for (int i = 0; i < length; i++) {
		log_d("%d", pData[i]);
	}
}

void MyoUtils::emgCallback(BLERemoteCharacteristic* pBLERemoteCharacteristic, uint8_t* pData, size_t length, bool isNotify) {

	log_d(">> emgCallback");
	log_d("EMG: \t");

	log_e("Longitid: %d", length);

	for (int i = 0; i < length; i++) {
		MyoUtils::emg[i] = pData[i];
		log_d("%d", pData[i]);
	}	
}

void MyoUtils::gestureCallback(BLERemoteCharacteristic* pBLERemoteCharacteristic, uint8_t* pData, size_t length, bool isNotify) {
	
	// Print the gesture
	if (pData[0] == myohw_classifier_event_pose) {
	 log_d("Gesture: ");
	
    switch (pData[1]) {
		case myohw_pose_rest:
			 log_d("rest");
        break;
		case myohw_pose_fist:
			 log_d("fist");
        break;
		case myohw_pose_wave_in:
			 log_d("wave in");
        break;
		case myohw_pose_wave_out:
			 log_d("wave out");
        break;
		case myohw_pose_fingers_spread:
			 log_d("fingers spread");
        break;
		case myohw_pose_double_tap:
			 log_d("double tap");
        break;
		default:
        break;
    }
  }
}

/********************************************************************************************************
    TRANSITIONS
 ********************************************************************************************************/

int MyoUtils::getMyoTransition(){

    int transition = 0;       
       
    //log_i("EMG: [%d][%d][%d][%d][%d][%d][%d][%d][%d][%d][%d][%d][%d][%d][%d][%d]", 
    //       MyoUtils::emg[0], MyoUtils::emg[1], MyoUtils::emg[2],  MyoUtils::emg[3],  MyoUtils::emg[4],  MyoUtils::emg[5], MyoUtils::emg[6], MyoUtils::emg[7], 
	//	   MyoUtils::emg[8], MyoUtils::emg[9], MyoUtils::emg[10], MyoUtils::emg[11], MyoUtils::emg[12], MyoUtils::emg[13], MyoUtils::emg[14], MyoUtils::emg[15]);        
    
	Serial.print(MyoUtils::emg[0]);
	Serial.print(",");
	Serial.print(MyoUtils::emg[1]);
	Serial.print(",");
	Serial.print(MyoUtils::emg[2]);
	Serial.print(",");
	Serial.print(MyoUtils::emg[3]);
	Serial.print(",");
	Serial.print(MyoUtils::emg[4]);
	Serial.print(",");
	Serial.print(MyoUtils::emg[5]);
	Serial.print(",");
	Serial.print(MyoUtils::emg[6]);
	Serial.print(",");
	Serial.print(MyoUtils::emg[7]);

    return transition;

}


void MyoUtils::getMyoSerial(){

	do{

    	log_i("EMG: [%d][%d][%d][%d][%d][%d][%d][%d][%d][%d][%d][%d][%d][%d][%d][%d]", 
           MyoUtils::emg[0], MyoUtils::emg[1], MyoUtils::emg[2],  MyoUtils::emg[3],  MyoUtils::emg[4],  MyoUtils::emg[5], MyoUtils::emg[6], MyoUtils::emg[7]);      

		vTaskDelay(1000);
		//delay(1000);

	}while(true);

}


                    
