#!/usr/bin/env python3

def apply(config, args):
    config['baseimg'] = 'expected/build/drmario64_uncompressed.z64'
    config['myimg'] = 'build/drmario64_uncompressed.z64'
    config['mapfile'] = 'build/drmario64.map'
    config['source_directories'] = ['./src','./include']
    config['objdump_flags'] = ['-Mreg-names=32']
    # config['objdump_flags'].append("-Mno-aliases")
    config['makeflags'] = ['KEEP_MDEBUG=1', "WERROR=0"]
