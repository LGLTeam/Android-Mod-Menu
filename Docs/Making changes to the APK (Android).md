**BEST VIEWED ON MOBILE!**

**Some screenshots are from my PC. You do not need to worry about it**

## 1. Exporting to APK

We need to compile the menu project into APK file

Click on 3 dots icon on the corner. **More... - Project - Publish project**

![](https://i.imgur.com/8N5waMf.png)

This dialog will show but why is export greyed? Because you need to create your own keystore first. Click **Create keystore**

![](https://i.imgur.com/a5GC1v5.png)

There is no need to put your organization info. Just your alias, password and name are fine. Don't forget your password!

After you created your keystore, you can now export

![](https://i.imgur.com/lM0Eto4.png)

Enter your keystore password

![](https://i.imgur.com/gpS1hr1.png)

The APK will be exported

![](https://i.imgur.com/oeWcN8w.png)

## 2. Downloading standalone APK from apkcombo

It is not a good idea to pull out installed APK from the phone because sometimes it comes with splitted APKs (Android App Bundle), we should use Apkcombo to download standalone APK

Try to use armv7 standalone APK as possible. It support on all devices universally

https://conggame.co/apk-downloader/

Put package name of the game, and choose Architecture, you will get standalone APK

## 3. Know the game's main activity

We are looking for main activity. X-plore app can get main activity of the app so we will use that

Click **Show**, check **App manager**.

![](https://i.imgur.com/aMPOyvN.png)

Long press on an app and click **Show details**, then click **App** and expand **Activity**

Here we can see the main activity. It's always on top

![](https://i.imgur.com/7rjwMGp.png)

Note it down somewhere to remember it. We will explain this later

## 4. Adding dex and lib file

We will use MT Manager to modify APK. Edit the files inside APK is pretty much straight forward, we do not need to decompile the whole APK to storage at all.

Open the APK file. Click **View** to show its content

![](https://i.imgur.com/WE4BNo5.png)

You will now see the content structure inside the APK

![](https://i.imgur.com/A1B8wmH.png)

Do the same on compiled mod menu APK on the other pane

We need to rename the dex on our mod menu APK to add dex into the game APK. We name it to classes2.dex since it contain only single dex. Dex of mod menu must always be last. Example, if the game have 3 dexes, like classes.dex, classes2.dex, classes3.dex, we would name it to classes4.dex.

![](https://i.imgur.com/oO55UNL.png)

Press and hold on our dex, and click **+ Add**. This dialog will show. Enable **Auto Sign**, leave Update mode **Replace All**

![](https://i.imgur.com/l9LJ2I8.png)

Click OK, it will copy and auto sign.

Copy your library file (.so file) too. Make sure to copy to the correct architecture
armeabi-v7a is armeabi-v7a, arm64-v8a is arm64-v8a, and so on.

PUTTING THE .SO file ON A WRONG ARCHITECTURE WILL RESULT IN A CRASH!

![](https://i.imgur.com/nQUq3wT.png)

## 5. Making corresponding changes

**We CANNOT cover steps for every Apktools for Android. You need to refer to help and support or online tutorial of the App**

Ok, we go back to the main directory inside APK. You can press **..** to go back

Use any Apktool of your choice and open AndroidManifest.xml from APK file. Since we don't have VIP account of MT Manager, we used APK Editor Pro to edit xml.

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

After you're done, save the change and sign the APK

If it works, congratulations!