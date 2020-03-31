
x-copy - Python utility
=======================
This utility compresses directories and copies into configured backup server

NOTE: Remote/Backup machine must be Linux variant (Limitation)

Installation
============
1. Copy xcopy.cfg to /etc directory

Configuration
=============
1. Configure username, ipaddr of remote machine.
2. Configure path where backup file needs to be copied

Usage
=====
    $ ./xcopy -d <list_of_dirs_separated_by_space> -p <local-path> -r

    Compresses list of directories and copies in path specified with -p
    Here, -r is optional, which if used copies backup files to remote machine.


