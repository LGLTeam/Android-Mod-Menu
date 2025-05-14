
#ifndef ANDROID_MOD_MENU_JNI_HPP
#define ANDROID_MOD_MENU_JNI_HPP

#include <jni.h>

namespace ToastLength {
    inline const int LENGTH_LONG = 1;
    inline const int LENGTH_SHORT = 0;
}

void setDialog(jobject ctx, JNIEnv *env, const char *title, const char *msg);

void Toast(JNIEnv *env, jobject thiz, const char *text, int length);

void startService(JNIEnv *env, jobject ctx);

void CheckOverlayPermission(JNIEnv *env, jclass thiz, jobject ctx);

#endif //ANDROID_MOD_MENU_JNI_HPP
