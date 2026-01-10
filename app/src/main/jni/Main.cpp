#include <jni.h>
#include <dlfcn.h>
#include <stdint.h>
#include <unistd.h>
#include <string>
#include <thread>

// Offsets Match Masters v8a
#define OFF_BYPASS 0x95B2C0
#define OFF_BOOSTER 0x2B3C4D
#define OFF_AUTOPLAY 0x7A8B9C

// Funcția care primește comenzile de la Menu.java
extern "C" JNIEXPORT void JNICALL
Java_com_android_support_StaticActivity_activateHack(JNIEnv *env, jclass clazz, jint featNum, jboolean isChecked) {
    if (!isChecked) return;

    // Deschidem librăria jocului
    void* handle = dlopen("libil2cpp.so", RTLD_LAZY);
    if (!handle) return;

    // Calculăm adresa de bază
    uintptr_t libBase = (uintptr_t)handle;

    // Aplicăm patch-urile în funcție de butonul apăsat
    if (featNum == 1) { // Bypass Security
        *(uint32_t*)(libBase + OFF_BYPASS) = 0xD2800000; 
    } else if (featNum == 2) { // Infinite Booster
        *(uint32_t*)(libBase + OFF_BOOSTER) = 0x42C80000;
    } else if (featNum == 3) { // Auto-Play Logic
        *(uint32_t*)(libBase + OFF_AUTOPLAY) = 0xD2800005;
    }
}

// Funcție pentru a genera lista de funcții în meniu (Cerută de LGL Template)
extern "C" JNIEXPORT jobjectArray JNICALL
Java_com_android_support_StaticActivity_getFeatureList(JNIEnv *env, jobject context) {
    jobjectArray ret;
    const char *features[] = {
        "Toggle_Bypass Security",
        "Toggle_Infinite Booster",
        "Toggle_Auto-Play Logic"
    };

    int Total_Feature = (sizeof features / sizeof features[0]);
    ret = (jobjectArray)env->NewObjectArray(Total_Feature, env->FindClass("java/lang/String"), env->NewStringUTF(""));

    for (int i = 0; i < Total_Feature; i++)
        env->SetObjectArrayElement(ret, i, env->NewStringUTF(features[i]));

    return (ret);
}
