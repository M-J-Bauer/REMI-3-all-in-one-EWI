# REMI 3 'All-in-One' EWI

REMI 3 is an electronic musical instrument (EWI) designed as a DIY project for electronics hobbyists.
The instrument is fully self-contained, battery-powered with built-in sound synthesizer, audio amplifier and speaker.

A full description can be found in the doc folder. See also: http://www.mjbauer.biz/REMI_3.htm

Makers who would prefer a simpler EWI design with MIDI controller capability, but without the built-in synthesizer, speaker, etc, may be interested in the REMI mk2 "handset", which is described here: http://www.mjbauer.biz/Build_the_REMI_mk2.htm

To build the firmware, install Arduino IDE 2.0 on your computer. Follow steps on the PJRC website to install Teensy library. Under "Tools/USB" choose MIDI. Create a folder named "remi_3". Copy all source files (#.ino, #.h) to the folder. Open the main file "remi_3.ino" with Arduino IDE. Each source file will appear under its own editor tab, but the entire set of files is regarded as a single "sketch". (Arduino IDE doesn't support modular programming properly.)

_You are welcome to post comments in the Discussions section._

Note: GitHub thinks the REMI 3 source code comprises mostly C++ language (95%) because it is compiled under the Arduino IDE with many library functions written in C++. In fact, the REMI application code is composed of 100% pure C-langauge (no C++).

There is now a User Manual in the /doc folder.
