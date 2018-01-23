/* --------------------------------------------------------------------------
    Programme pour le Robot distributeur de bonbons

    Processeur Arduino

    Ecrit par David de Lorenzo. 20-septembre-2014
-------------------------------------------------------------------------- */

// #define DEBUG 0

// -------- Circuit à réaliser
/*
-- LED RGB (RGBLed library)
 Pin D3 (Digital pwm)  : La broche Rouge de la LED RGB
 Pin D5 (Digital pwm)  : La broche Vert de la LED RGB
 Pin D6 (Digital pwm)  : La broche Bleu de la LED RGB
 Pin Vin               : Alimentation de la LED RGB

-- Potentiomètre (200k) 
 Pin +5v               : Potentiometre
 Pin A0  (Analog In)   : Potentiometre value
 Pin GND               : Potentiometre

-- Speaker (newTone library)
-- https://code.google.com/p/arduino-new-tone/
 Pin D9 (Digital pwm)  : 100 ohms Resistor + HP
 Pin GND               : HP

 -- LED 
 Pin D13 (Digital out) : 220 ohm Resistor + LED(+) Anode(short leg)
 Pin GND               : LED (-) Cathode(long leg)

-- Moteur + SN754410NE 
-- http://www.lextronic.fr/P19096-circuit-pont-en-h.html
-- https://www.sparkfun.com/products/315
-- http://arduino.cc/en/Reference/Stepper
 Pin D10 (Digital out) : 1.in (motor pin A1) 
 Pin D13 (Digital out) : 2.in (motor pin A2)
 Pin D8  (Digital out) : 3.in (motor pin B1) (not used)
 Pin D12 (Digital out) : 4.in (motor pin B2) (not used)
 Pin D11 (Digital out) : Motor Enable
 Pin 5v                : +5v
 Pin GND               : Gnd
Au final, j'ai remplacé le Stepper apr un moteur DC. 
Donc, le montage reste le meme, mais on utilise seulement le moteur A.


-- Ultrasonic Sensor SR04 (NewPing library)
-- http://arduino-info.wikispaces.com/UltraSonicDistance
-- http://playground.arduino.cc/Code/NewPing
 Pin 5v                : Vcc    (cable #3)
 Pin D2 (Digital out)  : Trig   (cable #2)
 Pin D4 (digital in)   : Echo   (cable #1)
 Pin GND               : Gnd    (cable #0)
 
 -- Interruption

*/


// --- Inclusion des librairies ---
#include <LedRGB.h>
#include <musical_notes.h>
#include <NewPing.h>
//#include <Stepper.h>
#include <ContiniousMotor.h>
#include <NewTone.h>



// --- Déclaration des constantes des broches 

#define POTARD_PIN    A0   // 1 input Analog pin for the potentiometer

#define TRIGGER_PIN   2    // (1 of 2) output pin tied to trigger pin on the ultrasonic sensor.
#define LED_PIN_R     3    // (1 of 3) output Digital PWM pins for the RGB Led
#define ECHO_PIN      4    // (1 of 2) input pin tied to echo pin on the ultrasonic sensor.
#define LED_PIN_G     5    // (2 of 3) output Digital PWM pins for the RGB Led
#define LED_PIN_B     6    // (3 of 3) output Digital PWM pins for the RGB Led
#define MOTOR_PIN_B1  8    // (3 of 4) output Digital pin for the Stepper Motor (not used)
#define SPEAKER_PIN   9    // (1 of 1) output Digital pin for the speaker
#define MOTOR_PIN_A1  10   // (1 of 4) output Digital pin for the Motor
#define MOTOR_PIN_EN  11   // (1 of 5) output Digital pin for Motor Enable
#define MOTOR_PIN_B2  12   // (4 of 4) output Digital pin for the Stepper Motor (not used)
#define MOTOR_PIN_A2  13   // (2 of 4) output Digital pin for the Motor


  
// --- Déclaration des variables globales ---

  int   MaxDistance = 100; // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
  int   Saturation  = 200;
  int   Lum         = 200;
  float PotarValue  = 0;
  int   EngineSpeed = 50;    // vitesse du moteur en tours/minute (RpM)
  int   Lock        = false;
  
// --- Déclaration des objets utilisés
  LedRGB          ColoredLED(LED_PIN_R,LED_PIN_G,LED_PIN_B);
  NewPing         Sonar(TRIGGER_PIN, ECHO_PIN, MaxDistance); // NewPing: setup of pins, and maximum distance.
