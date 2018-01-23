/*
  ContiniousMotor.cpp - Library for DC motor.
  Created by David de Lorenzo, September 25, 2014.
  Released into the public domain.
*/

#include "Arduino.h"
#include "ContiniousMotor.h"

// #define DEBUG

// ---------------------------------------------------------------------------------------
// Initialize the object
//   parameter: the pin where the motor is connected
//   use PWM (~) digital outputs  (ex: D3)
// ---------------------------------------------------------------------------------------
ContiniousMotor::ContiniousMotor(int pin)
{
	// Store the pin position
	Pin = pin;
	// Configure the pin as output
	pinMode (pin, OUTPUT); 
}

// ---------------------------------------------------------------------------------------
// Initialize the object
//   parameter: the pins where the motor controller is connected
//   1 and 2 to control the speed and direction
// 	 pin_E to enable, disable the motor
//   use PWM (~) digital outputs  (if you want to control the speed
// ---------------------------------------------------------------------------------------
ContiniousMotor::ContiniousMotor(int pin_1, int pin_2, int pin_E)
{
	// Store the pin position
	Pin1 = pin_1;
	Pin2 = pin_2;
	PinE = pin_E;
	// Configure the pin as output
	pinMode (Pin1, OUTPUT); 
	pinMode (Pin2, OUTPUT); 
	pinMode (PinE, OUTPUT); 
	digitalWrite(PinE,LOW);
}


// ---------------------------------------------------------------------------------------
// move the motor fr a given duration 
// see: http://boutique.semageek.com/fr/45-sn754410-compatible-l293d.html
// ---------------------------------------------------------------------------------------
void ContiniousMotor::step(int step) 
{ 
	if (step==0) return;

	if (step>0)
	{
		// if step >0, turn CW
		digitalWrite(Pin1,HIGH);
		digitalWrite(Pin2,LOW);
	}
	else
	{
		// if step <0, turn CCW
		digitalWrite(Pin1,LOW);
		digitalWrite(Pin2,HIGH);
	}
	delay(abs(step));
	digitalWrite(Pin1,LOW);
	digitalWrite(Pin2,LOW);
}

// ---------------------------------------------------------------------------------------
// Start the motor 
// ---------------------------------------------------------------------------------------
void ContiniousMotor::startEngine() 
{ 
	digitalWrite(PinE, HIGH);
}

// ---------------------------------------------------------------------------------------
// Stop the motor.
// This also reset the stored speed to 0.
// ---------------------------------------------------------------------------------------
void ContiniousMotor::stopEngine() 
{ 
	// Reset the speed value
	Speed = 0;
	digitalWrite(PinE,LOW);  
	digitalWrite(Pin1,LOW);
	digitalWrite(Pin2,LOW);
}

// ---------------------------------------------------------------------------------------
// Change the stored speed (not the actual speed of the motor: for this, use changeSpeed).
// ---------------------------------------------------------------------------------------
void ContiniousMotor::setSpeed(int speed)
{
	// Store the speed value
	Speed = min(255,abs(speed));
}

// ---------------------------------------------------------------------------------------
// Change the actual speed of the motor.
// ---------------------------------------------------------------------------------------
void ContiniousMotor::changeSpeed(int speed)
{
	// Store the speed value
	Speed = min(255,abs(speed));
	analogWrite(Pin, Speed);
}

// ---------------------------------------------------------------------------------------
// Reverse the speed of the motor.
// ---------------------------------------------------------------------------------------
void ContiniousMotor::reserseSpeed()
{
// not implemented
}

// ---------------------------------------------------------------------------------------
// Stop the motor. The previous speed is memorized.
// ---------------------------------------------------------------------------------------
void ContiniousMotor::pauseEngine()
{
	analogWrite(Pin, 0);
}

// ---------------------------------------------------------------------------------------
// Restart the motor, with the last memorized speed. 
// ---------------------------------------------------------------------------------------
void ContiniousMotor::resumeEngine()
{
	analogWrite(Pin, Speed);
}

// ---------------------------------------------------------------------------------------
// Accelerate the motor speed.
// ---------------------------------------------------------------------------------------
void ContiniousMotor::accelerate()
{
	Speed ++;
	Speed = min(255,abs(Speed));
	analogWrite(Pin, Speed);
}

// ---------------------------------------------------------------------------------------
// Slow down the motor speed
// ---------------------------------------------------------------------------------------
void ContiniousMotor::slowDown()
{
	Speed --;
	Speed = min(255,abs(Speed));
	analogWrite(Pin, Speed);
}

// ---------------------------------------------------------------------------------------
// Return the actual speed.
// ---------------------------------------------------------------------------------------
int ContiniousMotor::getSpeed()
{
	return (Speed);
}

