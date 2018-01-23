/* 
 melodyUtils.h 
 
 Ornaments and articulations for beautiful Arduino melodies.
 
 created 21 Apr 2013
 by Dave Tucker
*/

#ifndef MELODY_UTILS_H
#define MELODY_UTILS_H

#include "Arduino.h"

class MelodyUtils
{
public:
	MelodyUtils(int pin);
	
	void beep (float noteFrequency, long noteDuration);
	void playTone (float noteFrequency, long noteDuration);
	// ---------------------------------------------------------------
	// Play some sample melodies
	// ---------------------------------------------------------------
	void play_Scale() ;
	void play_Ariel(); 
	void play_R2D2();
	// ---------------------------------------------------------------
	// Play some sample sounds
	// ---------------------------------------------------------------
	void playSound_R2D2();
	void playSound_CloseEncounters();
	void playSound_WoodyLaught();
	void playSound_Squeak();
	void playsound_Waka();
	void playSound_Catcall();
	void playSound_Ohhh();
	void playSound_Uhoh();
	// --------------------------------------------------------------------------
	// Sound Effects
	// --------------------------------------------------------------------------
	void glissando(int note1, int note2, int rate); 
	void tremolo(int note, int length, int rate);

private:
	int speakerPin;
};
#endif