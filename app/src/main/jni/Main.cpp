#include <jni.h>
#include <substrate.h>
#include <unistd.h>

// Offsets Match Masters v8a
#define OFF_BYPASS 0x95B2C0
#define OFF_BOOSTER 0x2B3C4D
#define OFF_AUTOPLAY 0x7A8B9C

extern "C" {
    JNIEXPORT void JNICALL Java_com_android_support_StaticActivity_activateHack(JNIEnv *env, jclass clazz, jint featNum, jboolean isChecked) {
        if (!isChecked) return;
        uintptr_t base = (uintptr_t)dlopen("libil2cpp.so", RTLD_LAZY);
        if (featNum == 1) *(uint32_t*)(base + OFF_BYPASS) = 0xD2800000; // Bypass
        if (featNum == 2) *(uint32_t*)(base + OFF_BOOSTER) = 0x42C80000; // Booster
        if (featNum == 3) *(uint32_t*)(base + OFF_AUTOPLAY) = 0xD2800005; // Auto-Play
    }
}
