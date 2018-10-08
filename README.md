# One Wire Slave Emulator

Back in college, there was a research project that needed a wired system where each of its parts could be moved around freely while mainting their functionalities. I proposed to use the One Wire communication protocol, as it only required 1 data wire for communications.
One wire has two type of devices: slaves and masters. Each one-wire system has one master and multiple slaves. The master can communicate to the exact slave it wants to as each slave has an unique ID number. This ability of the one wire protcol made it the perfect candidate for the research project.
However, MAXIM, the owner of the protocol, does not open source the protocol and thus there is no way to make a legit customized one-wire slave device.

NOT LEGALLY, anyway.

Being the bad engineer that I am, I took a logic analyzer and a oscilloscope and reverse engineered the protocol, which now would allow others to create one-wire slaves with custom functioanlities. 

## Notes:

It's meant to be run on a PIC24HJ128GP502. I have not tested it on other micro-controllers, but it should still work. You would need to change something with the timing though.

If you look at the code, you will see that I unfolded a lot of loops. It is because the timing is very strict and avoiding loop increase the performance by a noticeable amount. When I did this, I used the onboard oscillator with phase locked loop to increase the frequency to 40 MHz, but it's pretty finicky. To improve the performance, I would advise you using external crystals. Also, I mostly used the delay function inside lib, which did the job but is not optimal. Using a timer with interrupt would also give you a better performance.

### Prerequisites

```
MP LAB X IDE
XC16 C Compiler
PIC24HJ128GP502
```

### Connection
common ground and one shared data line. Currently, it's pin RB13. Since we need to both read and write to the data line, I configure the pin as a pull-up input whenever I need to read something and configure it as an output whenever I need to write something. These changes happen dynamically.

### What works

All in all, in terms of results, it's mostly there. It supports all of the different commands that a master can send and is right now masquerading as a DS18B20 temperature sensor. It should work with different one wire masters (I tested with a Raspberry Pi and a Feather M0). You can add codes to do stuff in the while loop inside main as the communications are handled via interrupts (I used changed notification).  

### What doesn't works:
Sometimes if the master sends too many reset requests consequently, you may have to hit the reset button for the thing to work properly
