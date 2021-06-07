#ifndef MYO_OTA_H
#define MYO_OTA_H

#include "Constants.h"

// Threading
#include <pthread.h>

// OTA LIbraries
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <Update.h>


class MyoOTA {
        
	public:
	
		void startOTA();
		
	private:

		pthread_t webServerThread;
		static void * runServer(void * threadId);
    
};

#endif