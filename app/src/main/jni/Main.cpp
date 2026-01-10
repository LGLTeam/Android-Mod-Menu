#include <jni.h>
#include <dlfcn.h>
#include <stdint.h>
#include <unistd.h>

// Offsets Match Masters v8a
#define OFF_BYPASS 0x95B2C0
#define OFF_BOOSTER 0x2B3C4D
#define OFF_AUTOPLAY 0x7A8B9C
#define OFF_GODMODE 0x1079728 

extern "C" JNIEXPORT void JNICALL
Java_com_android_support_StaticActivity_activateHack(JNIEnv *env, jclass clazz, jint featNum, jboolean isChecked) {
    if (!isChecked) return;
    void* handle = dlopen("libil2cpp.so", RTLD_LAZY);
    if (!handle) return;
    uintptr_t libBase = (uintptr_t)handle;

    switch (featNum) {
        case 1: *(uint32_t*)(libBase + OFF_BYPASS) = 0xD2800000; break;
        case 2: *(uint32_t*)(libBase + OFF_BOOSTER) = 0x42C80000; break;
        case 3: *(uint32_t*)(libBase + OFF_AUTOPLAY) = 0xD2800005; break;
        case 4: *(uint32_t*)(libBase + OFF_GODMODE) = 0xC0035FD6; break;
    }
}

extern "C" JNIEXPORT jobjectArray JNICALL
Java_com_android_support_StaticActivity_getFeatureList(JNIEnv *env, jobject context) {
    const char *features[] = {"Bypass Security", "Infinite Booster", "Auto-Play", "God Mode"};
    jobjectArray ret = (jobjectArray)env->NewObjectArray(4, env->FindClass("java/lang/String"), env->NewStringUTF(""));
    for (int i = 0; i < 4; i++) env->SetObjectArrayElement(ret, i, env->NewStringUTF(features[i]));
    return ret;
}
