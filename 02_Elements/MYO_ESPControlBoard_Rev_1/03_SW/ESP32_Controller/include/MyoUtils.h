#ifndef MYO_UTILS_H
#define MYO_UTILS_H

// Myo Armbrand libraries
#include <myo.h>

class MyoUtils {
        
    public:

        // Myo BLE Armband
        armband myo;
        
        MyoUtils();
        void connect();
        void detectDisconnect();
        int getMyoTransition();
      
    private:

        void closeCondition(int* emg); 

        void batteryCallback(BLERemoteCharacteristic* pBLERemoteCharacteristic, uint8_t* pData, size_t length, bool isNotify);
        void imuCallback(BLERemoteCharacteristic* pBLERemoteCharacteristic, uint8_t* pData, size_t length, bool isNotify);
        void emgCallback(BLERemoteCharacteristic* pBLERemoteCharacteristic, uint8_t* pData, size_t length, bool isNotify);
        void gestureCallback(BLERemoteCharacteristic* pBLERemoteCharacteristic, uint8_t* pData, size_t length, bool isNotify);           

        /*
        void processBattery(int bat);                
        void ledEmg(int* emg);                
        
        void startThreadMyo();
        void joinThreadMyo(int timeout);
        void stopThreadMyo();
        
        void getEmg();
        void processEmg(int* emg);
        void processImu(int quat, int acc, int gyro);
        void processSync(int arm, int x_direction);
        */

         /*
        void resetMyo();      
        void runMyo();
        */
        
};

#endif