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

bool noDeath;
int scoreMul = 1, coinsMul = 1;

struct MemPatches {
    // let's assume we have patches for these functions for whatever game
    // boolean get_canShoot() function
    MemoryPatch noDeath;
    // etc...
} gPatches;

// Do not change or translate the first text unless you know what you are doing
// Assigning feature numbers is optional. Without it, it will automatically count for you, starting from 0
// Assigned feature numbers can be like any numbers 1,3,200,10... instead in order 0,1,2,3,4,5...
// ButtonLink, Category, RichTextView and RichWebView is not counted. They can't have feature number assigned
// Toggle, ButtonOnOff and Checkbox can be switched on by default, if you add True_. Example: CheckBox_True_The Check Box
// To learn HTML, go to this page: https://www.w3schools.com/

jobjectArray GetFeatureList(JNIEnv *env, jobject context) {
    jobjectArray ret;

    const char *features[] = {
            OBFUSCATE("Toggle_No death"),
            OBFUSCATE("Button_Start Invcibility (30 sec duration)"),
            OBFUSCATE("SeekBar_Score multiplier_1_100"),
            OBFUSCATE("SeekBar_Coins multiplier_1_1000"),
            OBFUSCATE("Category_Examples"), //Not counted
            OBFUSCATE("Toggle_The toggle"),
            OBFUSCATE(
                    "100_Toggle_True_The toggle 2"), //This one have feature number assigned, and switched on by default
            OBFUSCATE("110_Toggle_The toggle 3"), //This one too
            OBFUSCATE("SeekBar_The slider_1_100"),
            OBFUSCATE("SeekBar_Kittymemory slider example_1_5"),
            OBFUSCATE("Spinner_The spinner_Items 1,Items 2,Items 3"),
            OBFUSCATE("Button_The button"),
            OBFUSCATE("ButtonLink_The button with link_https://www.youtube.com/"), //Not counted
            OBFUSCATE("ButtonOnOff_The On/Off button"),
            OBFUSCATE("CheckBox_The Check Box"),
            OBFUSCATE("InputValue_Input number"),
            OBFUSCATE("InputValue_1000_Input number 2"), //Max value
			OBFUSCATE("1111_InputLValue_Input long number"),
            OBFUSCATE("InputLValue_1000000000000_Input long number 2"), //Max value
            OBFUSCATE("InputText_Input text"),
            OBFUSCATE("RadioButton_Radio buttons_OFF,Mod 1,Mod 2,Mod 3"),

            //Create new collapse
            OBFUSCATE("Collapse_Collapse 1"),
            OBFUSCATE("CollapseAdd_Toggle_The toggle"),
            OBFUSCATE("CollapseAdd_Toggle_The toggle"),
            OBFUSCATE("123_CollapseAdd_Toggle_The toggle"),
            OBFUSCATE("122_CollapseAdd_CheckBox_Check box"),
            OBFUSCATE("CollapseAdd_Button_The button"),

            //Create new collapse again
            OBFUSCATE("Collapse_Collapse 2_True"),
            OBFUSCATE("CollapseAdd_SeekBar_The slider_1_100"),
            OBFUSCATE("CollapseAdd_InputValue_Input number"),

            OBFUSCATE("RichTextView_This is text view, not fully HTML."
                      "<b>Bold</b> <i>italic</i> <u>underline</u>"
                      "<br />New line <font color='red'>Support colors</font>"
                      "<br/><big>bigger Text</big>"),
            OBFUSCATE("RichWebView_<html><head><style>body{color: white;}</style></head><body>"
                      "This is WebView, with REAL HTML support!"
                      "<div style=\"background-color: darkblue; text-align: center;\">Support CSS</div>"
                      "<marquee style=\"color: green; font-weight:bold;\" direction=\"left\" scrollamount=\"5\" behavior=\"scroll\">This is <u>scrollable</u> text</marquee>"
                      "</body></html>")
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

void Changes(JNIEnv *env, jclass clazz, jobject obj, jint featNum, jstring featName, jint value, jlong Lvalue, jboolean boolean, jstring text) {

    switch (featNum) {
        case 0:
        {
            if (boolean)
                gPatches.noDeath.Modify();
            else
                gPatches.noDeath.Restore();
            break;
        }
        case 1:
            btnPressed = true;
            break;
        case 2:
            scoreMul = value;
            break;
        case 3:
            coinsMul = value;
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

void (*old_AddScore)(void *instance, int score);
void AddScore(void *instance, int score) {
    return old_AddScore(instance, score * scoreMul);
}

void (*old_AddCoins)(void *instance, int count);
void AddCoins(void *instance, int count) {
    return old_AddCoins(instance, count * coinsMul);
}

//Target lib here
#define targetLibName OBFUSCATE("libil2cpp.so")

ElfScanner g_il2cppELF;

// we will run our hacks in a new thread so our while loop doesn't block process main thread
void *hack_thread(void *) {
    LOGI(OBFUSCATE("pthread created"));

    //Check if target lib is loaded
    /*do {
        sleep(1);
    } while (!isLibraryLoaded(targetLibName));*/

    do {
        sleep(1);
        // getElfBaseMap can also find lib base even if it was loaded from zipped base.apk
        g_il2cppELF = ElfScanner::createWithPath(targetLibName);
    } while (!g_il2cppELF.isValid());

    LOGI(OBFUSCATE("%s has been loaded"), (const char *) targetLibName);

#if defined(__aarch64__)
    uintptr_t il2cppBase = g_il2cppELF.base();

    //Il2Cpp: Use RVA offset
    StartInvcibility = (void (*)(void *, float)) getAbsoluteAddress(targetLibName, str2Offset(
            OBFUSCATE("0x107A3BC")));

    HOOK(targetLibName, str2Offset(OBFUSCATE("0x107A2E0")), AddScore, old_AddScore);
    HOOK(targetLibName, str2Offset(OBFUSCATE("0x107A2FC")), AddCoins, old_AddCoins);
    HOOK(targetLibName, str2Offset(OBFUSCATE("0x1078C44")), Update, old_Update);

    gPatches.noDeath = MemoryPatch::createWithHex(il2cppBase + str2Offset(OBFUSCATE("0x1079728")), "C0 03 5F D6");

    //HOOK(targetLibName, str2Offset(OBFUSCATE("0x1079728")), Kill, old_Kill);

    //PATCH(targetLibName, str2Offset("0x10709AC"), "E05F40B2 C0035FD6");
    //HOOK(OBFUSCATE("libFileB.so"), str2Offset(OBFUSCATE("0x123456")), FunctionExample, old_FunctionExample);
    //HOOK("libFileB.so", 4646464, FunctionExample, old_FunctionExample);
    //HOOK_NO_ORIG("libFileC.so", str2Offset("0x123456"), FunctionExample);
    //HOOKSYM("libFileB.so", "__SymbolNameExample", FunctionExample, old_FunctionExample);
    //HOOKSYM_NO_ORIG("libFileB.so", "__SymbolNameExample", FunctionExample);

#elif defined(__arm__)
    //Put your code here if you want the code to be compiled for armv7 only
#endif

    LOGI(OBFUSCATE("Done"));
    return nullptr;
}

__attribute__((constructor))
void lib_main() {
    // Create a new thread so it does not block the main thread, means the game would not freeze
    pthread_t ptid;
    pthread_create(&ptid, NULL, hack_thread, NULL);
}