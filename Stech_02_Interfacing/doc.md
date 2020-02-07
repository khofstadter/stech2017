# Interfacing

Vide demonstration from last year [here](https://youtu.be/McLRlrTbpoE). 

<!---
TODO
* 1) order folders logically, 01 Max, 02 SuperCollider, 03 Processing as this is how most of the code evolves;

-->


## Max
  
* simpleSerial

Here you can find a simple example to send analoge input signals (ASCII) from the Arduino to Max. Communication is only one way.

* Maxuino 

Homepage [here](http://www.maxuino.org/).


## Processing

* arduinoToProcessing 

Same simpleSerial Arduino code as in Max folder above. With the signals from Arduino, you change RGB values in a little Processing window. 

* superColliderToProcessing

Sending integers and a string (text) from SuperCollider to Processing with OSC. Needs Processing 'oscP5' external library [http://www.sojamo.de/oscP5](http://www.sojamo.de/oscP5) .

* arduinoToSuperColliderToProcessing

Send analogue signals from Arduino to SuperCollider and from there to Processing with OSC. Needs oscP5 external in Processing. 


## SuperCollider

* arduinoQuarkSimple (legacy)

This interfacing does not use any external libraries in Arduino, however, you need the have the ArduinoQuark installed for SuperCollider. Here you send analogue signals to SuperCollider and parse with the ArduinoQuark. The code is easy to understand once you have the Quark installed in SuperCollider.  


### arduinoToSupercollider_redFrik


* arduinoToSupercollider_simple

Reading only one analogue signal and map it to frequency (1) and sound rate (2).

* arduinoToSupercollider_advanced

Receiving 6 analogue signals from Arduino in SuperCollider. 


### supercolliderToArduino_sendAndReceive

Receive analogue signals from Arduino in SuperCollider and send signals from SuperCollider back to the Arduino simultaneously to its digital pins. 


All code here is from RedFrik. Source: [here](https://github.com/redFrik/udk10-Embedded_Systems/tree/master/udk131212).


