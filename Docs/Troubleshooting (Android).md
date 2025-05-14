### My game is crashing or freezing
There are many many reasons why, it could be your code fault, wrong offsets, bad c++ code, bad layout implementations, game protections etc.

This is very hard to diagnose. Check logcat on Android Studio to see the error logs, open **Logcat** window from below, and select your device, process and filter to **Error**. Once you do, you can see the errors in logcat

![](https://i.imgur.com/cutKC29.png)

Error on Java side is really easy to spot, if an the error occured natively, a huge `CRASH` report will be logged but it can be hard to figure out. You would have to dig deeper and figure out yourself.

If that caused by your hacks, check if your patches and hooks are correct.

If you believe the game has protection, bypass it or drop it!

### AIDE Troubleshooting

Problem with the project like app crashes: click **More... -> Project -> Refresh Build**. This will clear the project cache and fix problems

Problem with AIDE: Open System Settings -> Apps and clear data of AIDE app. This will reset everything and you need to install NDK again

AIDE has a lot of compatibility issues, you need to research a lot and do some trial and errors until you fix something.