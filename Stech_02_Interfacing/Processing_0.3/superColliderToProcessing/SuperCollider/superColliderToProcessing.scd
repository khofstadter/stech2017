/*
superColliderToProcessing
sending OSC messages from SuperCollider to Processing
[ needs oscP5osc library to be installed for Processing ]
http:/tedor.info/stech2014
*/


(
var slider1, slider2;
w = GUI.window.new("pSig", Rect(300, 0, 200, 100)).front;

~attention = 0;
~meditation = 0;
~presentIsland = 0;
~presentIslet = 0;
~attThreshold = 0;
~medThreshold = 0;
~message = "Na mi van?";

// create the NetAddr
// this
b = NetAddr.new("127.0.0.1", 12000);
(

~sendOsc = Task({
	inf.do({
		b.sendMsg("/test", ~attention, ~meditation, ~presentIsland, ~presentIslet, ~attThresholdVal, ~medThresholdVal, ~message);
		0.02.wait;
	});

}).play(AppClock);
);


//slider

	(
		slider1 = Slider(w, Rect(20, 30, 150, 20))
		.action = {

			p = 100*slider1.value;
			~attention = p.asInteger;
			};

		slider2 = Slider(w, Rect(20, 60, 150, 20))
		.action = {
			v = 100*slider2.value;
			~meditation = v.asInteger;
			};

		);

);


~message = "Working?";

~sendOsc.stop;


// Processing code

/*
/*
 * oscP5oscArgument by andreas schlegel
 * example shows how to parse incoming osc messages "by hand".
 * it is recommended to take a look at oscP5plug for an alternative way to parse messages.
 * oscP5 website at http://www.sojamo.de/oscP5
 *
 *
 * adapted by K.Hofstadter (tedor.info)
 * for EEG sonification/Neuro-feedback training visualization
 *
 */

import oscP5.*;
import netP5.*;
int Value0;  //attention value
int Value1;  //meditation value
int Value2;  //Present Island Value
int Value3;  //Present Islet Value
int Value4;  //Attention Threshold
int Value5;  //Meditation Threshold
String Value6 = "initial message";  //message Threshold

PFont font1;
PFont font2;

String text1 = "Island";
String text2 = "Islet";
String text3 = "Attention";
String text4 = "Meditation";


OscP5 oscP5;
NetAddress myRemoteLocation;

void setup() {
  size(600,600);
  font1 = loadFont("Didot-48.vlw");
  font2 = loadFont("CourierNewPSMT-30.vlw");
  noStroke();
  smooth();
  frameRate(25);
  /* start oscP5, listening for incoming messages at port 12000 */
  oscP5 = new OscP5(this,12000);
  myRemoteLocation = new NetAddress("127.0.0.1",12000);
  /* send an OSC message to this sketch */
//  oscP5.send("/test",new Object[] {new Integer("1"), new Float(2.0),"test string."}, myRemoteLocation);
}

void draw() {
  background(0);
  int x = 120;
  int y = 480;
  int ix = Value0*2;
  int iy = Value1*2;
  int attVal = Value0;
  int medVal = Value1;
  int islandVal = Value2;
  int isletVal = Value3;
  int attThreshold = Value4;
  int medThreshold = Value5;
  String message = Value6;



background(126);
textFont(font1);
text(text1, 22, 60);
text(text2, 22, 100);
textFont(font2);
text(islandVal, 170, 60);
text(isletVal, 170, 100);
text(text3, 22, 225);
text(text4, 320, 225);

text(message, 20, 500);
textFont(font1);


fill(255, 255);
text(attVal, 70, 290);
fill(0, 255);
text(medVal, 430, 290);

fill(0, 159);
ellipse(x, height/2, ix, ix);
fill(255, 159);
ellipse(y, height/2, iy, iy);

//noFill();
fill(255, 60);
ellipse(x, height/2, attThreshold*2, attThreshold*2);
fill(0, 60);
ellipse(y, height/2, medThreshold*2, medThreshold*2);
fill(0, 159);
}

void oscEvent(OscMessage theOscMessage) {
  /* check if theOscMessage has the address pattern we are looking for. */
  if(theOscMessage.checkAddrPattern("/test")==true) {
    /* check if the typetag is the right one. */
    if(theOscMessage.checkTypetag("iiiiiis")) {
      /* parse theOscMessage and extract the values from the osc message arguments. */
      Value0 = theOscMessage.get(0).intValue();  // get the first osc argument
      Value1 = theOscMessage.get(1).intValue(); // get the second osc argument
      Value2 = theOscMessage.get(2).intValue(); // get the third osc argument
      Value3 = theOscMessage.get(3).intValue(); // get the idea :)
      Value4 = theOscMessage.get(4).intValue();
      Value5 = theOscMessage.get(5).intValue();
      Value6 = theOscMessage.get(6).stringValue();

      return;
    }

    }
     else {
      print("wrong");
  }
}

*/