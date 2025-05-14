package uk.lgl.modmenu;

import android.content.Context;
import android.os.Build;
import android.util.Log;
import android.widget.Toast;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;

public class Logcat {
    public static void Clear(Context context) {
        try {
            Runtime.getRuntime().exec("logcat -c");
            Toast.makeText(context, "Logcat cleared", Toast.LENGTH_LONG).show();
        } catch (IOException e) {
            Toast.makeText(context, "There was an error saving logcat to file", Toast.LENGTH_LONG).show();
            e.printStackTrace();
        }
    }

    public static void Save(Context context) {
        File path = null;
        try {
            Process process = Runtime.getRuntime().exec("logcat -d");
            BufferedReader bufferedReader = new BufferedReader(
                    new InputStreamReader(process.getInputStream()));

            StringBuilder log = new StringBuilder();
            String line = "";
            while ((line = bufferedReader.readLine()) != null) {
                log.append(line + "\n");
            }
            long unixTime = System.currentTimeMillis() / 1000L;
            if (Build.VERSION.SDK_INT >= 30) { //Android R. AIDE didn't support Build.VERSION_CODES.R
                path = new File("/storage/emulated/0/Documents/");
            } else {
                path = new File(context.getExternalFilesDir(null) + "/Mod Menu");
            }

            File folder = new File(String.valueOf(path));
            folder.mkdirs();

            File file = new File(path + "/Mod menu log - " + context.getPackageName() + ".txt");
            file.createNewFile();

            try {
                //BufferedWriter for performance, true to set append to file flag
                BufferedWriter buf = new BufferedWriter(new FileWriter(file));
                buf.append(log.toString());
                buf.newLine();
                buf.close();
                Toast.makeText(context, "Logcat saved successfully to: " + file.toString(), Toast.LENGTH_LONG).show();
                Toast.makeText(context, "Logcat saved successfully to: " + file.toString(), Toast.LENGTH_LONG).show();
            } catch (IOException e) {
                Toast.makeText(context, "There was an error saving logcat to file: " + e.getLocalizedMessage(), Toast.LENGTH_LONG).show();
                e.printStackTrace();
            }
        } catch (IOException e) {
            Toast.makeText(context, "There was an error saving logcat to file: " + Log.getStackTraceString(e), Toast.LENGTH_LONG).show();
            e.printStackTrace();
        }
    }
}
