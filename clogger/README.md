
C-Logger
========

C-Logger(Controlled logger) is C shared library which supports runtime controlled logging features

This library comes with clog_ctl utility which can be used for log configuration in runtime

Build steps
===========

1. $ make all
2. Two binaries libclog.so and clog_ctl is built in current directory
3. To clean,
    $ make clean

Demo app
========
This code shows usage of c-logging apis.
To build demo app,
   $ cd demo-app
   $ gcc -o demo demo.c -lclog -L./../ -I ../inc/


NOTE: More clear documentation will be added soon
