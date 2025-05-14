LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

# Here is the name of your lib.
# When you change the lib name, change also on System.loadLibrary("") under OnCreate method on StaticActivity.java
# Both must have same name
LOCAL_MODULE    := MyLibName

# -std=c++17 is required to support AIDE app with NDK
LOCAL_CFLAGS := -w -s -Wno-error=format-security -fvisibility=hidden -fpermissive -fexceptions
LOCAL_CPPFLAGS := -w -s -Wno-error=format-security -fvisibility=hidden -Werror -std=c++17
LOCAL_CPPFLAGS += -Wno-error=c++11-narrowing -fpermissive -Wall -fexceptions
LOCAL_LDFLAGS += -Wl,--gc-sections,--strip-all,-llog
LOCAL_LDLIBS := -llog -landroid -lEGL -lGLESv2
LOCAL_ARM_MODE := arm

LOCAL_C_INCLUDES += $(LOCAL_PATH)

# Here you add the cpp file to compile
LOCAL_SRC_FILES := Main.cpp \
	Substrate/hde64.c \
	Substrate/SubstrateDebug.cpp \
	Substrate/SubstrateHook.cpp \
	Substrate/SubstratePosixMemory.cpp \
	Substrate/SymbolFinder.cpp \
	KittyMemory/KittyMemory.cpp \
	KittyMemory/MemoryPatch.cpp \
    KittyMemory/MemoryBackup.cpp \
    KittyMemory/KittyUtils.cpp \
	And64InlineHook/And64InlineHook.cpp \

include $(BUILD_SHARED_LIBRARY)
