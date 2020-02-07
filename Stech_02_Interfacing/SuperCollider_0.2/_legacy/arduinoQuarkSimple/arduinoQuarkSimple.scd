/*
K.Hofstadter - Stech2014
original code by R.Hoadley.

You have installed SuperCollider, but in this task to interface SuperCollider (SC) with Arduino (ARD) you will have to install the Arduino Quark, which is as an extension.

See page for SC plugins and extensions:
"http://supercollider.sourceforge.net/downloads/"

*/

/* Installing Arduino Quark

The Arduino Quark will be installed in your '/Library/Application Support/SuperCollider/' folder.

*/

Quarks.gui; //evaluate

/* in this window:
1, - 'Update Quark listing'. (It might asks you for some permissions, give it permission);

2, - 'Update Quarks' - You should see all quarks available;

3, - Click on 'Direcetory' to see where your quark listing was downloaded.

4, - Select Arduino (- will be +) and 'Apply'.

5, - It asks you to recompile the Class library. Go to your SuperCollider file menu, Language and click on 'Recomplile Class Libary'.

Now you should be ready to interface SC and ARD with the Arduino Quark.
*/



/* Interfacing Arduino with SC

There is a new folder called 'Extensions' in your '/Library/Application Support/SuperCollider/' folder. The quark is here with file examples i.e. code for both, SuperCollider (.scd) and the Arduino (.pde). The .pde files are for 'SimpleMessagingSytem' also called 'SMS'. Instead of SMS we will use 'Messenger' later, which is an updated version of 'SMS'.

In this task we will use the Arduino Quark with a simpler code by Richard for the Arduino, which will allow us to receive messages from the analog or digital inputs.

*/


// =====================================================================
// 01_Arduino_Quark_Simple
//
// This SC code uses a simple serialprint function in the Arduino
// environment, and receives it with the Arduino Quark in SuperCollider.
//
// The Arduino Quark is capable of sending data to the Arduino, however
// for that you would have to install the SMS library for Arduino and use
// Arduino v.023 or earlier. It does not work the recent version of
// Arduino v1.0. If you'd like to send data to the Arduino from SC, use
// Messenger instead.
// =====================================================================


//check what devices we have;
SerialPort.devices;

// this starts reading from the board
q = ArduinoSMS("/dev/tty.usbmodem1a21", 115200);

q.action = { |... msg| msg.postln };

// close port
q.close;

// =====================================================================
// Read more data
// =====================================================================
(
q = ArduinoSMS("/dev/tty.usbmodem1a21", 115200);
r = 0 ! 3;
q.action = { |... msg|
	x=[msg[0],msg[1]];
	case
	{x[0]=="a"} {r[0] = x[1];}
	{x[0]=="b"} {r[1] = x[1];}
	{x[0]=="c"} {r[2] = x[1];};

	//post a,b,c in one array;
	r.postln;

};
CmdPeriod.doOnce({q.close}); //close port;
);
