#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import argparse
import subprocess
import hashlib
import random

def get_syms(args):
    syms = (subprocess.check_output([args.nm, args.input])
            .decode('utf-8')
            .split('\n'))

    ret = []
    for i in syms:
        parts = i.strip().split()
        assert len(parts) <= 3
        if len(parts) <= 2:
            continue
        addr, symt, name = parts
        if symt == 'T':
            continue
        assert symt.islower(), 'bad public symbol: {}'.format(parts)
        ret.append(name)
    return ret

def gen_map(syms):
    syms = sorted(set(syms))
    md5 = hashlib.md5()
    for i in syms:
        md5.update(i.encode('utf-8'))
    rng = random.Random(md5.digest())
    rng.shuffle(syms)
    ret = []
    fmt = '_{:0%dx}' % ((len(syms).bit_length() + 3) / 4)
    fmt = fmt.format
    for i, v in enumerate(syms):
        ret.append((v, fmt(i)))
    return ret

def main():
    parser = argparse.ArgumentParser(
        description='mangle symbol names',
        formatter_class=argparse.ArgumentDefaultsHelpFormatter
    )
    parser.add_argument('input')
    parser.add_argument('output')
    parser.add_argument('--objcopy', default='objcopy',
                        help='objcopy command name')
    parser.add_argument('--nm', default='llvm-nm',
                        help='nm command name')
    args = parser.parse_args()

    syms = get_syms(args)
    sym_map = gen_map(syms)
    sym_file = args.output + '.sym'
    with open(sym_file, 'w') as fout:
        for i, j in sym_map:
            fout.write('{} {}\n'.format(i, j))
    subprocess.check_call([
        args.objcopy, '--redefine-syms={}'.format(sym_file),
        args.input, args.output])

if __name__ == '__main__':
    main()
