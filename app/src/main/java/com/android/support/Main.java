package com.android.support;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.net.Uri;
import android.os.Build;
import android.provider.Settings;
import android.widget.Toast;

public class Main {

    //Load lib
    static {
        // When you change the lib name, change also on Android.mk file
        // Both must have same name
        System.loadLibrary("MyLibName");
    }

    public static void StartWithoutPermission(Context context) {
        CrashHandler.init(context);
        if (context instanceof Activity) {
            //Check if context is an Activity.
            Menu menu = new Menu(context);
            menu.SetWindowManagerActivity();
            menu.ShowMenu();
        } else {
            Toast.makeText(context, "Failed to launch the mod menu\n", Toast.LENGTH_LONG).show();
        }
    }

    public static void Start(Context context) {
        CrashHandler.init(context);
        if (Build.VERSION.SDK_INT >= 23 && !Settings.canDrawOverlays(context)) {
            boolean overlay_toast_shown = Preferences.with(context).readBoolean(-7, false);
            if (!overlay_toast_shown) {
                Preferences.with(context).writeBoolean(-7, true);
                Toast.makeText(context, "Overlay permission is required in order to show mod menu.", Toast.LENGTH_LONG).show();
                Intent intent = new Intent(Settings.ACTION_MANAGE_OVERLAY_PERMISSION,
                        Uri.parse("package:" + context.getPackageName()));
                context.startActivity(intent);
            }
            StartWithoutPermission(context);
            return;
        }
        try {
            Intent intent = new Intent(context, Launcher.class);
            context.startService(intent);
        } catch (Exception e) {
            StartWithoutPermission(context);
        }
    }
}