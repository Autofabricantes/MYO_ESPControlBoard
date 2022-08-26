#ifndef MYO_UTILS_H
#define MYO_UTILS_H

#include "Constants.h"

// Myo Armbrand libraries
#include <myo.h>

class MyoUtils {
        
    public:

        // Myo BLE Armband
        armband myo;
		
		// EMG data storage
        static uint8_t emg[8];
		
        // Detección de estados (OPEN/CLOSE)
		int getMyoStateToGet();

        // Conexión y reconexión del brazalete a la placa
        void detectDisconnect();
        void connect();

        // Testeo de la señal mediante la salida del purto serie.
        void getMyoEMG();

		
	private:
		
        // Callbacks de señales del brazalete
        static void emgCallback(BLERemoteCharacteristic* pBLERemoteCharacteristic, uint8_t* pData, size_t length, bool isNotify);
        void batteryCallback(BLERemoteCharacteristic* pBLERemoteCharacteristic, uint8_t* pData, size_t length, bool isNotify);
        void imuCallback(BLERemoteCharacteristic* pBLERemoteCharacteristic, uint8_t* pData, size_t length, bool isNotify);        
        void gestureCallback(BLERemoteCharacteristic* pBLERemoteCharacteristic, uint8_t* pData, size_t length, bool isNotify);           
        
};

#endif