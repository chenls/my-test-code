/home/chenliusheng/soft/android-ndk-r20/toolchains/llvm/prebuilt/linux-x86_64/bin/clang \
--target=aarch64-none-linux-android28 \
--gcc-toolchain=/home/chenliusheng/soft/android-ndk-r20/toolchains/llvm/prebuilt/linux-x86_64 \
--sysroot=/home/chenliusheng/soft/android-ndk-r20/toolchains/llvm/prebuilt/linux-x86_64/sysroot \
 \
 \
-g \
-DANDROID \
-fdata-sections \
-ffunction-sections \
-funwind-tables \
-fstack-protector-strong \
-no-canonical-prefixes \
-fno-addrsig \
-Wa,--noexecstack \
-Wformat \
-Werror=format-security \
 \
-v \
-fPIE \
 \
 \
-o \
CMakeFiles/test.dir/main.c.s \
 \
 \
-S \
/home/chenliusheng/Desktop/test/arm_dot/main.c