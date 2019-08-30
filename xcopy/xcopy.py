#!/usr/bin/python3

'''
    File:   xcopy.py
    Desc:   Script to compress, copy dirs to specific path and/or remote server
    Author: Basavaraj M. Hubli
'''

import os
import errno
import shutil
import argparse
import datetime
import threading
import subprocess
import configparser as mcfg

bkup_dir_default = '/media/sf_Documents/backup'
conf_file = '/etc/xcopy.cfg'

CLR_RED   = "\x1b[31m"
CLR_GREEN = "\x1b[32m"
CLR_RST   = "\x1b[39m"

def process_args():
    ''' Function to set argument list '''
    parser = argparse.ArgumentParser(description=__doc__)

    parser.add_argument('-d', '--dir', nargs='*', required='True',
            help='Directories to be backed up')
    parser.add_argument('-p', '--path_dest', default=bkup_dir_default,
            help='Directory where files will be copied')
    parser.add_argument('-r', '--remote', action='store_true',
            help='File will be copied on remote machine configured in\
            xcopy.cfg')

    return parser.parse_args()

def compress_dir(wdir):
    ''' Function to compress given directory '''
    tgt_file = wdir + '-' + str(datetime.date.today()) + '.tgz'
    tar_cmd = ['tar', '-zcvf', tgt_file, wdir]

    try:
        print(CLR_GREEN,'--> Compressing...',CLR_RST)
        output = subprocess.check_output(tar_cmd)
    except subprocess.CalledProcessError as e:
        raise

    print(CLR_GREEN,'--> Compressed file {} created from {}'.format(tgt_file, wdir),CLR_RST)
    return tgt_file

def copy_file(wfile, tpath):
    ''' Function to copy file to target path '''
    try:
        print(' --> Copying...')
        shutil.copy(wfile, tpath)
    except shutil.Error as e:
        raise

    print(CLR_GREEN,'--> File {} copied to {}'.format(wfile, tpath),CLR_RST)

def remote_copy(wfiles):
    ''' Function to copy file to remote server '''

    # Check if config file exists in /etc
    if not os.path.exists(conf_file):
        print(CLR_RED,'--> Config file does not exist', CLR_RST)
        raise

    try:
        cfg = mcfg.ConfigParser(conf_file)
        cfg.read(conf_file)
    except Exception as e:
        print(CLR_RED,'--> Failed to read config file: '+str(e),CLR_RST)
        raise

    print('--> Read remote machine details from config file '+conf_file)

    username = cfg.get('scp_details', 'username')
    ipaddr   = cfg.get('scp_details', 'ipaddr')
    rpath    = cfg.get('scp_details', 'path')

    wfiles_str = ' '.join(wfiles)

    scp_cmd = ['scp', wfiles_str, username+'@'+ipaddr+':'+rpath]
    print(scp_cmd)
    try:
        print('** Executing scp command...')
        output = subprocess.check_output(scp_cmd)
    except subprocess.CalledProcessError as e:
        print('--> Failed to scp: '+str(e))
        raise

    print(CLR_GREEN,'--> File copied to remote machine = '+wfiles,CLR_RST)

if __name__ == '__main__':
    ''' main() '''

    args = process_args()

    try:
        os.mkdir(args.path_dest)
    except OSError as e:
        if e.errno != errno.EEXIST:
            print(CLR_RED,'Error creating '+args.path_dest, CLR_RST)
            raise

    total_files = []
    if type(args.dir) is list:
        for d in args.dir:
            tgt_file = compress_dir(d)
            copy_file(tgt_file, args.path_dest)
            total_files.append(tgt_file)
    else:
        tgt_file = compress_dir(args.dir)
        copy_file(tgt_file, args.path_dest)
        total_files.append(tgt_file)

    if args.remote:
        remote_copy(total_files)

    print(CLR_GREEN, '--> List of files backed up:'+str(total_files), CLR_RST)
