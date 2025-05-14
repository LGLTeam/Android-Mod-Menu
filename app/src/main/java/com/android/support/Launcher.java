package com.android.support;

import android.app.ActivityManager;
import android.app.Service;
import android.content.Intent;
import android.os.Handler;
import android.os.IBinder;
import android.view.View;

public class Launcher extends Service {

    Menu menu;

    //When this Class is called the code in this function will be executed
    @Override
    public void onCreate() {
        super.onCreate();

        menu = new Menu(this);
        menu.SetWindowManagerWindowService();
        menu.ShowMenu();

        //Create a handler for this Class
        final Handler handler = new Handler();
        handler.post(new Runnable() {
            public void run() {
               Thread();
                handler.postDelayed(this, 1000);
            }
        });
    }

    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }

    //Check if we are still in the game. If now our menu and menu button will dissapear
    private boolean isNotInGame() {
        ActivityManager.RunningAppProcessInfo runningAppProcessInfo = new ActivityManager.RunningAppProcessInfo();
        ActivityManager.getMyMemoryState(runningAppProcessInfo);
        return runningAppProcessInfo.importance != 100;
    }

    private void Thread() {
        if (isNotInGame()) {
            menu.setVisibility(View.INVISIBLE);
        } else {
            menu.setVisibility(View.VISIBLE);
        }
    }

    //Destroy our View
    public void onDestroy() {
        super.onDestroy();
        menu.onDestroy();
    }

    //Same as above so it wont crash in the background and therefore use alot of Battery life
    public void onTaskRemoved(Intent intent) {
        super.onTaskRemoved(intent);
        try {
            Thread.sleep(100);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        stopSelf();
    }

    //Override our Start Command so the Service doesnt try to recreate itself when the App is closed
    public int onStartCommand(Intent intent, int i, int i2) {
        return Service.START_NOT_STICKY;
    }
}
