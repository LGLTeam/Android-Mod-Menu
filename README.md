**WARNING: THIS TEMPLATE IS NOT FOR NEWBIES, THIS IS FOR EXPERIENCES PROGRAMMERS ONLY. NEWBIES SHOULD NOT PROCEED TO TRY IT**

**This won't cover how to mod games in general, hooking functions, etc that every other online tutorial already covers. This template simply tells you how to use them**

**For Android mobile users who don't have a PC, please read [README-MOBILE.md](https://github.com/LGLTeam/Android-Mod-Menu/blob/master/README-MOBILE.md)**

# KNOWN BUG
- Spinner does not show on Android 11

# Table of contents
- [Prerequisites](https://github.com/LGLTeam/Android-Mod-Menu/blob/master/README.md#prerequisites)
- [What you need](#what-you-need)
- [Video Tutorial](#video-tutorial)
- [Installation](#installation)
- [Files to work with and making changes](#files-to-work-with-and-making-changes)
- [Implementing the menu to the target game](#implementing-the-menu-to-the-target-game)
- [Loading lib without mod menu](#loading-lib-without-mod-menu)
- [Leeching concerns](#leeching-concerns)
- [FAQ](#faq)
- [Reporting issues/Cоntact](reporting-issuescоntact)
- [Credits/Acknowledgements](#creditsacknowledgements)

# Introduction
Floating mod menu for il2cpp and other native android games, originally based on [VanHoevenTRs](https://platinmods.com/threads/template-menu-free-for-mod-menu-il2cpp-and-other-native-games.67429/), and some codes used from [Octowolve](https://github.com/Octowolve/Hooking-Template-With-Mod-Menu). KittyMemory, MSHook, And64InlineHook and AY Obfuscator included. Assets are stored as base64 in cpp and does not need to be stored under assets folder.

Support Android 4.4.x up to Android S Preview. ARMv7, x86 and ARM64 architecture supported. However x86 is deprecated for Unity games so x86 is not our priority

Preview:

![](https://i.imgur.com/zeumkBG.gif)

# Prerequisites
Before we can jump head first into working a template, we need to go over a few things.

* **AN EXPERIENCED MODDER, NOT A BEGINNER:** You should be able to mod any games in general, like modifying .so files, dll files, smali files, etc.
* Basic knowledge of smali dalvik opcodes to modify smali
* Basic knowledge ARM and ARM64 assembly, to be able to patch hex (No need x86)
* Basic knowledge of C++ and java (JNI is optional)
* Be able to write hook function in C++ (Not really needed, but recommended if you want to do advanced modding in the future)
* Basic awareness of how Android layout works in XML and Java. This project only use Java for layout but you will learn it easly
* Time and patience: Don't start working on this if you have deadlines or important work. Take your time to read, learn and get used to work with this project.
* DIY (Do it yourself): Yes, you must be able to do things yourself, not depending being spoonfeed. We are not the teachers.
* An inquisitive mind

# What you need
* Android Studio 4 and up: https://developer.android.com/studio
* NDK Installed via Android Studio (Cmake is not needed) https://developer.android.com/studio/projects/install-ndk#default-version
* Apktool: [Apktool.jar](https://ibotpeaches.github.io/Apktool/) or any 3rd party tools
* [APK Easy Tool](https://forum.xda-developers.com/android/software-hacking/tool-apk-easy-tool-v1-02-windows-gui-t3333960). To get main activity: 
* Any text editor. We use [Notepad++](https://notepad-plus-plus.org/downloads/)
* Any png compression to compress your png file: We use https://compresspng.com/
* Any base64 encoding to encode your file: We use https://www.base64encode.org/
* ARM converter, to convert ARM instruction to hex: https://armconverter.com/

# Video Tutorial
Big thanks to modders who created a video tutorial for me. Be warned, those videos might be outdated

PMT DVA: https://www.youtube.com/watch?v=ieMclBtL6Ig

Pasha Production: https://www.youtube.com/watch?v=RvrZKIe-QGc

# Installation
Download this repo as ZIP, or clone using any git tools

Or download Releases here https://github.com/LGLTeam/Android-Mod-Menu/releases

Extract the source to your desired location. The location must **NOT** contain any spaces or symbols

Open the project

Please wait for a while, it will index and sync the project for the first time, takes around a minute depending your computer performance

After it's done, you can start working!

# Files to work with and making changes

#### **modmenu/Logcat.java**
To save and clear logcat on menu settings without root and without file permission. Can be helpful for modders to diagnose the issues

Android 11: /storage/emulated/0/Documents/Mod Menu logs/

Android 10 and below: /storage/emulated/0/Android/data/(package name)/files/Mod Menu logs

#### **modmenu/Preferences.java**

Saving the menu feature preferences and calling changes via JNI

#### **modmenu/FloatingModMenuService.java**

Main codes of floating mod menu design

You don't need to change unless you want to redesign it. The codes are explained in the comments

- `GradientDrawable`: A code for setting corner and stroke/inner border. Works for any View Components

```java
GradientDrawable gradientdrawable = new GradientDrawable();
gradientdrawable.setCornerRadius(20); //Set corner
gradientdrawable.setColor(Color.parseColor("#1C2A35")); //Set background color
gradientdrawable.setStroke(1, Color.parseColor("#32cb00")); //Set border
```

Set the gradient drawable to the view component

```java
[name of your view component].setBackground(gradientdrawable);
```

- Resizing menu box

I've added variables so you can find it easly to resize

```java
private final int MENU_WIDTH = 290;
private final int MENU_HEIGHT = 200;
```

Note: You may need to implement auto sizing due to many types of phone with different DPIs and resolutions

- Color Animation: The codes can be seen in `startAnimation()`

- Adding new view

Normally the Android development documentation does not explain the code in java. If you read the Android development documentation and you see an example like TextView

```java
TextView textView = (TextView) findViewById(R.id.textView);
textView.setFontVariationSettings("'wdth' 150");
```

This is for xml. Instead, create an instance for java and add view to your Layout

```java
TextView textView = new TextView(this);
textView.setFontVariationSettings("'wdth' 150");
LinearLayoutExample.addView(textView);
```

While we can't explain much here, you can use Google. Search like `create a textview programmatically android`, `create a button programmatically android` etc. for more infomation

#### **MainActivity.java**

The Main Activity. Checks if device running Android 6.0 or above and if have overlay permission enabled before starting menu service.

You pretty don't need to work with it unless you are implementing something like login layout.

#### **jni/Menu.h**

Menu related with JNI calls

- `Title`: Big text

- `Heading`: Little text. Semi HTML is supported. Text will scroll if the text is too long

- `Icon`: Compressed image that is encoded to base64

You can pretty much use any tools for base64 encoding.

We use a simple website https://www.base64encode.org/

Scroll down till you see `Encode files into Base64 format`. Click or tap on the box to select a file

Click on `ENCODE` button and click on `CLICK OR TAP HERE` to download your encoded file. Now you can paste it in cpp code

- `IconWebViewData`: Use icon in Web view with GIF animation support. URL requires internet permission `android.permission.INTERNET`

Examples

```cpp
//From internet: (Requires android.permission.INTERNET)
return env->NewStringUTF("https://i.imgur.com/SujJ85j.gif"); 

//From assets folder: (Requires android.permission.INTERNET)
return env->NewStringUTF("file:///android_asset/example.gif"); 

//Base64 html:
return env->NewStringUTF("data:image/png;base64, <encoded base64 here>");

//Nothing:
return NULL
```

- `settingsList`: Feature list for settings

#### **jni/Main.cpp**

In this file, you will work with your mods. Below `hack_thread`, you write your code to patch with KittyMemory or hook with MShook. You must have learned it already

It has a macro to detect if the ARM architecture is 32-bit or 64-bit on compile-time, it's to avoid using wrong offsets, like using ARMv7 offsets on an ARM64 lib. Check the game's APK what libs it contains before you proceed. If you want to target armeabi-v7a lib, write the code below `#else`. If you want to target arm64-v8a libs, write the code below `#if defined(__aarch64__)`. If the game has both armeabi-v7a and arm64-v8a, save your time and delete arm64-v8a folder, only target on armv7. Don't worry, the game will still work on ARM64

We know we could do `#if defined(__arm__)` for ARMv7 and `#if defined(__i386__)` for x86, but we will leaving `#else`, so AS doesn't make that part greyed out. We will still using ARMv7 as a primary target

- `Changes`: Get values to apply mods. BE CAREFUL NOT TO ACCIDENTLY REMOVE break;

- `settingsList`: Settings assigned in negative numbers, we keep the positive numbers for mods. Works same as mod features but the call must be implemented in `localChanges(int featureNum, boolean toggle)` in `FloatingModMenuService.java`

- `getFeatureList`: Mod features

Assigning feature numbers is optional. Without it, it will automatically count for you, starting from 0

Assigned feature numbers can be like any numbers 1,3,200,10... instead in order 0,1,2,3,4,5...

Do not change or translate the first text unless you know what you are doing

Toggle, ButtonOnOff and Checkbox can be switched on by default, if you add `True_`. Example: `CheckBox_True_The Check Box`

To learn HTML, go to this page: https://www.w3schools.com/

Usage:

```cpp
(Optional feature number)_Toggle_(feature name)
(Optional feature number)_True_Toggle_(feature name)
(Optional feature number)_SeekBar_(feature name)_(min value)_(max value)
(Optional feature number)_Spinner_(feature name)_(Items e.g. item1,item2,item3)
(Optional feature number)_Button_(feature name)
(Optional feature number)_ButtonOnOff_(feature name)
(Optional feature number)_InputValue_(feature name)
(Optional feature number)_CheckBox_(feature name)
(Optional feature number)_RadioButton_(feature name)_(Items e.g. radio1,radio2,radio3)
RichTextView_(Text with limited HTML support)
RichWebView_(Full HTML support)
ButtonLink_(feature name)_(URL/Link here)
Category_(text)
```

To add a collapse, create a new instance
```cpp
Collapse_The collapse 1
```

Then you can add component views to collapse like

```cpp
CollapseAdd_Toggle_The toggle
123_CollapseAdd_Toggle_The toggle
CollapseAdd_Button_The button
```

#### KittyMemory patching usage:
```cpp
MemoryPatch::createWithHex([Lib Name], [offset], "[hex. With or without spaces]");
[Struct].get_CurrBytes().Modify();
[Struct].get_CurrBytes().Restore();

[Struct].get_TargetAddress();
[Struct].get_PatchSize();
[Struct].get_CurrBytes().c_str();

PATCHOFFSET("0x20D3A8", "00 00 A0 E3 1E FF 2F E1");
PATCHOFFSET_LIB("libFileB.so", "0x20D3A8", "00 00 A0 E3 1E FF 2F E1");
```

Example: https://github.com/MJx0/KittyMemory/blob/master/Android/test/src/main.cpp

Use an online ARM assembly converter like ARMConverter to convert ARM to HEX: https://armconverter.com/

#### Hook usage:
This macro works for both ARMv7 and ARM64. Make sure to use predefined macro `defined(__aarch64__)` and `defined(__arm__)` if you are targeting both archs

Strings for macros are automatically obfuscated. No need to obfuscate!
```cpp
HOOK("0x123456", FunctionExample, old_FunctionExample);
HOOK_LIB("libFileB.so", "0x123456", FunctionExample, old_FunctionExample);
HOOK_NO_ORIG("0x123456", FunctionExample);
HOOK_LIB_NO_ORIG("libFileC.so", "0x123456", FunctionExample);
HOOKSYM("__SymbolNameExample", FunctionExample, old_FunctionExample);
HOOKSYM_LIB("libFileB.so", "__SymbolNameExample", FunctionExample, old_FunctionExample);
HOOKSYM_NO_ORIG("__SymbolNameExample", FunctionExample);
HOOKSYM_LIB_NO_ORIG("libFileB.so", "__SymbolNameExample", FunctionExample);
```

Or

ARM64:
```cpp
A64HookFunction((void *) getAbsoluteAddress([Lib Name], [offset]), (void *)[function], (void **)&[old function]);
```

ARMv7/x86:
```cpp
MSHookFunction((void *) getAbsoluteAddress([Lib Name], [offset]), (void *)[function], (void **)&[old function]);
```

#### **Android.mk**

The make file for the c++ compiler. In that file, you can change the lib name on the `LOCAL_MODULE` line
When you change the lib name, change also on `System.loadLibrary("")` under OnCreate method on `MainActivity.java`
Both must have same name

# Testing

Connect your device to the computer or run your emulator. Android Studio will detect and you can click Play to run your app.

![](https://i.imgur.com/ZegjeM8.png)

On physical device, make sure you have USB-Debugging enabled in the developer option of your device. To make it visible, go to **Settings** > **About phone** and tap Build number seven times. Return to the previous screen to find Developer options at the bottom. The Developer options screen might be located or named differently on some devices

Sometimes Android Studio does not detect emulators such as NOX or MEMU fail to connect to adb automatically, reboot can help sometimes. Please refer to the support page.

# Implementing the menu to the target game

### 1. Know your game's main activity

Now we are looking for main activity, there are 2 ways to do

1. Decompile the game's APK file. Open `AndroidManifest.xml` and search after `<action android:name="android.intent.action.MAIN"/>`.

Example the game's main activity was `com.unity3d.player.UnityPlayerActivity`

![](https://i.imgur.com/FfOtc1K.png)

Be sure to enable Word wrap so it is easier to read

![](https://i.imgur.com/7DzU8d0.png)

2. APK Easy Tool since it can read out location of main activity without decompiling APK

![](https://i.imgur.com/JQdPjyZ.png)

Note it somewhere to remember it

### 2. Making corresponding changes in the files

Decompile the game APK

Open the game's `AndroidManifest.xml`

Add the `SYSTEM_ALERT_WINDOW` permission besides other permissions if it doesn't exist. Doesn't matter where you place it as long as it's above the application tag
```xml
<uses-permission android:name="android.permission.SYSTEM_ALERT_WINDOW"/>
```

If you don't add it, you can't allow overlay permission.

![](https://i.imgur.com/XOxLU91.png)

Add the service above the end of application tag (change the package name of your menu if you had changed it)
```xml
<service android:name="uk.lgl.modmenu.FloatingModMenuService" android:enabled="true" android:exported="false" android:stopWithTask="true"/>
```

![](https://i.imgur.com/rw0hawa.png)

Now we need to call your mod menu activity

There are 2 ways to call your mod menu activity. Choose one of them you like to try. Don't know? just choose METHOD 1

**METHOD 1**

This simple way, we will call to `MainActivity.java`. `MainActivity.java` will never be used

Locate to the game's path of main activity and open the **smali** file. If the game have multi dexes, it may be located in smali_classes2.. please check all

With the path of the target game’s main activity which we determined earlier `com.unity3d.player.UnityPlayerActivity`. Think of it like a path `/com/unity3d/player/UnityPlayerActivity.smali`

Open the main acitivity's smali file, search for OnCreate method and paste this code inside (change the package name if you had changed it)
```
invoke-static {p0}, Luk/lgl/MainActivity;->Start(Landroid/content/Context;)V
```
 
![](https://i.imgur.com/7CxTCl8.png)

Save the file

**METHOD 2**

You can follow this it if the first method really fails, or if you really want to use `MainActivity.java` for a reason. Since this involve changing activites, it may cause some problems.

On your `MainActivity.java`, put the game's main activity to `public String GameActivity`

![](https://i.imgur.com/jdacwvH.png)

Uncomment this code

```
Toast.makeText(MainActivity.this, "Error. Game's main activity does not exist", Toast.LENGTH_LONG).show();
```

On `AndroidManifest.xml`, remove `<action android:name="android.intent.action.MAIN"/>` from the game's activity, like this:

![](https://i.imgur.com/z1RxPjc.png)

If you don't remove `<action android:name="android.intent.action.MAIN"/>` from the game's activity, your menu will not launch. `AndroidManifest.xml` can ONLY contain one `<action android:name="android.intent.action.MAIN"/>`

near the end of application tag `</application>`, add your main activity above it. `uk.lgl.MainActivity` is your main activity

```xml
<activity android:configChanges="keyboardHidden|orientation|screenSize" android:name="uk.lgl.MainActivity">
     <intent-filter>
         <action android:name="android.intent.action.MAIN"/>
         <category android:name="android.intent.category.LAUNCHER"/>
     </intent-filter>
</activity>
```

![](https://i.imgur.com/33lMPhc.png)

Save the file

_Do NOT use both methods at the same time_

### 3. Building your project and copying files

Build the project to the APK file.
**Build** -> **Build Bundle(s)/APK(s)** -> **Build APK(s)**

If no errors occured, you did everything right and build will succeded. You will be notified that it build successfully

![](https://i.imgur.com/WpSKV1L.png)

Click on **locate** to show you the location of **build.apk**. It is stored at `(your-project)\app\build\outputs\apk\app-debug.apk`

![](https://i.imgur.com/wBTPSLi.png)

Decompile your **app-debug.apk**.

Copy your mod menu from decompiled app-debug.apk smali to the game's smali folder. Example ours is uk.lgl.modmenu, we copy the `uk` folder from **app-debug** `(app-debug\smali\uk)` to the game's decompiled directory `(game name)\smali`

![](https://i.imgur.com/aO6eEab.png)
 
If the game have multidexes, just add your smali to the last `smali_classes` if possible to prevent compilation errors such as `Unsigned short value out of range: xxxxx` (Smali limit error)

Copy the library file (.so) from **app-debug.apk** to the target game. Watch out the folder names, we don't want to mix them up, so make sure to copy our lib file to the correct architecture. Like our armeabi-v7a lib goes to the target games armeabi-v7a folder, arm64-v8a lib goes to the arm64-v8a folder...

PUTTING THE LIB FILE ON A WRONG ARCHITECTURE LIKE PUTTING ARM64 LIB TO ARMV7 WILL RESULT A CRASH!
 
![](https://i.imgur.com/oZq1Wq7.png)
 
### 4. Compiling game apk
 
Now compile and sign the apk, and install it on your device

Congrats. You have successfully implemented a mod menu.

Compile failed? read the log and look up on Google

If you face any problem, please read the [FAQ](#faq)

# Leeching concerns

Leeching as known as stealing code and offsets via reverse enginnering, and editing credits via file editing and recompiling. We all know that, right?

There are some simple protections in the template:
- Simple C++ string obfuscation called AY Obfuscator. Usage `OBFUSCATE("string here")` and with a key `OBFUSCATE_KEY("string here", 64-bit key here)`. Example `OBFUSCATE_KEY("Hello", 2353474243)` or in hex `OBFUSCATE_KEY("Hello", 0x3FE63DF21A3B)`. The key must not be too long or too short
- `string2Offset("")` to protect offsets
- Simple anti-leech measures that crashes if JNI functions are not called
- Quite harder to edit credits via smali
- Toast hidden inside `getFeatureList` in Main.cpp

These protection are NOT full protection, it does not stop them, it will only slow them down, this intent is to help you improve on your own by yourself. You should:
- Improve anti-leech measures on your own way
- Protect and encrypt your dex and lib. Find the tools or the projects by yourself, chinese based tools is not recommended as anti virus may flag your mod for malware (false positive). Don't tell anyone what protection you are using, don't let game developers get a hand of it
- Improve string obfuscators a lot more or use others which are not known. Make sure that obfuscator is not too simple
- Enable proguard, and add filters to make sure it does not break your project. See https://developer.android.com/studio/build/shrink-code
- Never share your project to someone
- Do not include any important stuff such as 'offline' username and password, instead add an additional layer, e.g. a web service handling the protected request
- And etc.

Never contact how to protect more, never complain that your mod has been leeched, that's all your responsibility! If you are really worry about leeching, or getting constantly leeched, and can't protect, just upload your project on Github. They will download from your Github instead leeching.

**Never tell us how to leech stuff, we are not interested getting involved in it, You will get blocked immediately!**

# FAQ
### My game crashing or freezing/My mod menu does not work
There are many many reasons why, it could be your code fault, wrong offsets, bad c++ code, bad layout implementations, game protections etc.

This is very hard to diagnose. Check logcat on Android Studio to see the error logs, open **Logcat** window from below, and select your device, process and filter to **Error**. Once you do, you can see the errors in logcat

![](https://i.imgur.com/cutKC29.png)

Error on Java side is really easy to spot, if an the error occured natively, a huge `CRASH` report will be logged but it can be hard to figure out. You would have to dig deeper and figure out yourself. Google it if possible.

If that caused by your hacks, check if your patches and hooks are correct. For hooks, write down the logs such as `LOGD("whatever");` like this below:

```cpp
bool get_BoolExample(void *instance) {
    LOGD("Bool step 1");
    if (instance != NULL && featureHookToggle) {
        LOGD("Bool step 2");
        return true;
    }
    LOGD("Bool step 3");
    return old_get_BoolExample(instance);
}
```

This can help you what part of your code faced the problem.

If you believe the game has protection, bypass it or drop it!

See more about logcat: https://developer.android.com/studio/debug/am-logcat

### I have a problem decompiling or compiling APK file
Search for the related issues on Google or on Apktool Github page: https://github.com/iBotPeaches/Apktool/issues

### I'm getting an error `Unsigned short value out of range: 65536` if I compile
The method index can't fit into an unsigned 16-bit value, means you have too many methods in the smali due to the limit 65535. Place your code on other classes, such as smali_classes2 instead. This work for Android 5 (Lollipop) and above only.

### I'm getting an error `ERROR: executing external native build for ndkBuild Android.mk. Affected Modules: app`
See: https://github.com/LGLTeam/Android-Studio-Solutions/wiki/Executing-external-native-build-for-ndkBuild-Android.mk

### I'm getting strange issues on Android Studio or Gradle
See: https://github.com/LGLTeam/Android-Studio-Solutions/wiki

### How to get older version of the template? or how to see updates/commits?

Go to the commit page https://github.com/LGLTeam/Android-Mod-Menu/commits/master

### Why can't you just add the feature I want? For example closing animation?

Also known as: "You're a developer after all — it shouldn't be that hard!"

Since we can't spend my days on it, we have to prioritize the features and fixes that are likely to benefit the larger number of people. Features that is specific to your usage is not going to benefit that many users after all. This is important that you do not expect that anyone can do everything for you. Developing *is* hard, and even outside of supporting a feature, adding the code can take longer than you think!

With all this being said, remember that this is 100% Open Source. So if you really want a specific feature, try to do it yourself, or ask someone who are willing to help you.

### Why can't you just help or teach me modding the game? For example, hooking?

Anything else, such as how to hook, how to patch, how to bypass, what functions to mod, how il2cpp works, etc. is out of scope. We will not cover anything and trivial stuff every other tutorial online already covers. Instead, try to find a couple of tutorials to learn and mod the game yourself. It's a lot easier than you think. If you can't, find a couple of forums where you can ask your questions or ask the right modder for specific special features

### When there is a new update? I have waited for so long time

There is no ETA, we only push a commit when we want to. Please don't ask the same question over and over again. You could make something better yourself without having to wait

# Reporting issues/Cоntact
<details>
<summary>Cоntact:</summary>
Please stop and read this carefully.

Make sure you have readed FAQ and at least searching for answers.

If you have usage problems, try asking your questions on any forum sites. For example, if you have an issue with hooking or patching, bypassing security, or wanna mod PUBG and Free Fire, you should go to the **forums**. Here there are no teachers, or who deal with such issues.

Beginner/newbie/noobs and toxic peoples are **NOT** allowed to cоntact. They are annoying, you would be left **unanswered** and possibly get **BLOCKED**. Known leechers will be instant **BLOCKED**

Issue tracker is permanently disabled

Tеlеgram: @ThеᒪGᒪ

Disсоrd: Deleted because its community has become more toxic, and its security are bad

You can find @ThеᒪGᒪ on some forum modding communities
</details>

# Credits/Acknowledgements
Thanks to the following individuals whose code helped me develop this mod menu

* Octowolve/Escanor - Mod menu: https://github.com/z3r0Sec/Substrate-Template-With-Mod-Menu and Hooking: https://github.com/z3r0Sec/Substrate-Hooking-Example
* VanHoevenTR - Mod menu - https://github.com/LGLTeam/VanHoevenTR_Android_Mod_Menu
* MrIkso - First mod menu template https://github.com/MrIkso/FloatingModMenu
* MJx0 A.K.A Ruit - https://github.com/MJx0/KittyMemory
* Rprop - https://github.com/Rprop/And64InlineHook
* And everyone else who provided input and contributions to this project!