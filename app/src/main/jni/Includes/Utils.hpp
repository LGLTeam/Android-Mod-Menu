#ifndef UTILS
#define UTILS

#include <jni.h>
#include <unistd.h>
#include <cstdio>
#include <cstring>
#include <string>
#include <cstdlib>
#include "Includes/Logger.h"

typedef unsigned long DWORD;

DWORD findLibrary(const char *library);

DWORD getAbsoluteAddress(const char *libraryName, DWORD relativeAddr);

jboolean isGameLibLoaded(JNIEnv *env, jobject thiz);

bool isLibraryLoaded(const char *libraryName);

uintptr_t str2Offset(const char *c);

#endif