//--use with supercolliderArduino_sendAndReceive.ino
//supercollider code for reading 6 analog sensors and sending out to 6 pwm channels

SerialPort.listDevices;	//run this and see post window for name of serial device


//--gui code for sending 6 pwm
(
var name= "/dev/tty.usbmodem14121";	//edit to match your serial device
var port= SerialPort(name, 38400, crtscts: true);
var pwm= [10, 0, 0, 0, 0, 0, 0, 11];
var win= Window("pwm", Rect(99, 99, 260, 200), false);
Slider(win, Rect(10, 10, 30, 170)).action_{|view| pwm.put(1, (view.value*255).asInteger); port.putAll(pwm.postln)};
Slider(win, Rect(50, 10, 30, 170)).action_{|view| pwm.put(2, (view.value*255).asInteger); port.putAll(pwm.postln)};
Slider(win, Rect(90, 10, 30, 170)).action_{|view| pwm.put(3, (view.value*255).asInteger); port.putAll(pwm.postln)};
Slider(win, Rect(130, 10, 30, 170)).action_{|view| pwm.put(4, (view.value*255).asInteger); port.putAll(pwm.postln)};
Slider(win, Rect(170, 10, 30, 170)).action_{|view| pwm.put(5, (view.value*255).asInteger); port.putAll(pwm.postln)};
Slider(win, Rect(210, 10, 30, 170)).action_{|view| pwm.put(6, (view.value*255).asInteger); port.putAll(pwm.postln)};
win.front;
CmdPeriod.doOnce({port.putAll([10, 0, 0, 0, 0, 0, 0, 11]); port.close; win.close});
//press cmd+. to stop and close window and serial port

s.waitForBoot{
	var byte, num= 6, index= 0, data= Array.newClear(num);
	Ndef(\arduino, {|data= #[0, 0, 0, 0, 0, 0]| Splay.ar(SinOsc.ar(data.lag(0.02)+500, 0, 0.4))}).play; //temp sound
	Routine.run({
		inf.do{
			while({byte= port.read; byte.notNil}, {
				//byte.postln;	//debug
				if(index==0 and:{byte==20}, {//check if first byte is 20
					index= 1;
					}, {
						if(index>=1 and:{index<(num+1)}, {//ok, now start collecting bytes
							data[index-1]= byte;
							index= index+1;
							}, {
								if(index==(num+1) and:{byte==21}, {//until last data byte
									data.postln;	//debug
									Ndef(\arduino).setn(\data, data);
									index= 0;//done. reset index to prepare for new message
									}, {
										//something broke or beginning - restart
										"restart".postln;	//debug
										index= 0;
								});
						});
				});
			});
		};
	});
};

)
