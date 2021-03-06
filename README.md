# Robot à Bonbons
   
## Description
<img src="https://user-images.githubusercontent.com/25912285/35319683-333719ce-00e1-11e8-9006-0dc11f8cd7a7.jpg" width="180"  height=240/>A funny robot who distributes candies during the children's birthdays.<img src="https://user-images.githubusercontent.com/25912285/35319669-27f1d0c2-00e1-11e8-9af5-c3ce925fcb07.jpg" width="180" height=240/>

## Installation
The sketch has to be uploaded into an Arduino board.   
9v supply is necessary for the RGB Led to light. USB 5v supply is not enough.  
Fill the tank with round shaped candies.
## Usage
Approach your hand from the detector: the robot will emit some blips (like D2R2) and a candy will roll down to the basket.  
With the rear button, you can choose different colors for the side light.  
Maintain your hand one second very close of the detector (1 to 4 cm), and the robot will enter in the ***adjustment mode***. The motor will turn slowly until it reach its correct initial position.
You can adjust the rotation speed with the rear button.
## Credits
Many thanks to the authors of the external libraries used for this project:  
* **Arduino** at www.arduino.cc
* **MelodyUtils** (from Dave's Arduino Utilities) by Dave Tucker ('Ornaments and articulations for beautiful Arduino melodies')
* **NewPing Library** by Tim Eckel to deal with ultrasonic sensors. More information at https://bitbucket.org/teckel12/arduino-new-ping/wiki/Home
* **NewTone Library** by Tim Eckel for playing sound on an Arduino. More information at https://bitbucket.org/teckel12/arduino-new-tone/wiki/Home
