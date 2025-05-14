# 1. Know your game's main activity

Now we are looking for main activity

Decompile the game's APK file. Open `AndroidManifest.xml` and search after `<action android:name="android.intent.action.MAIN"/>`.

Example the game's main activity was `com.unity3d.player.UnityPlayerActivity`. Be sure to enable Word wrap so it is easier to read

![](https://i.imgur.com/FfOtc1K.png)

APK Easy Tool since it can read out location of main activity without decompiling APK

![](https://i.imgur.com/JQdPjyZ.png)

Note it somewhere to remember it. You can use any tools in your choice

# 2. Making corresponding changes

Decompile the game's APK

Now we need to launch your mod menu. There are 2 ways to launch your mod menu. First Method is recommended. 
Do NOT use both methods at the same time

## Method 1 - Launch from smali file

Locate to the game's path of main activity and open the **smali** file. If the game have multi dexes, it may be located in smali_classes2... please check all

With the path of the target game’s main activity which we determined earlier `com.unity3d.player.UnityPlayerActivity`. Think of it like a path `/com/unity3d/player/UnityPlayerActivity.smali`

### With overlay permission

Search for OnCreate method and paste this code inside

```
invoke-static {p0}, Lcom/android/support/Main;->Start(Landroid/content/Context;)V
```

![](https://i.imgur.com/TQy3jUY.png)

Open the game's `AndroidManifest.xml`

Add the `SYSTEM_ALERT_WINDOW` permission besides other permissions if it doesn't exist. Doesn't matter where you place it as long as it's above the application tag
```xml
<uses-permission android:name="android.permission.SYSTEM_ALERT_WINDOW"/>
```

![](https://i.imgur.com/XOxLU91.png)

If you don't add it, you can't enable overlay permission, it will be greyed out

Add the service above the end tag of application

```xml
<service android:name="com.android.support.Launcher" android:enabled="true"
    android:exported="false" android:stopWithTask="true" />
```

![](https://i.imgur.com/2Jjd8cY.png)


### Without overlay permission

**ONLY use if the game is detecting mod menu. Some games are using old AppCompat or custom activity that may interfere with the layout, such as enforced Kitkat-based layout like this below. I could not find a way to fix yet.**

![](https://i.imgur.com/tSKGGsy.png)

We can easly determite that this is an activity

![](https://i.imgur.com/iXQD6H6.png)

But what about this? It's an application context. Menu will not launch and asks for permission with switch greyed out.

![](https://i.imgur.com/APZytXN.png)

But if you are unsure, just give it a try.

Search for OnCreate method and paste this code inside

```
invoke-static {p0}, Lcom/android/support/Main;->StartWithoutPermission(Landroid/content/Context;)V
```
 
![](https://i.imgur.com/0KchOjz.png)

If menu is not showing up for some reason, or ask for permission. You need to add overlay permission. See above

## Method 2 - Launch from AndroidManifest.xml

This requires overlay permission. Only use if you really want to launch your own activity

On yout `MainActivity.java`, put the game's main activity to `public String GameActivity`

![](https://i.imgur.com/jdacwvH.png)

Uncomment this code

```
Toast.makeText(MainActivity.this, "Error. Game's main activity does not exist", Toast.LENGTH_LONG).show();
```

On `AndroidManifest.xml`, remove `<action android:name="android.intent.action.MAIN"/>` from the game's activity, like this:

![](https://i.imgur.com/z1RxPjc.png)

If you don't remove `<action android:name="android.intent.action.MAIN"/>` from the game's activity, your menu will not launch. `AndroidManifest.xml` can ONLY contain one `<action android:name="android.intent.action.MAIN"/>`

Add your activity tag. `com.android.support.MainActivity` is your main activity

```xml
<activity android:configChanges="keyboardHidden|orientation|screenSize"
    android:name="com.android.support.MainActivity" android:exported="true">
    <intent-filter>
        <action android:name="android.intent.action.MAIN" />
        <category android:name="android.intent.category.LAUNCHER" />
    </intent-filter>
</activity>
```

![](https://i.imgur.com/ZgbpTm8.png)

Add the `SYSTEM_ALERT_WINDOW` permission besides other permissions if it doesn't exist. Doesn't matter where you place it as long as it's above the application tag
```xml
<uses-permission android:name="android.permission.SYSTEM_ALERT_WINDOW"/>
```

![](https://i.imgur.com/XOxLU91.png)

If you don't add it, you can't enable overlay permission, it will be greyed out

Add the service above the end of application tag (change the package name of your menu if you had changed it)

```xml
<service android:name="com.android.support.Launcher" android:enabled="true"
    android:exported="false" android:stopWithTask="true" />
```

![](https://i.imgur.com/2Jjd8cY.png)

# 3. Building your project and copying files

Build the project to the APK file.
**Build** -> **Build Bundle(s)/APK(s)** -> **Build APK(s)**

If no errors occured, you did everything right and build will succeded. You will be notified that it has built successfully

![](https://i.imgur.com/WpSKV1L.png)

Click on **locate** to show you the location of **build.apk**. It is stored at `(your-project)\app\build\outputs\apk\app-debug.apk`

![](https://i.imgur.com/wBTPSLi.png)

Decompile your **app-debug.apk**.

Copy your mod menu from decompiled app-debug.apk smali to the game's smali folder. Example ours is com.android.support.Menu, we copy the `com` folder from **app-debug** `(decompiled app-debug\smali\com)` to the game's decompiled directory `(decompiled game)\(any smali folder)`

![](https://i.imgur.com/lU3Ne9l.png)
 
If the game have multidexes, just add your smali to the last `smali_classes` if possible to prevent compilation smali limit error `Unsigned short value out of range: xxxxx`

Copy the library file (.so) from **app-debug.apk** to the target game. Watch out the folder names, we don't want to mix them up, so make sure to copy our lib file to the correct architecture. Like our armeabi-v7a lib goes to the target games armeabi-v7a folder, arm64-v8a lib goes to the arm64-v8a folder...

PUTTING THE LIB FILE ON A WRONG ARCHITECTURE LIKE PUTTING ARM64 LIB TO ARMV7 WILL RESULT A CRASH!
 
![](https://i.imgur.com/PXA7dUt.png)
 
# 4. Compiling game apk
 
Now compile and sign the apk, and install it on your device

Congrats. You have successfully implemented a mod menu.
