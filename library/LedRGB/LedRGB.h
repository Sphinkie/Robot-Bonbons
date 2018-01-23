/*
  LedRGB.h - Library for RGB Led code.
  Created by David de Lorenzo, September 25, 2014.
  Released into the public domain.
*/

#ifndef LedRGB_h
#define LedRGB_h

#include "Arduino.h"

/*
 RVB led has 4 pins :
* Pin +v  (+5V or +12v)
* Pin for Red command
* Pin for Green command
* Pin for Blue command

Each pin can receive a PWM pulse (0-255) to command the intensity of each color.
*/

class LedRGB
{
  public:
    LedRGB(int pinLedRouge, int pinLedVert, int pinLedBleu);
    void switchOFF();
	void setColorRGB(int Red, int Green, int Blue);
	void setColorHSL(int Hue, int Saturation, int Lightness);
	void setFastColorHSL(int Hue, int Lightness);
	float fastSin(float value);
	float fastCos(float value);

  private:
    int PinRed;
    int PinGreen;
    int PinBlue;
};

#endif