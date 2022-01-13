# set -e
clear
dir=$(dirname $(readlink -f "$0"))
cd $dir
mkdir -p build
rm -rf build/*
cd build
cmake -DCMAKE_TOOLCHAIN_FILE=$ANDROID_NDK/build/cmake/android.toolchain.cmake \
-DANDROID_PLATFORM=android-28 \
..

bear make VERBOSE=1
cd -
ln -sf build/compile_commands.json compile_commands.json
file ./build/test
echo ""
adb push ./build/test /data/local/tmp/test_666
adb shell /data/local/tmp/test_666
echo ret:$?