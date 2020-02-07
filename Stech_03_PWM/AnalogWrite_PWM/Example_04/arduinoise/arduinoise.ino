// ArduiNoise
// a set of sound modules for the Arduino Duemilanove
// by Jaxon BK 
// credits to Paul Badger for frequout function
// and LFOno by Beavis Audio for inspiration
// global ints

int pitchval = 1;

const int inPot1 = 0; // in and out PINS
const int inPot2 = 1; // used for all functions
const int inPot3 = 2; 
const int inPot4 = 3; 
const int inPot5 = 4;
const int inPot6 = 5; // for function select only
const int outPot = 9;

void setup ()
{

pinMode (inPot1, INPUT); // 5 1k potentiometers
pinMode (inPot2, INPUT);
pinMode (inPot3, INPUT);
pinMode (inPot4, INPUT);
pinMode (inPot5, INPUT);
pinMode (inPot6, INPUT); // 1 10k potentiometer for module selection
pinMode (outPot, OUTPUT); // to speaker cable // should be resisted (line out)

}

void loop()
{

int functNum = analogRead(inPot6) ; //
functNum = map (functNum, 0, 1023, 0, 8) ; //select 1 of 5 modules
// i am not sure why I had to map it to a range of 0 to 8? (10k pot?)
// but it seems to work fine

if (functNum == 1){
VirtualTremolo () ;
}

if (functNum == 2){
BitKicks () ;
}

if (functNum == 3){
FreqFourFrogs () ;
}

if (functNum == 4){
FreqFrogFunc () ;
}

if (functNum == 5){
Snakey () ;
}

} // end loop

// ArduiNoise sound modules

void VirtualTremolo () 
// simulated tremolo by subtracting rest time
// from total note duration

{ 

int pitch1 = analogRead(inPot1); // pitch and tempo parameters
int pitch2 = analogRead(inPot2);
int pitch3 = analogRead(inPot3);
int tempo = analogRead(inPot4) ;

int tremolo = analogRead(inPot5) ; // used to measure noteRest in freq
tremolo = map (tremolo, 0, 1023, 0, tempo) ; // tempo proportional to tremolo

freqout2 (pitch1, tempo,tremolo); // use 3 parameters in freq
freqout2 (pitch2, tempo, tremolo);
freqout2 (pitch3, tempo, tremolo);
freqout2 (pitch2, tempo, tremolo); // for meter (only 3 freqInputs)

}

void BitKicks () 
// kick drum synth and sequencer
// uses for loops to simlate fast decay and quick attack
// "tuned" in realtime by pot inputs
{

pinMode (inPot5, OUTPUT) ; // turn off inPot5 to reduce noise
int attackPitch = analogRead(inPot1); // pitch of drum
int beatTempo = analogRead(inPot2) ; // sets bpm pulse
int decay = analogRead(inPot3); // amount of decay
decay = map(decay, 0, 1023, 10, 30); // decay mapped to small interval

int release = analogRead(inPot4) ; // end of note
release = map( release, 0, 1023, 0, 10) ; // release mapped to small interval

for ( decay; decay>release; decay--) // decay ends at release
{
digitalWrite(outPot, HIGH) ;
delay(attackPitch /decay ); 
digitalWrite(outPot, LOW); 
delay(attackPitch/ decay); 
}

delay (beatTempo /4) ; // separate bpm control for sequencer
pinMode (inPot5, INPUT); //turn on inPot5 
} // end BitKicks

void FreqFourFrogs () 
// 4 step synth sequencer using "round" tones
// uses modifed freqout function
// 4 pots for frequency
// 1 pot for tempo of sequence
{

pinMode (inPot5, OUTPUT);
for (int i = 0; i<4; i++)
{
int potNumber = analogRead(i); // iterate thru inPots 1 to 4
int tempo = analogRead(inPot5) ;// rate of sequencer
freqout1 (potNumber, tempo );
}
pinMode (inPot5, INPUT);
}
void FreqFrogFunc ()
// modified FourFrogs set to given tempo
// input speed preset to generate a rhythm
// outputs tweeky loop
// uses freqout function 
{

pinMode (inPot5, OUTPUT); // turn off to reduce noise
for (int i = 0; i<4; i++) 
{
int potNumber = analogRead(i); // 4 inputs read in steps
freqout1 (potNumber, 50); // changes in tempo alternate rhythm
freqout1 (1024- potNumber, 100); // invert freq for variation
freqout1 (1024- potNumber, 50);
freqout1 (potNumber, 100);

pinMode (inPot5, INPUT); // turn pin back on
}
}

void Snakey () // linear additive synth (maybe more granular synth?)
// 4 inputs used to generate tones
// tones play in ascending and descending frequencies
// 1 input used for filter effect
// frequencies change within for loops
// tones "connect" at descent points and filter

