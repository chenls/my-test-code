APP_ABI := arm64-v8a
APP_STL := c++_shared
APP_CPPFLAGS += -fno-rtti
APP_CFLAGS += -fstack-protector
APP_PLATFORM := android-28
APP_ALLOW_MISSING_DEPS=true
APP_OPTIM := debug