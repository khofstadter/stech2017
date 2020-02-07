 /*  
 *  Max2Arduino4Servo
 *  Send pin values fMax2ArduinoServorom MAX/MSP or Processing to Arduino Diecimilia Servos
 *  
 *  Max2ArduinoServo.pde
 *  ------------  
 *  This version: 23, June 2009
 *  ------------
 *  Copyleft: use as you like
 *  by MarkDavid
 *  altered by K.Hofstadter (added MegaServo library) - http://tedor.info
 *  Based on the Arduino Servo Tutorial: 
 *  http://www.arduino.cc/playground/Learning/SingleServoExample
 *  and a sketch and patch by Daniel Jolliffe & 
 *  Which was based on a sketch and patch by Thomas Ouellet Fredericks  tof.danslchamp.org
 *  
 * requires the following Libraries:
 * MegaServo: http://www.arduino.cc/playground/Code/MegaServo
 */


#include <MegaServo.h>

MegaServo servo1;
MegaServo servo2;
MegaServo servo3;
MegaServo servo4;

int x = 0;                              // a place to hold pin values
int ledpin = 13;

void setup()
{
  pinMode(1,OUTPUT);
  servo1.attach(9);
  servo2.attach(10); 
  servo3.attach(11);
  servo4.attach(12);
  
  Serial.begin(19200);
}


void loop()
{ 

if (Serial.available() > 0){         // Check serial buffer for characters
    
   char ch = Serial.read();
   static int v = 0;

    switch (ch){
      case '0'...'9':
        v = v * 10 + ch - '0';
        break;
      case 's':
        servo1.write(v);
        v = 0;
        break;
      case 't':
        servo2.write(v);
        v = 0;
        break;
      case 'u':
        servo3.write(v);
        v = 0;
        break;
      case 'q':
        servo4.write(v);
        v = 0;
        break;        
      case 'd':
        servo1.detach();
        servo2.detach();
        servo3.detach();
        servo4.detach();        
        break;
      case 'a':
        servo1.attach(9);
        servo2.attach(10);
        servo3.attach(11);
        servo4.attach(12);       
        break;
    }
 }

}