//  Stepper         Moteur(20,MOTOR_PIN_A1,MOTOR_PIN_A2,MOTOR_PIN_B1,MOTOR_PIN_B2);  // 18deg = 360/18 steps = 20 steps
ContiniousMotor    Moteur(MOTOR_PIN_A1,MOTOR_PIN_A2,MOTOR_PIN_EN);

// ---------------------------------------------------------------------------------------
// La fonction setup() est exécutée en premier et une seule fois, au démarrage du programme
// ---------------------------------------------------------------------------------------
void setup() 
  { 
  // ------- Initialisation fonctionnalités utilisées -------

  //start serial connection

Serial.begin(9600);
Serial.print("CPU Frequency (MHz): "); Serial.println(F_CPU/1000000);
  
  // ------- Broches en sorties numériques -------
  
  // ------- Broches en entrées numériques -------
  
  // ------- Activation si besoin du rappel au + (pullup) des broches en entrées numériques -------
  
  // ------- Initialisation des variables globales
 
  // ------- Initialisations
  // set the speed of the motor to 30 RPMs
  Serial.println("Motor OFF.");
  Moteur.setSpeed(EngineSpeed);  
  Moteur.stopEngine();       
  
  // ------- Debut du programme

  Serial.println("Note:");
  Serial.println(" La LED RGB ne peut s'allumer qu'avec une alimentation de 9v minimum.");
  Serial.println(" L'alimentation USB de 5v est insuffisante pour l'allumer.");

  Serial.println("Etalonage RGB");
  Serial.println(" 1 second Red");
  ColoredLED.setColorRGB(200,0,0);
  delay(1000);              // wait 

  Serial.println(" 1 second Green");
  ColoredLED.setColorRGB(0,200,0);
  delay(1000);              // wait 

  Serial.println(" 1 second Blue");
  ColoredLED.setColorRGB(0,0,200);
  delay(1000);              // wait 

  Serial.println(" 3 seconds Off");
  ColoredLED.switchOFF();
  delay(3000);              // wait   

  Serial.println("Switch the RGB LED ON.");
  // couleur initiale avant la lecture du potard
  ColoredLED.setColorRGB(0,200,00);    //  bleu

  Serial.println("*** Start ultrasonic scanning.");
  Sonar.ping();    // On fait un premier ping, sans mesure.
  Lock=false;
  
}   
  
  

