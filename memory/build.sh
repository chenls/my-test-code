set -e
clear
dir=$(dirname $(readlink -f "$0"))
cd $dir
mkdir -p build
rm -rf build/*
cd build
cmake ..
bear make VERBOSE=1
cd -
ln -sf build/compile_commands.json compile_commands.json
file ./build/test
echo ""
./build/test