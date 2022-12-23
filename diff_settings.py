#!/usr/bin/env python3

def apply(config, args):
    config['baseimg'] = 'expected/build/drmario64_uncompressed.z64'
    config['myimg'] = 'build/drmario64_uncompressed.z64'
    config['mapfile'] = 'build/drmario64_uncompressed.map'
    config['source_directories'] = ['./src','./include']
    config['objdump_flags'] = ['-M','reg-names=32', "-M", "no-aliases"]
    config['makeflags'] = ['KEEP_MDEBUG=1']
