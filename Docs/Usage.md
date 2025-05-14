Important for 32-bit mobile users: Please remove arm64-v8a from application.mk

#### **jni/Menu/Menu.h**

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

It has a macro to detect if the ARM architecture is 32-bit or 64-bit on compile-time, it's to avoid using wrong offsets, like using ARMv7 offsets on an ARM64 lib. Check the game's APK what libs it contains before you proceed. If you want to target armeabi-v7a lib, write the code below `#else`. If you want to target arm64-v8a libs, write the code below `#if defined(__aarch64__)`. If the game has both armeabi-v7a and arm64-v8a, save your time and delete arm64-v8a folder. Armv7 will work universally

We know we could do `#if defined(__arm__)` for ARMv7 and `#if defined(__i386__)` for x86, but we will leaving `#else`, so Android Studio doesn't make that part greyed out. We will still using ARMv7 as a primary target

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

//Example
hexPatches.GodMode = MemoryPatch::createWithHex(targetLibName, string2Offset(OBFUSCATE("0x123456")), OBFUSCATE("00 00 80 D2 C0 03 5F D6"));
hexPatches.GodMode.Modify();
hexPatches.GodMode.Restore();
```

```cpp
// Patching offsets directly. Strings are automatically obfuscated!
PATCH("libFileB.so", "0x20D3A8", "00 00 A0 E3 1E FF 2F E1");
PATCH_SYM("_SymbolExample", "00 00 A0 E3 1E FF 2F E1");

//Switchable patches
PATCH_SWITCH("libil2cpp.so", "0x200000", "00 00 A0 E3 1E FF 2F E1", boolean);;
PATCH_SYM_SWITCH("libNativeGame.so", "_SymbolExample", "00 00 A0 E3 1E FF 2F E1", boolean);

//Restore patched offset to original
RESTORE("libil2cpp.so", "0x400000");
RESTORE_SYM("libil2cpp.so", "_SymbolExample");
```

Example: https://github.com/MJx0/KittyMemory/blob/master/Android/test/src/main.cpp

Use an online ARM assembly converter like ARMConverter to convert ARM to HEX: https://armconverter.com/

#### Hook usage:
This macro works for both ARMv7 and ARM64. Make sure to use predefined macro `defined(__aarch64__)` and `defined(__arm__)` if you are targeting both archs

Strings for macros are automatically obfuscated. No need to obfuscate!
```cpp
HOOK("libFileB.so", "0x123456", FunctionExample, old_FunctionExample);
HOOK_NO_ORIG("libFileC.so", "0x123456", FunctionExample);
HOOKSYM("libFileB.so", "__SymbolNameExample", FunctionExample, old_FunctionExample);
HOOKSYM_NO_ORIG("libFileB.so", "__SymbolNameExample", FunctionExample);
```
