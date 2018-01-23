/*
  ContiniousMotor.h - Library for RGB Led code.
  Created by David de Lorenzo, September 25, 2014.
  Released into the public domain.
*/

#ifndef ContiniousMotor_H
#define ContiniousMotor_H

#include "Arduino.h"

/*
	ContiniousMotor give function to manage a DC motor (Brushed motor).
	Speed can be negative, for reverse engine. (-255 .. 255)
*/

class ContiniousMotor
{
  public:
    ContiniousMotor(int pin);
    ContiniousMotor(int pin_1, int pin_2, int pin_E);
    void startEngine();
	void step(int step);
	void setSpeed(int speed);
	void changeSpeed(int speed);
	int  getSpeed();	
	void reserseSpeed();
	void stopEngine();
	void pauseEngine();
	void resumeEngine();
	void accelerate();
	void slowDown();


  private:
    int Pin, Pin1, Pin2, PinE;
    int Speed;

};

#endif