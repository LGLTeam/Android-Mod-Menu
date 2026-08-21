#include "Jni.hpp"
#include <list>
#include <vector>
#include <cstring>
#include <string>
#include <pthread.h>
#include <thread>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <dlfcn.h>
#include "Includes/obfuscate.h"
#include "Menu/Jni.hpp"
#include "Includes/Logger.h"

void Dialog(JNIEnv *env, jobject context, const char *title, const char *message, const char *openBtn, const char *closeBtn, int sec, const char *url) {
    jclass dialogHelperClass = env->FindClass(OBFUSCATE("com/android/support/DialogHelper"));
    jmethodID showMethod = env->GetStaticMethodID(dialogHelperClass, OBFUSCATE("showDialogWithLink"),
                                                  OBFUSCATE("(Landroid/content/Context;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;ILjava/lang/String;)V"));

    jstring jTitle = env->NewStringUTF(title);
    jstring jMessage = env->NewStringUTF(message);
    jstring jOpen = env->NewStringUTF(openBtn);
    jstring jClose = env->NewStringUTF(closeBtn);
    jint jSec = sec;
    jstring jUrl = env->NewStringUTF(url);

    env->CallStaticVoidMethod(dialogHelperClass, showMethod, context, jTitle, jMessage, jOpen, jClose, jSec, jUrl);

    env->DeleteLocalRef(jTitle);
    env->DeleteLocalRef(jMessage);
    env->DeleteLocalRef(jOpen);
    env->DeleteLocalRef(jClose);
    env->DeleteLocalRef(jUrl);
}

void Toast(JNIEnv *env, jobject thiz, const char *text, int length) {
    jstring jstr = env->NewStringUTF(text);
    jclass toast = env->FindClass(OBFUSCATE("android/widget/Toast"));
    jmethodID methodMakeText =env->GetStaticMethodID(toast,OBFUSCATE("makeText"),OBFUSCATE("(Landroid/content/Context;Ljava/lang/CharSequence;I)Landroid/widget/Toast;"));
    jobject toastobj = env->CallStaticObjectMethod(toast, methodMakeText,thiz, jstr, length);
    jmethodID methodShow = env->GetMethodID(toast, OBFUSCATE("show"), OBFUSCATE("()V"));
    env->CallVoidMethod(toastobj, methodShow);
}

//Big letter cause crash
void setText(JNIEnv *env, jobject obj, const char* text){
    //https://stackoverflow.com/a/33627640/3763113
    //A little JNI calls here. You really really need a great knowledge if you want to play with JNI stuff
    //Html.fromHtml("");
    jclass html = (*env).FindClass(OBFUSCATE("android/text/Html"));
    jmethodID fromHtml = (*env).GetStaticMethodID(html, OBFUSCATE("fromHtml"), OBFUSCATE("(Ljava/lang/String;)Landroid/text/Spanned;"));

    //setText("");
    jclass textView = (*env).FindClass(OBFUSCATE("android/widget/TextView"));
    jmethodID setText = (*env).GetMethodID(textView, OBFUSCATE("setText"), OBFUSCATE("(Ljava/lang/CharSequence;)V"));

    //Java string
    jstring jstr = (*env).NewStringUTF(text);
    (*env).CallVoidMethod(obj, setText,  (*env).CallStaticObjectMethod(html, fromHtml, jstr));
}
