/* 
Ce programme teste l'affichage des couleurs
sur une LED RVB à anode commune (+ commun)
*/


// -------- Circuit à réaliser ---------

// Broche 3 : La broche Rouge de la LED RGB
// Broche 5 : La broche Vert de la LED RGB
// Broche 6 : La broche Bleu de la LED RGB


// --- Inclusion des librairies ---
#include <LedRGB.h>




// --- Déclaration des variables globales ---

  LedRGB ColoredLED(3,5,6);
  
  int Saturation = 250;
  int Lum = 250  ;
  int Pot = 0;


// ---------------------------------------------------------------------------------------
// La fonction setup() est exécutée en premier et 1 seule fois, au démarrage du programme
// ---------------------------------------------------------------------------------------

void setup() 
  { 
  //start serial connection
  Serial.begin(9600);
 
  // Test simple colors 
  Serial.println("1 second Red");
  ColoredLED.setColorRGB(200,0,0);
  delay(1000);              // wait 

  Serial.println("1 second Green");
  ColoredLED.setColorRGB(0,200,0);
  delay(1000);              // wait 

  Serial.println("1 second Blue");
  ColoredLED.setColorRGB(0,0,200);
  delay(1000);              // wait 

  Serial.println("3 second off");
  ColoredLED.switchOFF();
  delay(3000);              // wait   

  Serial.println("color circle");
} 
  
  

// ---------------------------------------------------------------------------------------
// la fonction loop() s'exécute sans fin en boucle aussi longtemps que l'Arduino est sous tension
// ---------------------------------------------------------------------------------------
void loop()
{ 
  Pot++;
  if (Pot>255) {Pot=0;      ColoredLED.switchOFF();  delay(10000);   }           // wait 10 sec

  Serial.print(Pot);
  Serial.println("   ");
  ColoredLED.setColorHSL(Pot, 250, 150);

  delay(100);              // wait 

  // while(1); // stop loop
}



