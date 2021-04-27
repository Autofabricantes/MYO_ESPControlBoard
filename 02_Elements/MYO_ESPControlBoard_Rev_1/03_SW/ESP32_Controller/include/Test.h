#ifndef TEST_H
#define TEST_H

#include <Adafruit_NeoPixel.h>
#include "Constants.h"
#include "InputOutputUtils.h"


class Test{

  private:
    Adafruit_NeoPixel ledRGB;
    bool memorySW;
    bool swActiveMomentary();
    void switchLedRGB();
    InputOutputUtils * ioUtils;

  public:
    void setIoUtils(InputOutputUtils * ioUtilsClass);
	  int  getKeyboardTransition();
    void testingBoard();

};

#endif
