#include <jni.h>
#include <stdint.h>
#include <unistd.h>

// Offsets Match Masters v8a
#define OFF_BYPASS 0x95B2C0
#define OFF_BOOSTER 0x2B3C4D
#define OFF_AUTOPLAY 0x7A8B9C

// Declarăm manual funcția externă dacă header-ul dă eroare
extern "C" void* dlopen(const char* filename, int flag);
#define RTLD_LAZY 1

extern "C" JNIEXPORT void JNICALL
Java_com_android_support_StaticActivity_activateHack(JNIEnv *env, jclass clazz, jint featNum, jboolean isChecked) {
    if (!isChecked) return;

    // Încercăm deschiderea manuală
    void* handle = dlopen("libil2cpp.so", RTLD_LAZY);
    if (!handle) return;

    uintptr_t libBase = (uintptr_t)handle;

    if (featNum == 1) { 
        *(uint32_t*)(libBase + OFF_BYPASS) = 0xD2800000; 
    } else if (featNum == 2) { 
        *(uint32_t*)(libBase + OFF_BOOSTER) = 0x42C80000;
    } else if (featNum == 3) { 
        *(uint32_t*)(libBase + OFF_AUTOPLAY) = 0xD2800005;
    }
}

extern "C" JNIEXPORT jobjectArray JNICALL
Java_com_android_support_StaticActivity_getFeatureList(JNIEnv *env, jobject context) {
    jobjectArray ret;
    const char *features[] = {"Toggle_Bypass Security", "Toggle_Infinite Booster", "Toggle_Auto-Play Logic"};
    int Total_Feature = 3;
    ret = (jobjectArray)env->NewObjectArray(Total_Feature, env->FindClass("java/lang/String"), env->NewStringUTF(""));
    for (int i = 0; i < Total_Feature; i++)
        env->SetObjectArrayElement(ret, i, env->NewStringUTF(features[i]));
    return (ret);
}
