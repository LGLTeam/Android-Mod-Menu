#ifndef DAWN_LOGGER_H
#define DAWN_LOGGER_H

#include <android/log.h>

enum daLogType {
    daDEBUG = 3,
    daERROR = 6,
    daINFO = 4,
    daWARN = 5
};

//Change this to another Log Tag if ya want. IN the batch script I provide you change the log tag then too
#define TAG OBFUSCATE("Mod_Menu")

#define LOGD(...) ((void)__android_log_print(daDEBUG, TAG, __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(daERROR, TAG, __VA_ARGS__))
#define LOGI(...) ((void)__android_log_print(daINFO,  TAG, __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(daWARN,  TAG, __VA_ARGS__))

#endif //DAWN_LOGGER_H