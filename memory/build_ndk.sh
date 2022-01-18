#!/bin/bash
set -e
clear
dir=$(dirname $(readlink -f "$0"))
cd $dir

PROJECT_PATH=$(cd "$(dirname $0)";pwd)

ndk-build -j32  V=1 \
    NDK_PROJECT_PATH=$PROJECT_PATH \
    NDK_APPLICATION_MK=$PROJECT_PATH/Application.mk \
    APP_BUILD_SCRIPT=$PROJECT_PATH/Android.mk \
    clean 

ndk-build -j32  V=1 \
    NDK_PROJECT_PATH=$PROJECT_PATH \
    NDK_APPLICATION_MK=$PROJECT_PATH/Application.mk \
    APP_BUILD_SCRIPT=$PROJECT_PATH/Android.mk

cd -
file libs/arm64-v8a/test
echo ""
adb push libs/arm64-v8a/test /data/local/tmp/test_666
adb push libs/arm64-v8a/libclang_rt.asan-aarch64-android.so /data/local/tmp/
adb push wrap.sh /data/local/tmp/
adb shell "cd /data/local/tmp/; ./wrap.sh ./test_666"
echo ret:$?