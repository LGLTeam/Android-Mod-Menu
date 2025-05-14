**This is for Android mobile users who do not have a PC. Floating apps or similar is recommended to read this page while working at the same time**

**BEST VIEWED ON MOBILE!**

# Quick links
- [Prerequisites](https://github.com/LGLTeam/Android-Mod-Menu/blob/master/README.md#prerequisites)
- [What you need](#what-you-need)
- [Video Tutorial](#video-tutorial)
- [Installation](#installation)
- [Setting up AIDE](#setting-up-aide)
- [Files to work with and making changes](#files-to-work-with-and-making-changes)
- [Implementing the menu to the target game](#implementing-the-menu-to-the-target-game)
- [FAQ](#faq)
- [Troubleshooting](#troubleshooting)
- [Credits/Acknowledgements](#creditsacknowledgements)

# What you need
* Modded AIDE app, choose one of them you like to use. The official AIDE from Play Store will not work with this project
    * [AIDE CMODs](https://secufiles.com/nE9J/AIDE_CMODs_3.2.200108.apk)
	* [AIDE Lite Mod](https://mega.nz/file/bIpCQL6I#BzyLf1pB1Sf7EayW_PEJHl3f50qHHZDdb0BpB8FYdVo)
* NDK support for modded AIDE
    * NDK for 32-bit/ARMv7 phones: [ndk_arm.tar.gz](https://mega.nz/folder/2c1TWIJD#UCzO7kIo1e4WpFwZHIMYVw/file/XRlRTIjJ)
    * NDK for 64-bit/ARM64 phones: [ndk_arm64.tar.gz](https://mega.nz/folder/2c1TWIJD#UCzO7kIo1e4WpFwZHIMYVw/file/7RdTzYxQ)
* Any File Manager app you like to use but these are recommended
    * [X-plore](https://play.google.com/store/apps/details?id=com.lonelycatgames.Xplore&hl=en): 
    * [MT Manager](https://bbs.binmt.cc/forum-2-1.html) [(Mirror link)](https://secufiles.com/js6i/MT2.9.2.apk) With build-in Apktool and editors to modify APK file. Note: It requires VIP to edit `AndroidManifest.xml` more than 200 lines
* Apktool app to edit `AndroidManifest.xml` for free: [Modded APK Editor Pro app](https://mega.nz/file/zQxA0YDY#eNRgcyrHwpWh1nSTHhcc4quxzeXrXcUHlYPoRyltKEw) or [APK Repacker](https://mega.nz/file/LIom0DDL#hJyIchPDCk2n_gcDmutNsOKS86WXQN58qpEGa9JsLrU) (We use APK Editor Pro)
* [Floating apps](https://play.google.com/store/apps/details?id=com.lwi.android.flappsfull&hl=en) (optional): You can use it to read this page and working at the same time or use a build-in feature by OEM

# Video Tutorial
Note: Videos may be quite outdated

Mahmoud Gaming: https://www.youtube.com/watch?v=SMCsUy60Hs8

NSRAÎNA HACKER: https://www.youtube.com/watch?v=MkkZ_loEDTU

BROKE MODS OFC (Customized menu): https://www.youtube.com/watch?v=IYREVGc-quM

# Installation

Go to releases page https://github.com/LGLTeam/Android-Mod-Menu/releases/ and download **Source code (zip)**

To download latest commit, enable desktop mode on your browser then click **Code**, and click **Download ZIP**

![](https://i.imgur.com/EZnbd10.png)

# Setting up AIDE

Now let's begin

Firstly, make sure you know your phone's hardware well, and download correct NDK file coresponding to your phone's architecture. ndk_arm.tar.gz for 32-bit/ARMv7 phones, ndk_arm64.tar.gz for 64-bit/ARM64 phones. Installing incorrect version will cause problems

Now install NDK support for modded AIDE. Click on 3 dots on the right-corner. Click **More... - Settings**

![](https://i.imgur.com/LyZMkK1.png)

Go to **Build & Run**, and click on **Manage native code support**.

![](https://images2.imgbox.com/6e/5c/DootVB4P_o.png)

A prompt will ask to input the path of NDK file.

If you use X-plore, you can show details of the file and copy file path easly.

![](https://images2.imgbox.com/54/2b/G0gVbhrN_o.png)

Paste it in the prompt box.

![](https://images2.imgbox.com/e1/c0/HSj9yQS9_o.png)

Click install and wait

![](https://images2.imgbox.com/1d/55/7LPXB7CI_o.png)

After installiation, you can now use AIDE with NDK support

# Opening project in AIDE

On the main screen, it says **No open files**. We simply click on **No open files** to show file explorer. Navigate to the directory of the project and open **app** folder

An option **Open Android app Project** will appear. Click on it to open

![](https://images2.imgbox.com/dc/7f/Jtq8ZEl1_o.png)

Now that the file explorer will look like this, means the project has been opened

![](https://images2.imgbox.com/2f/9a/EA0zZr8R_o.png)

Press play to compile the project whether it works or not

If successful, it will ask you to install the APK. It may ask you to allow installation from unknown sources. Please allow when asked

Open the app to test

# Files to work with and making changes

See more: https://github.com/LGLTeam/Android-Mod-Menu#files-to-work-with-and-making-changes

Important for 32-bit users: Please remove arm64-v8a from application.mk

# Implementing the menu to the target game

### 1. Exporting to APK

We need to compile the project into APK file

Click on 3 dots icon on the corner. **More... - Project - Publish project**

![](https://images2.imgbox.com/e3/2b/8uBsyDwe_o.png)

This dialog will show but why is export greyed? Because you need to create your own keystore first. Click **Create keystore**

![](https://images2.imgbox.com/ec/86/pQMmCpiN_o.png)

There is no need to put your organization info. Just your alias, password and name are fine. Don't forget your password!

After you created your keystore, you can now export

![](https://images2.imgbox.com/7c/4b/dkSUTXpx_o.png)

Enter your keystore password

![](https://images2.imgbox.com/3f/05/0Ois42P5_o.png)

After that, it will tell you the APK has been experted

![](https://images2.imgbox.com/4b/7b/GZuUcUOi_o.png)

### 2. Downloading standalone APK from apkcombo

It is not a good idea to pull out installed APK from phone because sometimes it comes with splitted APKs, it's a dumb feature, we should use Apkcombo to download standalone APK

Try to use armv7 standalone APK as possible. It support on all armv7, x86 and arm64 devices

https://apkcombo.com/

### 3. Know the game's main activity

We are looking for main activity. X-plore app can get main activity of the app so we will use that

Click **Show**, check **App manager**.

![](https://images2.imgbox.com/d9/f2/wFQs1Nwi_o.png)

Long press on an app and click **Show details**, then click **App** and expand **Activity**

Here we can see the main activity. It's always on top

![](https://images2.imgbox.com/fd/e4/CQFS4fJJ_o.png)

Note it down somewhere to remember it. We will explain this later

### 4. Adding dex and lib file

We will use MT Manager to modify APK. Edit the files inside APK is pretty much straight forward, we do not need to decompile the whole APK to storage at all.

Open the APK file. Click **View** to show its content

![](https://images2.imgbox.com/f6/6c/6xd8CxIa_o.png)

You will now see the content structure inside the APK

![](https://images2.imgbox.com/68/b6/ejdGhu1M_o.png)

Do the same on compiled mod menu APK on the other pane

We need to rename the dex on our mod menu APK to add dex into the game APK. We name it to classes2.dex since it contain only single dex. If the game have multiple dexes, like classes.dex, classes2.dex, classes3.dex, we would name it to classes4.dex. Mod menu dex must always be last

![](https://images2.imgbox.com/2d/f2/0ySkQexV_o.png)

Press and hold on our dex, and click **+ Add**. This dialog will show. Enable **Auto Sign**, leave Update mode **Replace All**

![](https://images2.imgbox.com/42/94/6awBaOeG_o.png)

Click OK, it will copy and auto sign.

Copy your library file (.so file) too. Make sure to copy to the correct architecture
armeabi-v7a is armeabi-v7a, arm64-v8a is arm64-v8a, and so on.

PUTTING THE .SO file ON A WRONG ARCHITECTURE WILL RESULT IN A CRASH!

![](https://images2.imgbox.com/34/93/NqI2kgOl_o.png)

### 5. Making corresponding changes and compile

Ok, we go back to the main directory inside APK. You can press **..** to go back

**I don't want to explain it here again, so please go to main README.md to read: https://github.com/LGLTeam/Android-Mod-Menu/blob/master/README.md#2-making-corresponding-changes-in-the-files**

**Editing DEX file using MT Manager**

Open `classes.dex` directly, choose **Dex Editor Plus**

![](https://images2.imgbox.com/d4/65/UlDjc5EY_o.png)

This dialog will show if it have multidex. **SELECT ALL** and click OK

![](https://images2.imgbox.com/c3/65/3vpID6Um_o.png)

The editor opens.

Make some changes. After you're done, save it

![](https://images2.imgbox.com/ad/7c/JyAKmAwA_o.png)

Go back and **save and exit**

![](https://images2.imgbox.com/f2/a3/x0V6dgjH_o.png)

Click OK to update the changes to the game's APK file with auto sign on

![](https://images2.imgbox.com/1a/5a/4Dw9YFv9_o.png)

Go back outside APK. You will now see a green text which tells you that you have recently modified the file

![](https://images2.imgbox.com/dc/c3/SX5pHGPj_o.png)

**Editing XML file using APK Editor Pro**

MT Manage requires an account to edit `AndroidManifest.xml` and VIP account to edit more than 200 lines. No, we don't need VIP, we will use APK Editor Pro to edit

Open APK Editor Pro, click "Select an Apk file". Navigate to the location where you have stored APK, and select it to edit

![](https://images2.imgbox.com/97/05/bIwx800E_o.png)

Open `AndroidManifest.xml`

![](https://images2.imgbox.com/01/11/eP695bXz_o.png)

Make some changes. After you're done, save it

![](https://images2.imgbox.com/e4/e5/CgmEHFof_o.png)

Go back, save the APK file

![](https://images2.imgbox.com/ca/4d/0zeGiS91_o.png)

Wait until it finish compiling. This screen will show after it's done. You can choose to install the APK right now. You may need to uninstall original APK first

![](https://images2.imgbox.com/30/3e/hNbeXhYr_o.png)

It's obvious that it saved an APK to the strange location `/storage/emulated/0/ApkEditor/tmp/gen_signed.apk`, just move it somewhere if you like to.

If it works, congratulations!

# Troubleshooting

Problem with the project like app crashes: click **More... -> Project -> Refresh Build**. This will clear the project cache and fix problems

Problem with AIDE: Open System Settings -> Apps and clear data of AIDE app. This will reset everything and you need to install NDK again

AIDE has a lot of compatibility issues, you need to research a lot and do some trial and errors until you fix something.

# FAQ

See: https://github.com/LGLTeam/Android-Mod-Menu#faq

# Credits/Acknowledgements

* RAUNAK MODS for help in modding games via phone, and testing the template in AIDE