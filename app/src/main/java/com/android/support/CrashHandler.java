//Credit: Raunak Mods - https://t.me/raunakmods786

package com.android.support;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.Application;
import android.content.ActivityNotFoundException;
import android.content.ClipData;
import android.content.ClipboardManager;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.res.Resources;
import android.os.Build;
import android.os.Bundle;
import android.text.Html;
import android.text.InputFilter;
import android.text.InputType;
import android.text.TextUtils;
import android.text.method.DigitsKeyListener;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.view.inputmethod.InputMethodManager;
import android.widget.EditText;
import android.widget.HorizontalScrollView;
import android.widget.LinearLayout;
import android.widget.ScrollView;
import android.widget.TextView;
import android.widget.Toast;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.PrintWriter;
import java.io.StringWriter;
import java.lang.Thread.UncaughtExceptionHandler;
import java.text.SimpleDateFormat;
import java.util.Date;

public final class CrashHandler {

    public static final UncaughtExceptionHandler DEFAULT_UNCAUGHT_EXCEPTION_HANDLER = Thread.getDefaultUncaughtExceptionHandler();

    public static void init(final Context app, final boolean overlayRequired) {
        Thread.setDefaultUncaughtExceptionHandler(new Thread.UncaughtExceptionHandler() {

            @Override
            public void uncaughtException(Thread thread, Throwable throwable) {
                Log.e("AppCrash", "Error just lunched ");
                try {
                    tryUncaughtException(thread, throwable);
                } catch (Throwable e) {
                    e.printStackTrace();
                    if (DEFAULT_UNCAUGHT_EXCEPTION_HANDLER != null)
                        DEFAULT_UNCAUGHT_EXCEPTION_HANDLER.uncaughtException(thread, throwable);
                    else
                        System.exit(2);
                }
            }

            private void tryUncaughtException(Thread thread, Throwable throwable) {
                Log.e("AppCrash", "Try saving log");

                final String time = new SimpleDateFormat("yyyy_MM_dd-HH_mm_ss").format(new Date());
                String fileName = "mod_menu_crash_" + time + ".txt";
                String dirName;

                if (Build.VERSION.SDK_INT >= 30) { //Android R. AIDE didn't support Build.VERSION_CODES.R
                    dirName = "/storage/emulated/0/Documents/";
                } else {
                    dirName = String.valueOf(app.getExternalFilesDir(null));
                }

                File crashFile = new File(dirName, fileName);

                String versionName = "unknown";
                long versionCode = 0;
                try {
                    PackageInfo packageInfo = app.getPackageManager().getPackageInfo(app.getPackageName(), 0);
                    versionName = packageInfo.versionName;
                    versionCode = Build.VERSION.SDK_INT >= 28 ? packageInfo.getLongVersionCode()
                            : packageInfo.versionCode;
                } catch (PackageManager.NameNotFoundException ignored) {
                }

                String fullStackTrace;
                {
                    StringWriter sw = new StringWriter();
                    PrintWriter pw = new PrintWriter(sw);
                    throwable.printStackTrace(pw);
                    fullStackTrace = sw.toString();
                    pw.close();
                }

                StringBuilder devInfo = new StringBuilder();
                devInfo.append("************* Crash Head ****************\n");
                devInfo.append("Time Of Crash      : ").append(time).append("\n");
                devInfo.append("Device Manufacturer: ").append(Build.MANUFACTURER).append("\n");
                devInfo.append("Device Model       : ").append(Build.MODEL).append("\n");
                devInfo.append("Android Version    : ").append(Build.VERSION.RELEASE).append("\n");
                devInfo.append("Android SDK        : ").append(Build.VERSION.SDK_INT).append("\n");
                devInfo.append("App VersionName    : ").append(versionName).append("\n");
                devInfo.append("App VersionCode    : ").append(versionCode).append("\n");
                devInfo.append("************* Crash Head ****************\n");
                devInfo.append("\n").append(fullStackTrace);

                String errorLog = devInfo.toString();

                try {
                    writeFile(crashFile, errorLog);
                } catch (IOException ignored) {
                }

                Toast.makeText(app, "Game has crashed unexpectedly", Toast.LENGTH_LONG).show();
                Toast.makeText(app, "Log saved to: " + String.valueOf(crashFile).replace("/storage/emulated/0/", ""), Toast.LENGTH_LONG).show();

                Log.e("AppCrash", "Done");

                System.exit(2);
            }

            private void writeFile(File file, String content) throws IOException {
                File parentFile = file.getParentFile();
                if (parentFile != null && !parentFile.exists()) {
                    parentFile.mkdirs();
                }
                file.createNewFile();
                FileOutputStream fos = new FileOutputStream(file);
                fos.write(content.getBytes());
                try {
                    fos.close();
                } catch (IOException e) {
                }
            }
        });
    }
}

