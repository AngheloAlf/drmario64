#!/usr/bin/env python3

def apply(config, args):
    config['baseimg'] = 'expected/build/drmario64_uncompressed.usa.z64'
    config['myimg'] = 'build/drmario64_uncompressed.usa.z64'
    config['mapfile'] = 'build/drmario64.usa.map'
    config['source_directories'] = ['./src', './include', './asm']
    config['objdump_flags'] = ['-Mreg-names=32']
    # config['objdump_flags'].append("-Mno-aliases")
    config['makeflags'] = ['KEEP_MDEBUG=1', "WERROR=0"]
