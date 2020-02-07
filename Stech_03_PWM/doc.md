# PWM

Learning Material for Sensor Technology.    

<!---
TODO
* check all code;
* make video demonstrations;
-->
	
## AnalogWrite_PWM

Basic examples which use PWM on digital pins:


* example_01 pcm_01

Source: http://playground.arduino.cc/Code/PCMAudio


* example_02 auduino_v5

You’ll need 5 potentiometers and a little spearker/piezo/jack connection to amplifier. On a speaker you'll hear more difference when changing the sound than on the piezo disk. Remember the digital pins can only provide 40mA – so don't try to connect a big speaker unless you amplified the signal. 

Source: https://code.google.com/p/tinkerit/downloads/list

* example_03 polysynth

Use the code and experiment with the sounds. You’ll need 4 potentiometers and a speaker/piezo/jack to amplifier.

You connect the pots in the usual way, they go into the analogue pins. Get the sounds signal out of digital pins 2-3-4-5 and forge them into one. Use a resistor. The website suggests a 100K resistor if you connect it to a jack/amplify it. 

Source: http://little-scale.blogspot.co.uk/2008/02/simple-polyphonic-synth-with-just.html
	
* example_04 arduinoise

Use 6 potentiometers (or sensors) with the 6 analogue input pins. 
Connect a speaker/jack (with resistors) to digital pin 9. 

Source: http://www.blackkat.org/Arduinoise/Arduinoise.html

Experiment with these too:

http://playground.arduino.cc/Main/Freqout

