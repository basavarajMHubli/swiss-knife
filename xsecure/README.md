
xsecure - Simple python scrypt to secure files using cryptography module
========================================================================
This script encrypts/decrypts any file for secure storage and sharing.
Uses built-in cryptography python module

NOTE: Host machine must be Linux variant

Usage
=====
xsecure.py [-h] (-e ENCRYPT | -d DECRYPT) [-g] [-k KEY_FILE]

Encryption:
a) To generate key and encrypt file
    $ ./xsecure.py -g -e <filename_to_be_encrypted>
    This creates x.key file and <filename_to_be_encrypted.enc> encrypted file

b) To encrypt file using existing key file
    $ ./xsecure.py -e <filename_to_be_encrypted> -k <key_file>
    This creates <filename_to_be_encrypted.enc> encrypted file

Decryption:
a) To decrypt file using existing key file
    $ ./xsecure.py -d <filename_to_be_encrypted> -k <key_file>
    This creates <filename_to_be_encrypted.dec> decrypted file
