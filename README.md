# Robot à Bonbons
---
## Description
A small robot used for the children birthdays, to distribute candies.
## Installation
The sketch has to be uploaded into an Arduino board.  
9v supply is necessary for the RGB Led to light. USB 5v supply is not enough.  
Fill the tank with round shaped candies.
## Usage
Approach your hand from the detector: the robot will emit some blips (like D2R2) and a candy will roll down to the basket.  
With the rear button button, you can choose different colors for the side light.
Maintain your hand one seconds very close of the detector (1 to 4 cm), and the robot will enter in the ***adjustment mode***. The motor will turn slowly until it reach its correct initial position.
You can adjust the rotation speed with the rear button.
## Credits
Many thanks to the authors of the libraries use for this project:  
* **Arduino** at www.arduino.cc
* **MelodyUtils** (from Dave's Arduino Utilities) by Dave Tucker (Ornaments and articulations for beautiful Arduino melodies)
* **NewPing Library** by Tim Eckel
* **NewTone Library** by Tim Eckel
