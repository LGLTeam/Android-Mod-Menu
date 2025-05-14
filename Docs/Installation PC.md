# What you need
* Android Studio 4 and up: https://developer.android.com/studio
* NDK Installed via Android Studio, doesn't matter what version, minimim version required is 17 (Cmake is not needed) https://developer.android.com/studio/projects/install-ndk#default-version
* Apktool: [Apktool.jar](https://ibotpeaches.github.io/Apktool/) or any 3rd party tools
* [APK Easy Tool](https://forum.xda-developers.com/android/software-hacking/tool-apk-easy-tool-v1-02-windows-gui-t3333960). To get main activity: 
* Any text editor. We use [Notepad++](https://notepad-plus-plus.org/downloads/)
* Any png compression to compress your png file: We use https://compresspng.com/
* Any base64 encoding to encode your file: We use https://www.base64encode.org/
* ARM converter, to convert ARM instruction to hex: https://armconverter.com/

I don't know if these softwares are capable to run on other operating systems, like Linux and Mac. You may need to find alternative softwares

# Extract the project

After downloading project, extract it to your desired location. The location must **NOT** contain any spaces or symbols.

# Open the project

Ok, now run Android Studio and open the project you have just extracted

Please wait for a while, it will index and sync the project for the first time, takes around a minute depending your computer performance

If this is the first time you are using Android Studio, you may encounter an error you need to accept license to install recommended version of NDK. Please do it so

![](https://i.imgur.com/B0vsb3n.png)

After it's done, and no errors or strange bugs occured, you can start working!

# Testing the app

Connect your device to the computer or run your emulator. Android Studio will detect and you can click Play to run your app.

![](https://i.imgur.com/ZegjeM8.png)

On your physical device, make sure you have USB-Debugging enabled in the developer option of your device. To make it visible, go to **Settings** > **About phone** and tap Build number seven times. Return to the previous screen to find Developer options at the bottom. The Developer options screen might be located or named differently on some devices

Sometimes Android Studio does not detect emulators such as NOX or MEMU fail to connect to adb automatically, reboot can help sometimes. Please refer to the support page.