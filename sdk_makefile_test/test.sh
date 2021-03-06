# 说明
# https://www.diigo.com/user/chenls/b/605517016

clear
dir=$(dirname $(readlink -f "$0"))
cd $dir
export PATH=/home/chenliusheng/soft/android-ndk-r20/toolchains/llvm/prebuilt/linux-x86_64/bin:$PATH
ARCH_SUFFIX=aarch64
make OPTLEVEL=-O3 ARCH=qsee-$ARCH_SUFFIX -C ./ NEED_MANGLE=1 VENDOR_NAME=${vendor_name} PROJECT_NAME=${PROJECT_NAME} LIMIT_TIME=${LimitTime} clean
# make SHELL='sh -x'
# make -n
# make -d -p
make SHELL='sh -x' OPTLEVEL=-O3 ARCH=qsee-$ARCH_SUFFIX -C ./ NEED_MANGLE=1 VENDOR_NAME=${vendor_name} PROJECT_NAME=${PROJECT_NAME} LIMIT_TIME=${LimitTime}
clang --target=aarch64-none-linux-android28 main.c anctee__aarch64.o -o test -Wl,-gc-sections
ls -al anctee__aarch64.o test
adb push test /data/local/tmp
echo
adb shell /data/local/tmp/test
cd - >/dev/null
