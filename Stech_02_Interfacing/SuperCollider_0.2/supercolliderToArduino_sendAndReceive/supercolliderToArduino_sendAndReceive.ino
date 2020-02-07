//supercolliderArduino_sendAndReceive /f0
//  controlling 6 pwm channels and reading 6 analog inputs at the same time
//  use with sc code supercolliderArduino_sendAndReceive.scd

//--serial protocol
// pwm sc->arduino: 10 nn nn nn nn nn nn 11 (nn bytes 1-6= pwm channels 0-5)
// adc arduino->sc: 20 nn nn nn nn nn nn 21 (nn bytes 1-6= analog channels 0-5)

//--settings
byte pwmPins[]= {5, 3, 9, 6, 11, 10};
byte adcPins[]= {0, 1, 2, 3, 4, 5};  //A0-A5

//--variables
boolean changed;
byte val, cnt= 0;
byte pwmData[]= {0, 0, 0, 0, 0, 0, 0, 0};
byte adcData[]= {0, 0, 0, 0, 0, 0, 0, 0};  //for detecting change and filter out repetitions

void setup() {
  Serial.begin(38400);    //baudrate must match in sc
  for(byte i= 0; i<6; i++) {
    pinMode(pwmPins[i], OUTPUT);
    pinMode(adcPins[i], INPUT);
  }
}
void loop() {
  
  //--from sc
  while(Serial.available()) {
    val= Serial.read();
    if(cnt==0) {
      if(val==10) {  //beginning of message found
        cnt= 1;  //start counter
      }
    } else if(cnt<7) {  //between 1 and 6 means message started and that bytes should be saved
      pwmData[cnt-1]= val;  //saving incoming bytes in temporary data array
      cnt++;
    } else {
      if(val==11) {
        for(byte i= 0; i<6; i++) {
          analogWrite(pwmPins[i], pwmData[i]);  //output read message to pwm pins
        }
      } else {
        //serial read error
      }
      cnt= 0;  //reset byte counter
    }
  }
  
  //--to sc
  changed= false;
  for(byte i= 0; i<6; i++) {
    val= analogRead(adcPins[i])>>4;  //scale from 10 to 8 bits
    if(val!=adcData[i]) {
      adcData[i]= val;
      changed= true;
    }
  }
  if(changed) {  //check if any sensor changed
    Serial.write(20);
    Serial.write(adcData[0]);
    Serial.write(adcData[1]);
    Serial.write(adcData[2]);
    Serial.write(adcData[3]);
    Serial.write(adcData[4]);
    Serial.write(adcData[5]);
    Serial.write(21);
  }
  delay(10);  //wait 10 milliseconds
}

