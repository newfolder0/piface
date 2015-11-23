# piface
Face tracking with a Raspberry Pi and Arduino
Code in C++, requires OpenCV installed

src/      - contains source files
bin/      - directory for compiled binaries, contents ignored by git
arduino/  - arduino programs

PI notes...
User: pi
Password: nodelab1
IP: 10.0.0.123
Host: lingon.local


Build with "make <name>" from this directory to build different cpp files from
src/ (requires a C++ compiler, gcc for example)
Run with "bin/<name>"

For example, change into piface directory:
$ cd <dir/piface>

Compile main program (src/main.cpp, might have to update arduino serial port):
$ make main

Run main program:
$ bin/main

OR compile and run in one line:
$ make main && bin/main


ARDUINO:
Commands below require "platformio" package and probably "arduino" package
(I haven't checked if platformio works without arduino)

Change into SerialCSV program dir:
$ cd <piface>/arduino/SerialCSV/

Compile and upload (might have to change serial port):
$ platformio run

Monitor output from arduino (should be of format "x=... y=..."):
$ platformio serialports monitor
