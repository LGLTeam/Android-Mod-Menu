#include <list>
#include <vector>
#include <cstring>
#include <pthread.h>
#include <thread>
#include <cstring>
#include <string>
#include <jni.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <dlfcn.h>
#include "Includes/Logger.h"
#include "Includes/obfuscate.h"
#include "Includes/Utils.hpp"
#include "Menu/Menu.hpp"
#include "Menu/Jni.hpp"
#include "Includes/Macros.h"
#include "dobby.h"

int scoreMul = 1, coinsMul = 1;

// Do not change or translate the first text unless you know what you are doing
// Assigning feature numbers is optional. Without it, it will automatically count for you, starting from 0
// Assigned feature numbers can be like any numbers 1,3,200,10... instead in order 0,1,2,3,4,5...
// ButtonLink, Category, RichTextView and RichWebView is not counted. They can't have feature number assigned
// Toggle, ButtonOnOff and Checkbox can be switched on by default, if you add True_. Example: CheckBox_True_The Check Box
// To learn HTML, go to this page: https://www.w3schools.com/
jobjectArray GetFeatureList(JNIEnv *env, jobject context) {
    jobjectArray ret;

    const char *features[] = {
            OBFUSCATE("Heading_Free Fire Mod Menu"),
            OBFUSCATE("Toggle_Headshot 90%"),
            OBFUSCATE("Toggle_Aim Lock"),
            OBFUSCATE("Toggle_Ghost Hack"),
            OBFUSCATE("SeekBar_FOV Slider_1_120"),
            OBFUSCATE("Button_Anti-Ban Fix")
    };

    int Total_Feature = (sizeof features / sizeof features[0]);
    ret = (jobjectArray)
            env->NewObjectArray(Total_Feature, env->FindClass(OBFUSCATE("java/lang/String")),
                                env->NewStringUTF(""));

    for (int i = 0; i < Total_Feature; i++)
        env->SetObjectArrayElement(ret, i, env->NewStringUTF(features[i]));

    return (ret);
}



bool btnPressed = false;

//Target main lib here
#define targetLibName OBFUSCATE("libil2cpp.so")

void Changes(JNIEnv *env, jclass clazz, jobject obj, jint featNum, jstring featName, jint value, jlong Lvalue, jboolean boolean, jstring text) {

    switch (featNum) {
        case 0:
            // offset, hex
            PATCH_SWITCH(targetLibName, "0x1079728", "C0 03 5F D6", boolean);
            // The patch switch has been returned and reworked:
            // - (active) Dobby-Kitty implementation
            // - reworked KittyMemory implementation
            //
            // if you encounter any problems:
            // - switch to Kitty implementation (uncomment code in Macros.h)
            // - uncommiting logging for detailed debug
            // - special attention to the preferences -> this is the only source of this problem in the past that I have noticed:
            // -- try rename the preferences file;
            // -- for a maximum stable and flexible save settings, recommend using own system with XML/JSON files.

            // alt possibles usage variants:
            // symbol, hex
            PATCH_SWITCH(targetLibName, "_example__sym", "C0 03 5F D6", boolean);
            // offset, asm
            PATCH_SWITCH(targetLibName, "0x1079728", "ret", boolean);
            // symbol, asm
            PATCH_SWITCH(targetLibName, "_example__sym", "ret", boolean);

            // asm allows you to avoid using hex code, as it is generated automatically from the instructions.
            // - this is the awesome option if you know what you're doing
            // recommended insert ';' to separate statements, example: "mov x0, #1; ret"
            // recommended to test your instructions on https://armconverter.com or
            // https://shell-storm.org/online/Online-Assembler-and-Disassembler/

            // - this is probably especially useful with creating dynamic deep patches
            dPATCH_SWITCH(true, targetLibName, "0x1079728", "mov w%d, #%d", 0, 222);
            dPATCH_SWITCH(true, targetLibName, "_example__sym", "mov w%d, #%d", 0, 222);
            // standard formatting specifiers are supported (%d, %i, %x, %s, etc.)


            // Relative patches allow you to speed up patch creation if you are sure that the offsets within methods rarely change
            // So, you only need to update the offset instruction for the function
            // https://www.rapidtables.com/calc/math/hex-calculator.html <- use hex calculator to calculate the offset relative to the method
            // ! This is an extremely unstable due to the hard offsets... don't forget to check the logs to identify outdated offsets
            // offset, offset, hex
            rPATCH_SWITCH(targetLibName, "0x1079728", "0x204", "C0 03 5F D6", boolean);
            // sym, offset, hex
            rPATCH_SWITCH(targetLibName, "_example__sym", "0xAC", "C0 03 5F D6", boolean);
            // offset, offset, asm
            rPATCH_SWITCH(targetLibName, "0x1079728", "0x204", "mov x0, #0xffffff; ret", boolean);
            // sym, offset, asm
            rPATCH_SWITCH(targetLibName, "_example__sym", "0xAC", "mov x0, #0xffffff; ret", boolean);
            break;
        case 4:
            if(boolean) {
                // offset, hex
                PATCH(targetLibName, "0x10709AC", "E05F40B2 C0035FD6");
                rPATCH(targetLibName, "0x107094D", "0x5F", "E05F40B2 C0035FD6");

                // alt possibles usage variants:
                // symbol, hex
                PATCH(targetLibName, "_example__sym", "E0 5F 40 B2 C0 03 5F D6");
                rPATCH(targetLibName, "_example__sym", "0x5F", "E0 5F 40 B2 C0 03 5F D6");
                // offset, asm
                PATCH(targetLibName, "0x10709AC", "mov x0, #0xffffff; ret");
                rPATCH(targetLibName, "0x107094D", "0x5F", "mov x0, #0xffffff; ret");
                // symbol, asm
                PATCH(targetLibName, "_example__sym", "mov x0, #0xffffff; ret");
                rPATCH(targetLibName, "_example__sym", "0x5F", "mov x0, #0xffffff; ret");
            } else {
                RESTORE(targetLibName, "0x10709AC");
                rRESTORE(targetLibName, "0x10709AC", "0x5F");
                // or
                RESTORE(targetLibName, "_example__sym");
                rRESTORE(targetLibName, "_example__sym", "0x5F");
            }
            break;
        case 1:
            btnPressed = true;
            break;
        case 2:
            scoreMul = value;
            break;
        case 3:
            coinsMul = value;
            break;
        case 5:
            // you can use this for things as detect log, counting function calls, executing side code before the function is executed
            // now instrument wrapper implemented for detecting execution in logcat
            INST(targetLibName, "0x235630", "AnyNameForDetect2", boolean);

            if(boolean) {
                INST(targetLibName, "_example__sym", "AnyNameForDetect3", true);
            } else {
                INST(targetLibName, "_example__sym", "AnyNameForDetect3", false);
            }
            break;
        default:
            break;
    }
}