{
int filter = analogRead(inPot5) ;
filter = map ( filter, 0, 1023, 1, 1023) ; //used to avoid /0
// for loop for tone 1
for (int i =10; i<30; i++) 
{
int tone1 = analogRead(inPot1);
if ( i > 25)
{
digitalWrite(outPot, HIGH); 
delay(tone1 /i /2) ; 
digitalWrite(outPot, LOW); 
delay(tone1 /i/2); 
}
else 
{
digitalWrite(outPot, HIGH); 
delay(tone1 / i ); 
digitalWrite(outPot, LOW); 
delay(tone1 / filter+1 /2 ); 
}
} // end for

//for loop for tone2
for (int i =40; i>10; i--)
{
int tone2 = analogRead(inPot2);
if ( i > 25 )
{
digitalWrite(outPot, HIGH) ;
delay(tone2 / i/2 ); 
digitalWrite(outPot, LOW); 
delay(tone2 / filter +1); 
}
else
{
digitalWrite(outPot, HIGH) ;
delay(tone2 /i ); 
digitalWrite(outPot, LOW); 
delay(tone2/filter+1 /i ); 
}
}// end for

//for loop for tone3 
for (int i =10; i<30; i++) 
{
int tone3 = analogRead(inPot3);
int newNUm ;
if ( i < 5)
{
digitalWrite(outPot, HIGH); 
delay(tone3 / i) ; 
digitalWrite(outPot, LOW); 
delay (tone3 / filter+1) ;
}
else 
{
digitalWrite(outPot, HIGH); 
delay(tone3/ i ); 
digitalWrite(outPot, LOW); 
delay(tone3 / filter+1 / 2); 
}
}// end for

//for loop for tone4
for (int i =40; i>10; i--)
{
int tone4 = analogRead(inPot4);
if ( i < 5 )
{
digitalWrite(outPot, HIGH) ;
delay(tone4 / i ); 
digitalWrite(outPot, LOW); 
delay(tone4 / filter +1 ); 
}
else
{
digitalWrite(outPot, HIGH) ;
delay(tone4 / i ); 
digitalWrite(outPot, LOW); 
delay(tone4 / filter+1 / 2 ); 
}
} //end for
} // end Snakey


// freq function by Paul Badger 
// mods by me
// allows playing a specific note for a given length of time


void freqout2(int freq, int t, int trem)
// used in Virtual Tremolo
// two cycles created for note and rest
// rest time read from pot, acts as tremolo
// notes are increased or decreased in duration
// while the tempo stays constant
// 3rd paramater added for trem input

// freqout function by Paul Badger 
// calculates the cycles per interval for a given frequency

{
int hperiod; //calculate 1/2 period in us
long cycleNote, cycleRest, cycleTotal, i;
int totalTime = t ;
int newTime ;
if ( totalTime > trem) 
{
newTime = totalTime - trem ;
}
else
{
newTime = totalTime ;
}

// subtract 7 us to make up for digitalWrite overhead - determined empirically
hperiod = (500000 / ((freq - 7) * pitchval)); // 50000=1000 milliseconds /2?
// calculate cycles
cycleNote = ((long)freq * (long)newTime) / 1000; // calculate cycles
cycleRest = ((long)freq * (long)trem) / 1000; // calculate cycles

// note and rest cycle lengths generated and joined
// tremolo time is subtracted from total note duration

for (i=0; i<= cycleNote; i++)
{ // play note
digitalWrite(outPot, HIGH);
delayMicroseconds(hperiod );
digitalWrite(outPot, LOW);
delayMicroseconds(hperiod - 1 );
// - 1 to make up for fractional microsecond in digitaWrite overhead
}

for (i=0; i<= cycleRest; i++)
{ // play rest
digitalWrite(outPot, LOW);
delayMicroseconds(hperiod );
digitalWrite(outPot, LOW);
delayMicroseconds(hperiod - 1 );
// - 1 to make up for fractional microsecond in digitaWrite overhead
}

}

 

void freqout1(int freq, int t)
// used with Frog sequencers
// digitalWrites alternate in frequency
// effect used to "round" the sound
// freqout function by Paul Badger 
// calculates the cycles per interval for a given frequency
// ny computing the period
// from frequency clock cycle, and tempo

{
int hperiod; //calculate 1/2 period in us
long cycles, i;

// subtract 7 us to make up for digitalWrite overhead - determined empirically
hperiod = (500000 / ((freq - 7) * pitchval));

// calculate cycles
cycles = ((long)freq * (long)t) / 1000; // calculate cycles

for (i=0; i<= cycles; i++)
{ // play note for t ms
digitalWrite(outPot, HIGH);
delayMicroseconds(hperiod );
digitalWrite(outPot, LOW);
delayMicroseconds(hperiod );
//2nd set added for effect
digitalWrite(outPot, HIGH);
delayMicroseconds(hperiod/i );
digitalWrite(outPot, LOW);
delayMicroseconds(hperiod/i - 1 );
// - 1 to make up for fractional microsecond in digitaWrite overhead

}

} // end freqout1
