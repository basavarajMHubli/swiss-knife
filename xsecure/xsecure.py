#!/usr/bin/python3

'''
    File:   xsecure.py
    Desc:   Simple script to encrypt/decrypt any file for secure storage and
            sharing
    Author: Basavaraj M. Hubli
'''

import os
import errno
import argparse
from cryptography.fernet import Fernet

KEY_FILE_PATH = "./"
KEY_FILE_NAME = "x.key"
KEY_FILE      = KEY_FILE_PATH + KEY_FILE_NAME

CLR_RED   = "\x1b[31m"
CLR_GREEN = "\x1b[32m"
CLR_RST   = "\x1b[39m"

def process_args():
    ''' Function to set argument list '''
    parser = argparse.ArgumentParser(description=__doc__)
    group  = parser.add_mutually_exclusive_group (required = True)
    group.add_argument('-e', '--encrypt', action='store',
                        help='File to be encrypted')
    group.add_argument('-d', '--decrypt', action='store',
                        help='File to be decrypted')
    parser.add_argument('-g', '--generate-key-file', action='store_true',
                        help='Generate key file used for en/decryption')
    parser.add_argument('-k', '--key-file', action='store',
                        help='Key file used for en/decrypt')
    return parser.parse_args()

def load_key_file(fname):
    ''' Function to load key from file '''
    print(" --> Loading key file")

    # If fname args in None, read key data from default file
    if fname is None:
        fname = KEY_FILE

    try:
        with open(fname, 'rb') as fd:
            key = fd.read()
    except Exception as e:
        raise

    return key

def generate_key_file():
    ''' Function to generate new key and write to file '''
    print(" --> Generating key file")
    key = Fernet.generate_key()

    # Store the key into file for future use
    try:
        with open(KEY_FILE, 'wb') as fd:
            fd.write(key)
    except Exception as e:
        raise

    print(CLR_GREEN, "NOTE: Store "+KEY_FILE+" for future use, without which "
          "decryption is impossible", CLR_RST)
    return key

def encrypt_file(fname, key):
    ''' Function to encrypt file '''
    fernet = Fernet(key)

    with open(fname, 'rb') as fd:
        original = fd.read()

    # Encrypting...
    encrypted = fernet.encrypt(original)

    # Create encrypted file
    e_fname = fname+'.enc'
    with open(e_fname, 'wb') as fd:
        fd.write(encrypted)

    print(CLR_GREEN, "--> Encrypted file "+e_fname+" generated", CLR_RST)

def decrypt_file(fname, key):
    ''' Function to encrypt file '''
    with open(fname, 'rb') as fd:
        original = fd.read()

    # Decrypting... TODO: Handle exception
    fernet = Fernet(key)
    decrypted = fernet.decrypt(original)

    # Create decrypted file
    fname = fname.replace('.enc', '.dec')
    with open(fname, 'wb') as fd:
        fd.write(decrypted)

    print(CLR_GREEN, "--> Decrypted file "+fname+" generated", CLR_RST)

if __name__ == '__main__':
    ''' main() '''

    args = process_args()

    if args.key_file:
        key = load_key_file(args.key_file)
    elif args.generate_key_file:
        key = generate_key_file()
    else:
        print(CLR_RED, "--> Key file missing! Use -h for more details. Exiting")
        exit()

    if args.encrypt:
        encrypt_file(args.encrypt, key)

    if args.decrypt:
        pass
        decrypt_file(args.decrypt, key)