//CharacterPlayer
void (*StartInvcibility)(void *instance, float duration);

void (*old_Update)(void *instance);
void Update(void *instance) {
    if (instance != nullptr) {
        if (btnPressed) {
            StartInvcibility(instance, 30);
            btnPressed = false;
        }
    }
    return old_Update(instance);
}

/*
 void (*old_AddScore)(void *instance, int score);
 void AddScore(void *instance, int score) {
    //default any actions
    return old_AddScore(instance, score * scoreMul);
 }
*/
// === This function was completely replaced with `install_hook_name` from dobby.h ===
// (base name, return type, ... args)
install_hook_name(AddScore, void *, void *instance, int score) {
    // default any actions

    // use orig_ for call original function
    return orig_AddScore(instance, score + scoreMul);
}

void (*old_AddCoins)(void *instance, int count);
void AddCoins(void *instance, int count) {
    return old_AddCoins(instance, count * coinsMul);
}


// we will run our hacks in a new thread so our while loop doesn't block process main thread
void hack_thread() {
    // This loop should be always enabled in unity game
    // because libil2cpp.so is not loaded into memory immediately.
    while (!isLibraryLoaded(targetLibName)) {
        sleep(1); // Wait for target lib be loaded.
    }

    // In Android Studio, to switch between arm64-v8a and armeabi-v7a syntax highlighting,
    // You can modify the "Active ABI" in "Build Variants" to switch to another architecture for parsing.
#if defined(__aarch64__)
    //Il2Cpp: Use RVA offset
    StartInvcibility = (void (*)(void *, float)) getAbsoluteAddress(targetLibName, OBFUSCATE("0x107A3BC"));
    StartInvcibility = (void (*)(void *, float)) getAbsoluteAddress(targetLibName, OBFUSCATE("_characterPlayer_Update"));

    HOOK(targetLibName, "0x107A2FC", AddCoins, old_AddCoins);

    // HOOK(targetLibName, "0x107A2E0", AddScore, old_AddScore);
    // === This function was completely replaced with super-macro `install_hook_name` from dobby.h ===
    // don't forget set address for install_hook:
    // ! getAbsoluteAddress not have OBFUSCATE, so don't forget use his here
    install_hook_AddScore(getAbsoluteAddress(targetLibName,OBFUSCATE("0x107A2E0")));

    HOOK(targetLibName, "0x1078C44", Update, old_Update);
    //HOOK(targetLibName, "0x1079728", Kill, old_Kill);
    //HOOK(targetLibName, "_example__sym", Kill, old_Kill);
    //HOOK_NO_ORIG("libFileC.so", "0x123456", FunctionExample);
    //HOOK_NO_ORIG("libFileC.so", "_example__sym", FunctionExample);

    //PATCH(targetLibName, "0x10709AC", "E05F40B2C0035FD6");

    INST(targetLibName, "0x23558C", "AnyNameForDetect", true);

    // LOGI(OBFUSCATE("Test SYM: 0x%llx"), (uintptr_t)getAbsoluteAddress(OBFUSCATE("libil2cpp.so"), OBFUSCATE("il2cpp_init")));
#elif defined(__arm__)
    //Put your code here if you want the code to be compiled for armv7 only
#endif

    LOGI(OBFUSCATE("Done"));
}

// Functions with `__attribute__((constructor))` are executed immediately when System.loadLibrary("lib_name") is called.
// If there are multiple such functions at the same time, `constructor(priority)` (the priority is an integer)
// will determine the execution priority, otherwise the execution order is undefined behavior.
__attribute__((constructor))
void lib_main() {
    // Create a new thread so it does not block the main thread, means the game would not freeze
    // In modern C++, you should use std::thread(yourFunction).detach() instead of pthread_create
    std::thread(hack_thread).detach();
}
