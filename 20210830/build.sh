clear
dir=$(dirname $(readlink -f "$0"))
cd $dir
mkdir -p build-arm64-v8a
rm -rf build-arm64-v8a/*
cd build-arm64-v8a
cmake -DCMAKE_TOOLCHAIN_FILE=$ANDROID_NDK/build/cmake/android.toolchain.cmake \
-DANDROID_ABI="x86_64" \
-DANDROID_PLATFORM=android-28 \
..
bear make VERBOSE=1
cd -
file ./build-arm64-v8a/test
echo ""
./build-arm64-v8a/test