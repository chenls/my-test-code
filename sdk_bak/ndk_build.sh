clear
dir=$(dirname $(readlink -f "$0"))
cd $dir

init() {
    git submodule update --init
    cd MegBrain
    git submodule update --init third_party/midout
    cd -
    ./third-party/init_aarch64.sh
    ./fix_megbrain_complie.sh
    cd src/megdnn
    ln -sf ../../MegBrain/dnn/src/aarch64
    cd -
}

# init

mkdir -p build-arm64-v8a
# rm -rf build-arm64-v8a/*
cd build-arm64-v8a
cmake -DCMAKE_TOOLCHAIN_FILE=$ANDROID_NDK/build/cmake/android.toolchain.cmake \
    -DANDROID_ABI="arm64-v8a" \
    -DANDROID_PLATFORM=android-28 \
    ..
# time make VERBOSE=1
time make -j64
cd -

obgs=$(find build-arm64-v8a/CMakeFiles/megtee.dir/ -name "*.o")
time /data/data/android-ndk-r21b/toolchains/llvm/prebuilt/linux-x86_64/bin/aarch64-linux-android-ld -r -o build-arm64-v8a/anctee.o $obgs
ls -l build-arm64-v8a/anctee.o
cp build-arm64-v8a/anctee.o /data/chenliusheng/trustonic_sdk_500/fingerprintproject/customization/anc_ta/algorithm/lib/lib64/anctee.o
zip anctee.zip build-arm64-v8a/anctee.o

# build sdk-demo
# cp build-arm64-v8a/libmegtee.a mgb_loader/full_tee_sdk_demo/release_vendor_aarch64
# cd mgb_loader/full_tee_sdk_demo/release_vendor_aarch64
# source build_config
# cd jni
# ndk-build clean
# # ndk-build NDK_DEBUG=1 V=1
# ndk-build
# cd -
