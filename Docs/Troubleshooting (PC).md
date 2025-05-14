### My game is crashing or freezing
There are many many reasons why, it could be your code fault, wrong offsets, bad c++ code, bad layout implementations, game protections etc.

This is very hard to diagnose. Check logcat on Android Studio to see the error logs, open **Logcat** window from below, and select your device, process and filter to **Error**. Once you do, you can see the errors in logcat

![](https://i.imgur.com/cutKC29.png)

Error on Java side is really easy to spot, if an the error occured natively, a huge `CRASH` report will be logged but it can be hard to figure out. You would have to dig deeper and figure out yourself.

If that caused by your hacks, check if your patches and hooks are correct. If you want quick debug, write down the logs such as `LOGD("whatever");` anywhere like this below:

```cpp
bool get_BoolExample(void *instance) {
    LOGD("Bool step 1");
    if (instance != NULL && featureHookToggle) {
        LOGD("Bool step 2");
        return true;
    }
    LOGD("Bool step 3");
    return old_get_BoolExample(instance);
}
```

This can help you what part of your code faced the problem.

If you believe the game has protection, bypass it or drop it!

See more about logcat: https://developer.android.com/studio/debug/am-logcat

### Android Studio Troubleshooting

To clear Android Studio's cache and bring it out of its state of confusion, select **Build** and then click the **Clean project** 

![](https://i.imgur.com/xBnI4ch.png)

Select **File > Invalidate Caches / Restart** and then click the **Invalidate and Restart** button.

![](https://i.imgur.com/xzmqlsM.png)