LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := test

LOCAL_CFLAGS += -O0 -g -DANC_DEBUG

LOCAL_CFLAGS += -fsanitize=address -fno-omit-frame-pointer
LOCAL_LDFLAGS += -fsanitize=address

LOCAL_C_INCLUDES += $(LOCAL_PATH)
LOCAL_SRC_FILES += anc_memory_debug.c \
	anc_log.c \
	anc_memory.c \
	anc_memory_wrapper.c \
	anc_time.c \
	main.c

include $(BUILD_EXECUTABLE)