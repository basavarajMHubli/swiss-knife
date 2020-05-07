
C-Logger
========

C-Logger(Controlled logger) is C shared library which supports runtime controllable log level

This library comes with clog_ctl utility which can be used for log configuration in runtime

Build steps
===========

1. $ make all
2. Two binaries libclog.so and clog_ctl is built in current directory
3. To clean,
    $ make clean

Demo app
========
This code shows usage of c-logger apis.
To build demo app,
   $ cd demo-app
   $ gcc -o demo demo.c -lclog -L./../ -I ../inc/

clog_ctl
========
This binary lets you control log configuration in runtime.

    Usage: ./clog_ctl -p <logger name> -t <log type> -l <log level>

    <logger name>: String identifier used in cLogInit() api
    <log type>: console/syslog/file (multiple values with , separation is supported)
    <log level>: info/error/debug
