#include <myo.h>

/**********************************************************************
 * GFORCE EMG ARMBAND EXAMPLE
 * Author: Davide Asnaghi
 * Date: April 3rd 2019
 * Requirements: 
 *    - ESP32 arduino (https://github.com/espressif/arduino-esp32.git)
 *    - ESP32 Myo library (https://github.com/project-sparthan/sparthan-myo.git)
 **********************************************************************/

armband myo;                // Myo BLE Armband

int emdData[16];

/********************************************************************************************************
    SET CALLBACKS WHEN RECEIVING DATA
 ********************************************************************************************************/

void batteryCallback(BLERemoteCharacteristic* pBLERemoteCharacteristic, uint8_t* pData, size_t length, bool isNotify) {

  log_e(">> batteryCallback");

  myo.battery = pData[0];
  log_e("Battery: %d", myo.battery);
}

void imuCallback(BLERemoteCharacteristic* pBLERemoteCharacteristic, uint8_t* pData, size_t length, bool isNotify) {

  log_e(">> imuCallback");

  log_e("IMU: \t");
  for (int i = 0; i < length; i++) {
    log_e("%d", pData[i]);
  }
  log_e("%d", millis());
}

void emgCallback(BLERemoteCharacteristic* pBLERemoteCharacteristic, uint8_t* pData, size_t length, bool isNotify) {

  //log_e(">> emgCallback");
  //log_e("EMG: \t");

  for (int i = 0; i < length; i++) {
    emdData[i] = pData[i];
    //log_e("%d", pData[i]);
  }
  //log_e("%d", millis());
}

void gestureCallback(BLERemoteCharacteristic* pBLERemoteCharacteristic, uint8_t* pData, size_t length, bool isNotify) {
  // Print the gesture
  if (pData[0] == myohw_classifier_event_pose) {
    log_e ("Gesture: ");
    switch (pData[1]) {
      case myohw_pose_rest:
        log_e ("rest");
        break;
      case myohw_pose_fist:
        log_e ("fist");
        break;
      case myohw_pose_wave_in:
        log_e ("wave in");
        break;
      case myohw_pose_wave_out:
        log_e ("wave out");
        break;
      case myohw_pose_fingers_spread:
       log_e ("fingers spread");
        break;
      case myohw_pose_double_tap:
        log_e ("double tap");
        break;
      default:
        break;
    }
  }
}

/********************************************************************************************************
    ARDUINO SKETCH
 ********************************************************************************************************/

void setup()
{
  Serial.begin(115200);                             // Start serial interface for debugging
  
  log_e ("Connecting...");
  myo.connect();                                    // Connect to the myo
  log_e ("Connected!!!!");
 
  //delay(100);
  vTaskDelay(100);

  myo.set_sleep_mode(myohw_sleep_mode_never_sleep);

  myo.set_myo_mode(myohw_emg_mode_send_emg,         // EMG mode
                   myohw_imu_mode_send_data,        // IMU mode
                   myohw_classifier_event_pose);    // Classifier mode

  //myo.battery_notification(TURN_ON)->registerForNotify(batteryCallback);
  myo.emg_notification(TURN_ON)->registerForNotify(emgCallback);
  //myo.imu_notification(TURN_ON)->registerForNotify(imuCallback);
  myo.gesture_notification(TURN_ON)->registerForNotify(gestureCallback);


  // short vibration
  myo.vibration(myohw_vibration_short);

  myo.get_firmware();
  log_e("Firmware version: %d.%d.%d.%d", myo.fw_major, myo.fw_minor, myo.fw_patch, myo.fw_hardware_rev);

  log_e("Battery: %d", myo.battery);

  myo.get_info();
  log_e("Armband info: %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",
        myo.fw_serial_number[0], myo.fw_serial_number[1], myo.fw_serial_number[2], 
        myo.fw_serial_number[3], myo.fw_serial_number[4], myo.fw_serial_number[5], 
        myo.fw_serial_number[6], myo.fw_unlock_pose, myo.fw_active_classifier_type, 
        myo.fw_active_classifier_index, myo.fw_has_custom_classifier, myo.fw_stream_indicating, 
        myo.fw_sku, myo.fw_reserved[0], myo.fw_reserved[1], 
        myo.fw_reserved[2], myo.fw_reserved[3], myo.fw_reserved[4], 
        myo.fw_reserved[5], myo.fw_reserved[6], myo.fw_reserved[7]);

}

void loop()
{  

  log_e("EMG sample..................................................");

  for (int i = 0; i < 16; i++) {
     log_e("%d", emdData[i]);
  }

  // Detect disconnection
  if (!myo.connected) {
    log_e ("Device disconnected: reconnecting...");
    myo.connect();
    log_e ("Reconnected!!!!!");
    myo.set_myo_mode(myohw_emg_mode_send_emg,               // EMG mode
                     myohw_imu_mode_send_data,              // IMU mode
                     myohw_classifier_mode_enabled);        // Classifier mode

    //myo.battery_notification(TURN_ON)->registerForNotify(batteryCallback);
    myo.emg_notification(TURN_ON)->registerForNotify(emgCallback);
    //myo.imu_notification(TURN_ON)->registerForNotify(imuCallback);
    myo.gesture_notification(TURN_ON)->registerForNotify(gestureCallback);

  }
  
  vTaskDelay(1000);
  //delay (5000);

}
