# REMI 3 'All-in-One' EWI

REMI 3 is an electronic musical instrument (EWI) designed as a DIY project for electronics hobbyists.
The instrument is fully self-contained, battery-powered with built-in sound synthesizer, audio amplifier and speaker.

A full description can be found in the doc folder. See also: http://www.mjbauer.biz/REMI_3.htm

Makers who would prefer a simpler EWI design with MIDI controller capability, but without the built-in synthesizer, speaker, etc, may be interested in the REMI mk2 "handset", which is described here: http://www.mjbauer.biz/Build_the_REMI_mk2.htm

REMI 3 software is built under the Arduino IDE with Teensyduino support package. The Arduino development environment, while not ideal (from a professional software engineer's point of view), provides the quickest and easiest path to completion.

To build the firmware, download and install Arduino IDE and the Teensyduino library on your PC. Create a folder named "remi_3". Copy all source files (#.ino, #.h) to the folder. Open the main file "remi_3.ino" with Arduino IDE. Each file will appear under its own editor tab, but the entire set of files is regarded as a single "sketch" in Arduino.

_You are welcome to post comments in the Discussions section._

Note: GitHub thinks the REMI 3 source code comprises mostly C++ language (95%) because it is compiled under the Arduino IDE with many library functions written in C++. In fact, the REMI application code is composed of 100% pure C-langauge (no C++).
