#include "Menu/Setup.h"
// Register your class native methods. This is to hide function names from disassembler
// See more: https://developer.android.com/training/articles/perf-jni#native-libraries

jint Register(JNIEnv *globalEnv, const char* classPath, const JNINativeMethod* methods, jint nMethods) {
    jclass c = globalEnv->FindClass(classPath);
    if (c != nullptr) {

        int mm = globalEnv->RegisterNatives(c, methods,
                                            nMethods);
        if (mm != JNI_OK) {
            LOGE(OBFUSCATE("%s error"), classPath);
            return mm;
        }
    } else {
        LOGE(OBFUSCATE("JNI error"));
        return JNI_ERR;
    }

    LOGI(OBFUSCATE("Register OK"));
    return 0;
}