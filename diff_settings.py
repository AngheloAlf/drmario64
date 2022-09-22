#!/usr/bin/env python3

def apply(config, args):
    config['baseimg'] = 'baserom.z64'
    config['myimg'] = 'build/drmario64.z64'
    config['mapfile'] = 'build/drmario64.map'
    config['source_directories'] = ['./src','./include']
    config['objdump_flags'] = ['-M','reg-names=32']
    config['makeflags'] = ['KEEP_MDEBUG=1']
