#ifndef MENU_HPP
#define MENU_HPP

#include <jni.h>

void setText(JNIEnv *env, jobject obj, const char* text);

jstring Icon(JNIEnv *env, jobject thiz);

jstring IconWebViewData(JNIEnv *env, jobject thiz);

jobjectArray SettingsList(JNIEnv *env, jobject activityObject);

jobjectArray GetFeatureList(JNIEnv *env, jobject context);

void Changes(JNIEnv *env, jclass clazz, jobject obj,
             jint featNum, jstring featName, jint value, jlong Lvalue,
             jboolean boolean, jstring str);

#endif