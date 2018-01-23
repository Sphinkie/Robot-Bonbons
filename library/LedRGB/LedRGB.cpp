/*
  LedRGB.cpp - Library for RGB Led code.
  Created by David de Lorenzo, September 25, 2014.
  Released into the public domain.
*/

#include "Arduino.h"
#include "LedRGB.h"

// #define DEBUG

#define PI 3.14159265358979323846
const float PIx2   = 2*PI;
const float PIx3   = 3*PI;
const float PIsur2 = PI/2;
const float PIsur3 = PI/3;
const float PIsur6 = PI/6;



// ---------------------------------------------------------------------------------------
// Initialize LED RGB
//   parameter: the 3 pins where  the RGB cathodes of the LED are connected
//   use PWM (~) digital outputs  (ex: 3,5,6)
// ---------------------------------------------------------------------------------------
LedRGB::LedRGB(int RedLedPin, int GreenLedPin, int BlueLedPin)
{
	// Configure the 3 pins as output
	pinMode (RedLedPin,  OUTPUT); 
	pinMode (GreenLedPin,OUTPUT); 
	pinMode (BlueLedPin, OUTPUT); 
	// Store the pin position
	PinRed   = RedLedPin;
    PinGreen = GreenLedPin;
    PinBlue  = BlueLedPin; 
}

// ---------------------------------------------------------------------------------------
// Switch off the RGB LED
// Avec une LED RGB anode commune : la LED s'allume sur niveau BAS, et s'éteint sur niveau HAUT
// ---------------------------------------------------------------------------------------
void LedRGB::switchOFF() 
{ 
   analogWrite(PinRed,   255);
   analogWrite(PinGreen, 255); 
   analogWrite(PinBlue,  255); 
}

// ---------------------------------------------------------------------------------------
// allume la LED RGB , avec la couleur R,G,B demandée
//    reçoit une valeur comprise entre 0 et 255 par composante couleur
// ---------------------------------------------------------------------------------------
void LedRGB::setColorRGB(int Red, int Green, int Blue) 
{ 
   // Avec une LED RGB anode commune : la LED s'allume sur niveau BAS
   // Impulsion de la largeur voulue sur la broche:  0=0% et 255=100% haut
   analogWrite(PinRed,   255-Red);    
   analogWrite(PinGreen, 255-Green); 
   analogWrite(PinBlue,  255-Blue);  
}


// ---------------------------------------------------------------------------------------
// Light the LED with the specified color
// parameters:
//		Hue : 0..255			
//		Saturation: 0..255	As the LED cannot display grey, a low saturation is some kind of white
// 		Lightness:	0..255
// ---------------------------------------------------------------------------------------
void LedRGB::setColorHSL(int Hue, int Saturation, int Lightness)
{
	float H,S,L;
	float R,G,B;
	int   Red,Green,Blue;

	H = float(Hue) /255 *PIx2;    // 0..2xPI
	S = float(Saturation) /255; 	// 0..1
	L = float(Lightness)  /2;		// 0..127


	#ifdef DEBUG 
		Serial.print("  HSL : H=");	Serial.print(H);
	#endif
	
	R = 1 + S*(cos(H + PIsur3)); // 0..2
	G = 1 + S*(sin(H + PIsur6)); // 0..2
	B = 1 - S*(cos(H));          // 0..2
	
	Red   = int(L*R);
	Green = int(L*G);
	Blue  = int(L*B);
	
	#ifdef DEBUG 
		Serial.print("   Red="); 	Serial.print(Red);
		Serial.print(" Green="); 	Serial.print(Green);
		Serial.print(" Blue=");		Serial.print(Blue);
		Serial.println();
	#endif
		
	setColorRGB(Red, Green, Blue);
}



// ---------------------------------------------------------------------------------------
// Light the LED with the specified color.
// parameters:
//		Hue       : 0..255
// 		Luminosity: 0..255
// This function does not use the trigonometry, so the execution time is faster.
// Saturation is fixed to 100%
// ---------------------------------------------------------------------------------------
void LedRGB::setFastColorHSL(int Hue, int Lightness)
{
	float H,S,L;
	float R,G,B;
	int   Red,Green,Blue;

	H = float(Hue)*PIx2   /255;		// 0..2xPI (radians)
//	S = float(Saturation) /255;	    // 0..1
	L = float(Lightness)  /2;     	// 0..127

	#ifdef DEBUG 
		Serial.print("  fast: H=");	Serial.print(H);
	#endif
	
	R = 1 + fastCos(H + PIsur3);	// 0..2
	G = 1 + fastSin(H + PIsur6); 	// 0..2
	B = 1 - fastCos(H);     		// 0..2


	Red   = int(R*L);
	Green = int(G*L);
	Blue  = int(B*L);

	#ifdef DEBUG 
		Serial.print("   Red="); 	Serial.print(Red);
		Serial.print(" Green="); 	Serial.print(Green);
		Serial.print(" Blue=");		Serial.print(Blue);
		Serial.println();
	#endif
	setColorRGB(Red, Green, Blue);
}

// ---------------------------------------------------------------------------------------
// Fast Sinus function (value in radian: 0..2xPI)
// ---------------------------------------------------------------------------------------
float LedRGB::fastSin(float value)
{
	if (value<1)		return value;
	if (value<2)		return 1;
	if (value<4)		return PI-value;
	if (value<5)		return -1;
	if (value<PIx2+1)	return value-PIx2;
	if (value<PIx2+2)	return 1;
	if (value<PIx2+4) 	return PIx3-value;
	return -1;
}

// ---------------------------------------------------------------------------------------
// Fast Cosinus function (value in radian: 0..2xPI)
// cos(x) = sin(x+pi/2)
// ---------------------------------------------------------------------------------------
float LedRGB::fastCos(float value)
{
	return fastSin(value + PIsur2);
}
