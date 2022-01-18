set -e
clear
dir=$(dirname $(readlink -f "$0"))
cd $dir
mkdir -p build
rm -rf build/*
cd build
cmake -DCMAKE_TOOLCHAIN_FILE=$ANDROID_NDK/build/cmake/android.toolchain.cmake \
-DANDROID_PLATFORM=android-28 \
-DANDROID_ABI="arm64-v8a" \
..

bear make VERBOSE=1
cd -
ln -sf build/compile_commands.json compile_commands.json
file ./build/test
echo ""
adb push ./build/test /data/local/tmp/test_666
# adb shell /data/local/tmp/test_666
adb push libs/arm64-v8a/libclang_rt.asan-aarch64-android.so /data/local/tmp/
adb push wrap.sh /data/local/tmp/
adb shell "cd /data/local/tmp/; ./wrap.sh ./test_666"
echo ret:$?