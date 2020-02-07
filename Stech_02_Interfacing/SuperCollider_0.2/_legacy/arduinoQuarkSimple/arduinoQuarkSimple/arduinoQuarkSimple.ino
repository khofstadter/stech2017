/* 
ARU - R.Hoadley
*/

int anIn0 = 0;    // select the input pin for the potentiometer
int anIn1 = 1;    // select the input pin for a sharp IR
int anIn2 = 2;    // piezo
int val0 = 0;       // variable to store the value coming from the sensor
int val1 = 0;       // variable to store the value coming from the sensor
int val2 = 0;   // variable to store the value coming from the sensor
int del = 10;

void setup() {
  Serial.begin(115200);
}

void loop() {
  val0 = analogRead(anIn0);    // read the value from the sensor
  val1 = analogRead(anIn1);    // read the value from the sensor
  val2 = analogRead(anIn2);    // read the value from the sensor
 
  delay(del);                  // stop the program for some time

  Serial.print("a ");
  Serial.print(val0);
  Serial.println();
  
  Serial.print("b ");
  Serial.print(val1);
  Serial.println();
  
  Serial.print("c ");
  Serial.print(val2);
  Serial.println();
  
}

