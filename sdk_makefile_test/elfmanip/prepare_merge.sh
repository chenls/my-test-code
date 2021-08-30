#!/bin/bash -e

fpath=$1
if [ -z "$fpath" ]; then
    echo "usage: $0 <elf path>"
    exit -1
fi

fpath=$(readlink -f $fpath)
cd $(dirname $0)
#make -s
exec ./prepare_merge $fpath
