#ifndef MYO_UTILS_H
#define MYO_UTILS_H

// Myo Armbrand libraries
#include <myo.h>

class MyoUtils {
        
    public:

        // Myo BLE Armband
        armband myo;
		
		// EMG data storage
		static uint8_t emg[16];
		
		int getMyoTransition();

        void detectDisconnect();
        void connect();

        void getMyoSerial();

		
	private:
		
		void batteryCallback(BLERemoteCharacteristic* pBLERemoteCharacteristic, uint8_t* pData, size_t length, bool isNotify);
        void imuCallback(BLERemoteCharacteristic* pBLERemoteCharacteristic, uint8_t* pData, size_t length, bool isNotify);
        static void emgCallback(BLERemoteCharacteristic* pBLERemoteCharacteristic, uint8_t* pData, size_t length, bool isNotify);
        void gestureCallback(BLERemoteCharacteristic* pBLERemoteCharacteristic, uint8_t* pData, size_t length, bool isNotify);           

        
};

#endif