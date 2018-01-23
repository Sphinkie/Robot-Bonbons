/*
 melodyUtils.cpp
 
	Ornaments and articulations for beautiful Arduino melodies.
 
	Participation :  Apr 2013 - Dave Tucker
					 Oct 2014 - David de Lorenzo
*/

#include "MelodyUtils.h"
#include "Arduino.h"
#include "musical_notes.h"  			// notes with exact values


// --------------------------------------------------------------------------
// Initialize the Pin where the Speaker is connected.
//   Speaker is connected to GND and to a DigitalOut (with a 100 ohm resistor)
// --------------------------------------------------------------------------
MelodyUtils::MelodyUtils(int pin)
{
  speakerPin = pin;
  pinMode(pin, OUTPUT); // sets the speakerPin to be an output 

}



// ---------------------------------------------------------------
// Play a note (with direct control of the Digital signal)
//   Pas d'espace entre les notes: Passe bien sur un HP, mais pas sur un buzzer.
// ---------------------------------------------------------------
void MelodyUtils::beep (float noteFrequency, long noteDuration)
{    
  int x;
  // Convert the frequency to microseconds
  float microsecondsPerWave = 1000000/noteFrequency;
  // Calculate how many HIGH/LOW cycles there are per millisecond
  float millisecondsPerCycle = 1000/(microsecondsPerWave * 2);
  // Multiply noteDuration * number or cycles per millisecond
  float loopTime = noteDuration * millisecondsPerCycle;
  // Play the note for the calculated loopTime.
  for (x=0;x<loopTime;x++)   
          {   
              digitalWrite(speakerPin,HIGH); 
              delayMicroseconds(microsecondsPerWave); 
              digitalWrite(speakerPin,LOW); 
              delayMicroseconds(microsecondsPerWave); 
          } 
}     
     
     
// ---------------------------------------------------------------
// Play a note (with the arduino "tone" command)
// 		30% d'espace entre les notes, (30% recommanded by Arduino). 
// 		Un peu lent sur un HP, A TESTER sur un buzzer.
// ---------------------------------------------------------------
void MelodyUtils::playTone (float noteFrequency, long noteDuration)
{
    noteFrequency = noteFrequency/2;
    tone(speakerPin, noteFrequency, noteDuration);
    int pauseBetweenNotes = noteDuration * 1.25;
    delay(pauseBetweenNotes);
    noTone(speakerPin);

}


// ---------------------------------------------------------------
// Play some sample melodies
// ---------------------------------------------------------------

// ---------------------------------------------------------------
// Play the notes (Do-Re-Mi-Fa-Sol-La-Si-Do). Play each note for 500ms
// ---------------------------------------------------------------
void MelodyUtils::play_Scale() 
{    
          playTone(note_C7,500); //C
          playTone(note_D7,500); //D 
          playTone(note_E7,500); //E 
          playTone(note_F7,500); //F 
          playTone(note_G7,500); //G 
          playTone(note_A7,500); //A 
          playTone(note_B7,500); //B 
          playTone(note_C8,500); //C 
}  


// ---------------------------------------------------------------
// Play the Ariel melody
// ---------------------------------------------------------------
void MelodyUtils::play_Ariel() 
{
          playTone(note_C6,300); //C
          playTone(note_D6,300); //D
          playTone(note_Eb6,600); //D#
          delay(200);
          
          playTone(note_D6,300); //D
          playTone(note_Eb6,300); //D#
          playTone(note_F6,600); //F
          delay(200);
          
          playTone(note_C6,300); //C
          playTone(note_D6,300); //D
          playTone(note_Eb6,500); //D#
          playTone(note_D6,300); //D
          playTone(note_Eb6,300); //D#
          playTone(note_D6,300); //D
          playTone(note_Eb6,300); //D#
          playTone(note_F6,600); //F
          delay(200);
}
 


// ---------------------------------------------------------------
// Play some sample sounds
// ---------------------------------------------------------------

// ---------------------------------------------------------------
// Play R2D2 melody
// ---------------------------------------------------------------
void MelodyUtils::play_R2D2()
{
          playTone(note_A7,100); //A 
          playTone(note_G7,100); //G 
          playTone(note_E7,100); //E 
          playTone(note_C7,100); //C
          playTone(note_D7,100); //D 
          playTone(note_B7,100); //B 
          playTone(note_F7,100); //F 
          playTone(note_C8,100); //C 
          playTone(note_A7,100); //A 
          playTone(note_G7,100); //G 
          playTone(note_E7,100); //E 
          playTone(note_C7,100); //C
          playTone(note_D7,100); //D 
          playTone(note_B7,100); //B 
          playTone(note_F7,100); //F 
          playTone(note_C8,100); //C 
}

     

// ---------------------------------------------------------------
// Play R2D2 sounds
// ---------------------------------------------------------------
void MelodyUtils::playSound_R2D2()
{
          beep(note_A7,100); //A 
          beep(note_G7,100); //G 
          beep(note_E7,100); //E 
          beep(note_C7,100); //C
          beep(note_D7,100); //D 
          beep(note_B7,100); //B 
          beep(note_F7,100); //F 
          beep(note_C8,100); //C 
          beep(note_A7,100); //A 
          beep(note_G7,100); //G 
          beep(note_E7,100); //E 
          beep(note_C7,100); //C
          beep(note_D7,100); //D 
          beep(note_B7,100); //B 
          beep(note_F7,100); //F 
          beep(note_C8,100); //C 
}