// ---------------------------------------------------------------------------------------
// La fonction loop() s'exécute sans fin en boucle aussi longtemps que l'Arduino est sous tension
// ---------------------------------------------------------------------------------------
void loop()
{ 
  // --------------------------------------------
  // Main Loop:
  // --------------------------------------------
  unsigned int cm;             // Distance de détection courante
  unsigned int cm_maintained;  // Distance de détection precedente
  int          HueValue;       // Couleur pour la LED RGB
  
  // --------------------------------------------
  // On attend que le Sonar détecte une main.
  // --------------------------------------------
  delay(200);                              // Wait 100ms between pings (about 10 pings/sec). 29ms should be the shortest delay between pings.
  
  cm = Sonar.ping_cm();          // Send ping, get distance in cm.
  Serial.print(" Ping: "); Serial.print(cm); Serial.println("cm");

  if ( (cm<20) and (cm>6) and !Lock )
   {
  // -------------------------------------------------------
     // Une main est détectée (entre 4 et 20 cm): on livre un bonbon.
  // -------------------------------------------------------
     Lock=true;
     Serial.println("*** A hand was detected.");
     // On joue un son
     Serial.println("  Play a sound.");
     newPlay_R2D2();    // Attention synchrone: la fonction garde la main tant que dure la mélodie.
     // On livre un bonbon
     // On éteint la LED
     ColoredLED.switchOFF();
     Serial.println("  Start the motor (Light OFF).");
     Moteur.startEngine();       
     Moteur.step(3500);        // Tourne 
     delay(500);
     Moteur.step(-3500);       // Revient à la position initiale
     Moteur.stopEngine();       
     Serial.println("  Stop the motor (Lght ON).");
     ColoredLED.setColorHSL(HueValue, Saturation, Lum);
     Serial.println("  End of delivery.");
  } 


  if ( (cm>1) and (cm<6) and !Lock )
   {
  // -------------------------------------------------------
     // Une main très proche (entre 1 et 4 cm) est détectée : mode reglage si elle se maintient 1 seconde
  // -------------------------------------------------------
     Serial.println("*** Adjustment Mode.");
     delay(1000);
     cm_maintained = Sonar.ping_cm();          // Send ping, get distance in cm.
     if (cm_maintained==cm)
     {
        // La main se maintient: on fait le deblocage/reglage
        // On éteint la LED
        ColoredLED.switchOFF();
        Moteur.startEngine();       
        // Tant que la main est présente à moins de 10 cm
        while (Sonar.ping_cm() < 10)
        {
          int MotorAdjust = analogRead(POTARD_PIN);    // value 0..1023
          MotorAdjust = (int(MotorAdjust/100)-9)*100;  // value -900 .. +400
          Serial.print("  MotorAdjust: ");  Serial.println(MotorAdjust);
          Moteur.step(MotorAdjust);       
          delay(500);
        }
        Moteur.stopEngine();       
        ColoredLED.setColorHSL(HueValue, Saturation, Lum);
     }     
     Serial.println("   End of adjusment.");
     Lock=false;
   }

  // Ce lock sert à ce que le Robot ne distribue pas des bonbons en permanence:
  // il faut re-établir une distance de 40 cm avant qu'il en puisse redistribuer un.
  if ((cm>40) or (cm==0))  Lock=false; // 0 est la valeur infinie.
  

  // -------------------------------------------------------
  // On ajuste la couleur de la LED en fonction du potard
  // -------------------------------------------------------

  // Read the value from the sensor:
#ifdef DEBUG
  // If sensor is not connected, the value can be simulated here: (dents de scie)
  PotarValue+=3;
  if (PotarValue==1024) PotarValue=0; 
#else
  PotarValue = analogRead(POTARD_PIN);    // value 0..1023
#endif
  
  HueValue = PotarValue/4;     // value 0..255
  ColoredLED.setColorHSL(HueValue, Saturation, Lum);
/*
    Serial.print(" Adjust HLS command: "); 
    Serial.print(int(PotarValue)); Serial.print(": "); 
    Serial.print(HueValue);   Serial.print(", "); 
    Serial.print(Saturation); Serial.print(", "); 
    Serial.println(Lum);        
*/
  // ColoredLED.setFastColorHSL(PotarValue, Lum);
  
  
  // while(1); // stop loop

}



// ////////////////////////// FONCTIONS DE GESTION DES INTERRUPTIONS ////////////////////

   
// ////////////////////////// AUTRES FONCTIONS DU PROGRAMME ////////////////////

// ---------------------------------------------------------------
// Play R2D2 melody
// ---------------------------------------------------------------
void newPlay_R2D2()
{
          NewTone(SPEAKER_PIN,note_A7/2,100); //A 
          delay (130);
          NewTone(SPEAKER_PIN,note_G7/2,100); //G 
          delay (130);
          NewTone(SPEAKER_PIN,note_E7/2,100); //E 
          delay (130);
          NewTone(SPEAKER_PIN,note_C7/2,100); //C
          delay (130);
          NewTone(SPEAKER_PIN,note_D7/2,100); //D 
          delay (130);
          NewTone(SPEAKER_PIN,note_B7/2,100); //B 
          delay (130);
          NewTone(SPEAKER_PIN,note_F7/2,100); //F 
          delay (130);
//          NewTone(SPEAKER_PIN,note_C8/2,100); //C 
//          delay (130);
          NewTone(SPEAKER_PIN,note_A7/2,100); //A 
          delay (130);
          NewTone(SPEAKER_PIN,note_G7/2,100); //G 
          delay (130);
          NewTone(SPEAKER_PIN,note_E7/2,100); //E 
          delay (130);
          NewTone(SPEAKER_PIN,note_C7/2,100); //C
          delay (130);
          NewTone(SPEAKER_PIN,note_D7/2,100); //D 
          delay (130);
          NewTone(SPEAKER_PIN,note_B7/2,100); //B 
          delay (130);
          NewTone(SPEAKER_PIN,note_F7/2,100); //F 
          delay (130);
//          NewTone(SPEAKER_PIN,note_C8,100); //C 
          delay (200);
          noNewTone(SPEAKER_PIN);
}

    
