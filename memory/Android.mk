LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := test

LOCAL_CFLAGS += -O0 -g -DANC_DEBUG

LOCAL_CFLAGS += -fsanitize=address -fno-omit-frame-pointer -O0
LOCAL_CXXFLAGS += -fsanitize=address -fno-omit-frame-pointer -O0
LOCAL_LDFLAGS += -fsanitize=address -v

# LOCAL_CFLAGS += -Wall -Wextra -Werror -Wshadow
LOCAL_CFLAGS += -Wimplicit-function-declaration -Wconversion
LOCAL_CFLAGS += -fstack-protector --param ssp-buffer-size=4 -Wstack-protector
LOCAL_CFLAGS +=  -ferror-limit=19 -fmessage-length=226 -fsanitize-blacklist=/data/arm-toolchains/android-ndk-r20/toolchains/llvm/prebuilt/linux-x86_64/lib64/clang/8.0.7/share/asan_blacklist.txt -fsanitize-address-use-after-scope -fno-assume-sane-operator-new -fno-signed-char -fobjc-runtime=gcc -fdiagnostics-show-option -fcolor-diagnostics

LOCAL_C_INCLUDES += $(LOCAL_PATH)
LOCAL_SRC_FILES += anc_memory_debug.c \
	anc_log.c \
	anc_memory.c \
	anc_memory_wrapper.c \
	anc_time.c \
	main.cpp

include $(BUILD_EXECUTABLE)