// ---------------------------------------------------------------
// Play old arcade game sound
// ---------------------------------------------------------------
void MelodyUtils::playSound_CloseEncounters() 
{
          beep(note_Bb5,300); //B b
          delay(50);
          beep(note_C6,300); //C
          delay(50);
          beep(note_Ab5,300); //A b
          delay(50);
          beep(note_Ab4,300); //A b
          delay(50);
          beep(note_Eb5,500); //E b   
          delay(500);     
          
          beep(note_Bb4,300); //B b
          delay(100);
          beep(note_C5,300); //C
          delay(100);
          beep(note_Ab4,300); //A b
          delay(100);
          beep(note_Ab3,300); //A b
          delay(100);
          beep(note_Eb4,500); //E b   
          delay(500);  
          
          beep(note_Bb3,300); //B b
          delay(200);
          beep(note_C4,300); //C
          delay(200);
          beep(note_Ab3,300); //A b
          delay(500);
          beep(note_Ab2,300); //A b
          delay(550);
          beep(note_Eb3,500); //E b      
}


// ---------------------------------------------------------------
// Play the Woody Woodpeeker laught sound
// ---------------------------------------------------------------
void MelodyUtils::playSound_WoodyLaught() 
{
          beep(note_C6,200); //C
          beep(note_E6,200); //E  
          beep(note_G6,200); //G 
          beep(note_C7,200); //C 
          beep(note_C6,200); //C
          delay(50);
          beep(note_C6,200); //C
          beep(note_E6,200); //E  
          beep(note_G6,200); //G 
          beep(note_C7,200); //C 
          beep(note_C6,200); //C
          delay(50);
          beep(note_C6,50); //C
          delay(50);
          beep(note_C6,50); //C
          delay(50);
          beep(note_C6,50); //C
          delay(50);
          beep(note_C6,50); //C
          delay(50);
          beep(note_C6,50); //C
          delay(50);
          beep(note_C6,50); //C
          delay(50);
          beep(note_C6,50); //C
}
  
// ---------------------------------------------------------------
// Play a sound
// ---------------------------------------------------------------
void MelodyUtils::playSound_Squeak() 
{
	for (int i=100; i<5000; i=i*1.45) 
		{
		beep(i,60);
		}
	delay(10);
	for (int i=100; i<6000; i=i*1.5) 
		{
		beep(i,20);
		}
}

// ---------------------------------------------------------------
// Play the waka sound
// ---------------------------------------------------------------
void MelodyUtils::playsound_Waka() 
{
	for (int i=1000; i<3000; i=i*1.05) {
		beep(i,10);
	}
	delay(100);
	for (int i=2000; i>1000; i=i*.95) {
		beep(i,10);
	}
    for (int i=1000; i<3000; i=i*1.05) {
		beep(i,10);
	}
	delay(100);
	for (int i=2000; i>1000; i=i*.95) {
		beep(i,10);
	}
    for (int i=1000; i<3000; i=i*1.05) {
		beep(i,10);
	}
	delay(100);
	for (int i=2000; i>1000; i=i*.95) {
		beep(i,10);
	}
    for (int i=1000; i<3000; i=i*1.05) {
		beep(i,10);
	}
	delay(100);
	for (int i=2000; i>1000; i=i*.95) {
		beep(i,10);
	}
}

// ---------------------------------------------------------------
// Play a wisthle sound
// ---------------------------------------------------------------
void MelodyUtils::playSound_Catcall() 
{
	for (int i=1000; i<5000; i=i*1.05) {
		beep(i,10);
	}
	delay(300);
 	for (int i=1000; i<3000; i=i*1.03) {
		beep(i,10);
	}
	for (int i=3000; i>1000; i=i*.97) {
		beep(i,10);
	}
}

// ---------------------------------------------------------------
// Play a Ohhh sound
// ---------------------------------------------------------------
void MelodyUtils::playSound_Ohhh() 
{
	for (int i=1000; i<2000; i=i*1.02) {
		beep(i,10);
	}
	for (int i=2000; i>1000; i=i*.98) {
		beep(i,10);
	}
}

// ---------------------------------------------------------------
// Play a Uhoh sound
// ---------------------------------------------------------------
void MelodyUtils::playSound_Uhoh() 
{
	for (int i=1000; i<1244; i=i*1.01) {
		beep(i,30);
	}
	delay(200);
	for (int i=1244; i>1108; i=i*.99) {
		beep(i,30);
	}
}


// --------------------------------------------------------------------------
// Sound Effects
// --------------------------------------------------------------------------
    
// --------------------------------------------------------------------------
// Glissando
//    Slides up or down from note1 to note2.
//    Rate 0 is fast and can be increased to slow the effect down.
// --------------------------------------------------------------------------
void MelodyUtils::glissando(int note1, int note2, int rate) 
{
/*
  if (note1 < note2)
  {
    //Slide up
    int i = note1;
    while (i < note2)
    {
      tone(speakerPin, i);
      delay(rate);
      i++;
    }
  }
  else
  {
    //Slide down
    int i = note1;
    while (i > note2)
    {
      tone(speakerPin,i);
      delay(rate);
      i--;
    }
  }
  noTone(speakerPin);
  */
}

// --------------------------------------------------------------------------
// Tremolo = Fast repetition of a note
// 		note = the note (from pitches.h)
// 		length = duration of the effect in msec
// 		rate = number of repetitions
// --------------------------------------------------------------------------
void MelodyUtils::tremolo(int note, int length, int rate)
{
  int note_duration = length/rate;
  int pauseBetweenNotes = rate * (1 + rate/length);

  for (int i = 0; i <= rate; i++)
  {
//    tone(speakerPin, note, note_duration);
    delay(pauseBetweenNotes);
    noTone(speakerPin);
  }
}

