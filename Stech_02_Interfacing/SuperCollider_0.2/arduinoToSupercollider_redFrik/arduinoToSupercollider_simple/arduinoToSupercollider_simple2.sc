//--use with arduinoToSupercollider_simple.ino
//this example controls the playback speed of a soundfile

(
s.waitForBoot{
	b.free;
	b= Buffer.read(s, "/Users/tedor2/Dropbox/teaching-2017/STech/Learning Material/Learning Material 0.1/Stech_02_Interfacing/SuperCollider_0.2/arduinoToSupercollider_redFrik/arduinoToSupercollider_simple/sounds/akashi.aif");//edit
	s.sync;
	Ndef(\file).play;
	Ndef(\file, {|rate= 1| Splay.ar(PlayBuf.ar(b.numChannels, b.bufnum, rate, loop:1))});
};
)

//Ndef(\file).set(\rate, 1.5)

SerialPort.listDevices

(
var port= SerialPort("/dev/tty.usbmodem14121", 38400, crtscts: true);//edit
Ndef(\file).play;
Routine.run({
	var byte;
	inf.do{
		while({byte= port.read; byte.notNil}, {
			byte.postln;
			Ndef(\file).set(\rate, byte.linlin(0, 255, 0.25, 4));
		});
		0.01.wait;
	};
});
CmdPeriod.doOnce({port.close});
)
