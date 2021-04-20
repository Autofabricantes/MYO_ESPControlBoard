#ifndef TEST_H
#define TEST_H

#include <Adafruit_NeoPixel.h>
#include "Constants.h"

class Test{

  private:
    Adafruit_NeoPixel ledRGB;
    bool memorySW;
    bool swActiveMomentary();

  public:
    Test();
	  int  getKeyboardTransition();
    void testingBoard();

};

#endif
