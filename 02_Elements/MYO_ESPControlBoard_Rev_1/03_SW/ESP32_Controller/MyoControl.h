#ifndef MyoControl_h
#define MyoControl_h

#include <Arduino.h>
#include "Constants.h"

class MyoControl {
	
    public:
	    MyoControl();
        MyoControl(int aControlId);
        void sampling(unsigned long sampleTime);
        void calibration();
        bool activation();
    private:
        void blinkLED(uint8_t ledPin, unsigned int repeat, unsigned int blinkTime);
        void meanCalc(unsigned int meanSamples);
        double movAv();
        void mvcCalc(unsigned int mvcSamples);
		int multiplexorRead();
        //uint8_t _emg_pin;
		int controlId;
        volatile unsigned int emg;
        double emgMean, emgMvc;
        bool sampleOk, isActive;
        unsigned long prevTime = 0;
};

#endif
