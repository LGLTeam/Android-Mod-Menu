package com.android.support;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.net.Uri;
import android.os.Build;
import android.os.Handler;
import android.provider.Settings;
import android.widget.Toast;

public class Main {

    //Load lib
    static {
        // When you change the lib name, change also on Android.mk file
        // Both must have same name
        System.loadLibrary("MyLibName");
    }

    private static native void CheckOverlayPermission(Context context);

    public static void StartWithoutPermission(Context context) {
        CrashHandler.init(context, true);
        if (context instanceof Activity) {
            //Check if context is an Activity.
            Menu menu = new Menu(context);
            menu.SetWindowManagerActivity();
            menu.ShowMenu();
        } else {
            //Anything else, ask for permission
            CheckOverlayPermission(context);
        }
    }

    public static void Start(Context context) {
        CrashHandler.init(context, false);

        CheckOverlayPermission(context);
    }
}
