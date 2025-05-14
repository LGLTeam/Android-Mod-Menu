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

### Why is issues disabled on this Github repo?
Issues are disabled permanently due to peoples who have no mind (mostly newbies) aren't even able to fill proper issue templates nor are they able to read the instructions. I get so many useless issues, even useless pull-requests.

As a result, the contact infomation has been removed as well. However you can still find me in our Telegram channel

### Why can't you just add the feature I want? For example closing animation?

Also known as: "You're a developer after all — it shouldn't be that hard!"

Since we can't spend my days on it, we have to prioritize the features and fixes that are likely to benefit the larger number of people. Features that is specific to your usage is not going to benefit that many users after all. This is important that you do not expect that anyone can do everything for you. Developing *is* hard, and even outside of supporting a feature, adding the code can take longer than you think!

With all this being said, remember that this is 100% Open Source. So if you really want a specific feature, try to do it yourself, or ask someone who are willing to help you.

### Why can't you just help or teach me modding the game? For example, hooking?

Anything else, such as how to hook, how to patch, how to bypass, what functions to mod, how il2cpp works, etc. is out of scope. We will not cover anything and trivial stuff every other tutorial online already covers. Instead, try to find a couple of tutorials to learn and mod the game yourself. It's a lot easier than you think. If you can't, find a couple of forums where you can ask your questions or ask the right modder for specific special features

### When there is a new update? I have waited for so long time!!!

There is no ETA, never. Stop crying! We will only update when we want to. Please don't ask the same question over and over again. Try make something better yourself without having to wait

### I'm a bit concerned about someone leeching my mod. Does this project offset protections?

Yes, there are simple protections in the template:
- Simple C++ string obfuscation called AY Obfuscator. Usage `OBFUSCATE("string here")` and with a key `OBFUSCATE_KEY("string here", 64-bit key here)`. Example `OBFUSCATE_KEY("Hello", 2353474243)` or in hex `OBFUSCATE_KEY("Hello", 0x3FE63DF21A3B)`. The key must not be too long or too short
- `string2Offset("")` to protect offsets
- Simple anti-leech measures that crashes if JNI functions are not called
- Quite harder to edit credits via smali
- Toast hidden inside `getFeatureList` in Main.cpp
- JNI functions hidden

You should always keep in mind it's impossible stop leechers, this intent is to help you improve on your own by yourself. You should:
- Improve anti-leech measures on your own way
- Protect and encrypt your dex and lib. Find the tools or the projects by yourself, chinese based tools is not recommended as anti virus may flag your mod for malware (false positive). Don't tell anyone what protection you are using, don't let game developers get a hand of it
- Improve string obfuscators a lot more or use others which are not known. Make sure that obfuscator is not too simple
- Enable proguard, and add filters to make sure it does not break your project. See https://developer.android.com/studio/build/shrink-code
- Never share your project to someone
- Do not include any important stuff such as 'offline' username and password, instead add an additional layer, e.g. a web service handling the protected request
- And more

If you are really worry about leeching, getting constantly leeched, and no more option to protect, then the only option is to upload your source on Github. They will download from your Github instead trying to leech.
