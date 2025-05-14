package com.android.support;

import android.annotation.TargetApi;
import android.content.Context;
import android.content.SharedPreferences;
import android.os.Build;

import java.util.LinkedHashSet;
import java.util.Set;

public class Preferences {
    private static SharedPreferences sharedPreferences;
    private static Preferences prefsInstance;
    public static Context context;
    public static boolean loadPref, isExpanded;

    private static final String LENGTH = "_length";
    private static final String DEFAULT_STRING_VALUE = "";
    private static final int DEFAULT_INT_VALUE = 0; //-1
    private static final double DEFAULT_DOUBLE_VALUE = 0d; //-1d
    private static final float DEFAULT_FLOAT_VALUE = 0f; //-1f
    private static final long DEFAULT_LONG_VALUE = 0L; //-1L
    private static final boolean DEFAULT_BOOLEAN_VALUE = false;

    public static native void Changes(Context con, int fNum, String fName, int i, boolean bool, String str);

    public static void changeFeatureInt(String featureName, int featureNum, int value) {
        Preferences.with(context).writeInt(featureNum, value);
        Changes(context, featureNum, featureName, value, false, null);
    }

    public static void changeFeatureString(String featureName, int featureNum, String str) {
        Preferences.with(context).writeString(featureNum, str);
        Changes(context, featureNum, featureName, 0, false, str);
    }

    public static void changeFeatureBool(String featureName, int featureNum, boolean bool) {
        Preferences.with(context).writeBoolean(featureNum, bool);
        Changes(context, featureNum, featureName, 0, bool, null);
    }

    public static int loadPrefInt(String featureName, int featureNum) {
        if (loadPref) {
            int i = Preferences.with(context).readInt(featureNum);
            Changes(context, featureNum, featureName, i, false, null);
            return i;
        }
        return 0;
    }

    public static boolean loadPrefBool(String featureName, int featureNum, boolean bDef) {
        boolean bool = Preferences.with(context).readBoolean(featureNum, bDef);
        if (featureNum == -1) {
            loadPref = bool;
        }
        if (featureNum == -3) {
            isExpanded = bool;
        }
        if (loadPref || featureNum < 0) {
            bDef = bool;
        }

        Changes(context, featureNum, featureName, 0, bDef, null);
        return bDef;
    }

    public static String loadPrefString(String featureName, int featureNum) {
        if (loadPref || featureNum <= 0) {
            String str = Preferences.with(context).readString(featureNum);
            Changes(context, featureNum, featureName, 0, false, str);
            return str;
        }
        return "";
    }

    private Preferences(Context context) {
        sharedPreferences = context.getApplicationContext().getSharedPreferences(
                context.getPackageName() + "_preferences",
                Context.MODE_PRIVATE
        );
    }

    private Preferences(Context context, String preferencesName) {
        sharedPreferences = context.getApplicationContext().getSharedPreferences(
                preferencesName,
                Context.MODE_PRIVATE
        );
    }

    /**
     * @param context
     * @return Returns a 'Preferences' instance
     */
    public static Preferences with(Context context) {
        if (prefsInstance == null) {
            prefsInstance = new Preferences(context);
        }
        return prefsInstance;
    }

    /**
     * @param context
     * @param forceInstantiation
     * @return Returns a 'Preferences' instance
     */
    public static Preferences with(Context context, boolean forceInstantiation) {
        if (forceInstantiation) {
            prefsInstance = new Preferences(context);
        }
        return prefsInstance;
    }

    /**
     * @param context
     * @param preferencesName
     * @return Returns a 'Preferences' instance
     */
    public static Preferences with(Context context, String preferencesName) {
        if (prefsInstance == null) {
            prefsInstance = new Preferences(context, preferencesName);
        }
        return prefsInstance;
    }

    /**
     * @param context
     * @param preferencesName
     * @param forceInstantiation
     * @return Returns a 'Preferences' instance
     */
    public static Preferences with(Context context, String preferencesName,
                                   boolean forceInstantiation) {
        if (forceInstantiation) {
            prefsInstance = new Preferences(context, preferencesName);
        }
        return prefsInstance;
    }

    // String related methods

    /**
     * @param what
     * @return Returns the stored value of 'what'
     */
    public String readString(String what) {
        return sharedPreferences.getString(what, DEFAULT_STRING_VALUE);
    }

    /**
     * @param what
     * @return Returns the stored value of 'what'
     */
    public String readString(int what) {
        try {
            return sharedPreferences.getString(String.valueOf(what), DEFAULT_STRING_VALUE);
        } catch (java.lang.ClassCastException ex) {
            return "";
        }
    }

    /**
     * @param what
     * @param defaultString
     * @return Returns the stored value of 'what'
     */
    public String readString(String what, String defaultString) {
        return sharedPreferences.getString(what, defaultString);
    }

    /**
     * @param where
     * @param what
     */
    public void writeString(String where, String what) {
        sharedPreferences.edit().putString(where, what).apply();
    }

    /**
     * @param where
     * @param what
     */
    public void writeString(int where, String what) {
        sharedPreferences.edit().putString(String.valueOf(where), what).apply();
    }

    // int related methods

    /**
     * @param what
     * @return Returns the stored value of 'what'
     */
    public int readInt(String what) {
        return sharedPreferences.getInt(what, DEFAULT_INT_VALUE);
    }


    /**
     * @param what
     * @return Returns the stored value of 'what'
     */
    public int readInt(int what) {
        try {
            return sharedPreferences.getInt(String.valueOf(what), DEFAULT_INT_VALUE);
        } catch (java.lang.ClassCastException ex) {
            return 0;
        }
    }

    /**
     * @param what
     * @param defaultInt
     * @return Returns the stored value of 'what'
     */
    public int readInt(String what, int defaultInt) {
        return sharedPreferences.getInt(what, defaultInt);
    }

    /**
     * @param where
     * @param what
     */
    public void writeInt(String where, int what) {
        sharedPreferences.edit().putInt(where, what).apply();
    }

    /**
     * @param where
     * @param what
     */
    public void writeInt(int where, int what) {
        sharedPreferences.edit().putInt(String.valueOf(where), what).apply();
    }

    // double related methods

    /**
     * @param what
     * @return Returns the stored value of 'what'
     */
    public double readDouble(String what) {
        if (!contains(what))
            return DEFAULT_DOUBLE_VALUE;
        return Double.longBitsToDouble(readLong(what));
    }

    /**
     * @param what
     * @param defaultDouble
     * @return Returns the stored value of 'what'
     */
    public double readDouble(String what, double defaultDouble) {
        if (!contains(what))
            return defaultDouble;
        return Double.longBitsToDouble(readLong(what));
    }

    /**
     * @param where
     * @param what
     */
    public void writeDouble(String where, double what) {
        writeLong(where, Double.doubleToRawLongBits(what));
    }

    // float related methods

    /**
     * @param what
     * @return Returns the stored value of 'what'
     */
    public float readFloat(String what) {
        return sharedPreferences.getFloat(what, DEFAULT_FLOAT_VALUE);
    }

    /**
     * @param what
     * @param defaultFloat
     * @return Returns the stored value of 'what'
     */
    public float readFloat(String what, float defaultFloat) {
        return sharedPreferences.getFloat(what, defaultFloat);
    }

    /**
     * @param where
     * @param what
     */
    public void writeFloat(String where, float what) {
        sharedPreferences.edit().putFloat(where, what).apply();
    }

    // long related methods

    /**
     * @param what
     * @return Returns the stored value of 'what'
     */
    public long readLong(String what) {
        return sharedPreferences.getLong(what, DEFAULT_LONG_VALUE);
    }

    /**
     * @param what
     * @param defaultLong
     * @return Returns the stored value of 'what'
     */
    public long readLong(String what, long defaultLong) {
        return sharedPreferences.getLong(what, defaultLong);
    }

    /**
     * @param where
     * @param what
     */
    public void writeLong(String where, long what) {
        sharedPreferences.edit().putLong(where, what).apply();
    }

    // boolean related methods

    /**
     * @param what
     * @return Returns the stored value of 'what'
     */
    public boolean readBoolean(String what) {
        return sharedPreferences.getBoolean(what, DEFAULT_BOOLEAN_VALUE);
    }

    /**
     * @param what
     * @return Returns the stored value of 'what'
     */
    public boolean readBoolean(int what) {
        return sharedPreferences.getBoolean(String.valueOf(what), DEFAULT_BOOLEAN_VALUE);
    }

    /**
     * @param what
     * @param defaultBoolean
     * @return Returns the stored value of 'what'
     */
    public boolean readBoolean(String what, boolean defaultBoolean) {
        /*if (defaultBoolean == true && !sharedPreferences.contains(what))
            writeBoolean(what, true);*/
        return sharedPreferences.getBoolean(what, defaultBoolean);
    }

    /**
     * @param what
     * @param defaultBoolean
     * @return Returns the stored value of 'what'
     */
    public boolean readBoolean(int what, boolean defaultBoolean) {
        /*if (defaultBoolean == true && !sharedPreferences.contains(String.valueOf(what)))
            writeBoolean(what, true);*/
        try {
            return sharedPreferences.getBoolean(String.valueOf(what), defaultBoolean);
        } catch (java.lang.ClassCastException ex) {
            return defaultBoolean;
        }
    }

    /**
     * @param where
     * @param what
     */
    public void writeBoolean(String where, boolean what) {
        sharedPreferences.edit().putBoolean(where, what).apply();
    }

    /**
     * @param where
     * @param what
     */
    public void writeBoolean(int where, boolean what) {
        sharedPreferences.edit().putBoolean(String.valueOf(where), what).apply();
    }

    // String set methods

    /**
     * @param key
     * @param value
     */
    @TargetApi(Build.VERSION_CODES.HONEYCOMB)
    public void putStringSet(final String key, final Set<String> value) {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.HONEYCOMB) {
            sharedPreferences.edit().putStringSet(key, value).apply();
        } else {
            // Workaround for pre-HC's lack of StringSets
            putOrderedStringSet(key, value);
        }
    }

    /**
     * @param key
     * @param value
     */
    public void putOrderedStringSet(String key, Set<String> value) {
        int stringSetLength = 0;
        if (sharedPreferences.contains(key + LENGTH)) {
            // First read what the value was
            stringSetLength = readInt(key + LENGTH);
        }
        writeInt(key + LENGTH, value.size());
        int i = 0;
        for (String aValue : value) {
            writeString(key + "[" + i + "]", aValue);
            i++;
        }
        for (; i < stringSetLength; i++) {
            // Remove any remaining values
            remove(key + "[" + i + "]");
        }
    }

    /**
     * @param key
     * @param defValue
     * @return Returns the String Set with HoneyComb compatibility
     */
    @TargetApi(Build.VERSION_CODES.HONEYCOMB)
    public Set<String> getStringSet(final String key, final Set<String> defValue) {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.HONEYCOMB) {
            return sharedPreferences.getStringSet(key, defValue);
        } else {
            // Workaround for pre-HC's missing getStringSet
            return getOrderedStringSet(key, defValue);
        }
    }

    /**
     * @param key
     * @param defValue
     * @return Returns the ordered String Set
     */
    public Set<String> getOrderedStringSet(String key, final Set<String> defValue) {
        if (contains(key + LENGTH)) {
            LinkedHashSet<String> set = new LinkedHashSet<>();
            int stringSetLength = readInt(key + LENGTH);
            if (stringSetLength >= 0) {
                for (int i = 0; i < stringSetLength; i++) {
                    set.add(readString(key + "[" + i + "]"));
                }
            }
            return set;
        }
        return defValue;
    }

    // end related methods

    /**
     * @param key
     */
    public void remove(final String key) {
        if (contains(key + LENGTH)) {
            // Workaround for pre-HC's lack of StringSets
            int stringSetLength = readInt(key + LENGTH);
            if (stringSetLength >= 0) {
                sharedPreferences.edit().remove(key + LENGTH).apply();
                for (int i = 0; i < stringSetLength; i++) {
                    sharedPreferences.edit().remove(key + "[" + i + "]").apply();
                }
            }
        }
        sharedPreferences.edit().remove(key).apply();
    }

    /**
     * @param key
     * @return Returns if that key exists
     */
    public boolean contains(final String key) {
        return sharedPreferences.contains(key);
    }

    /**
     * Clear all the preferences
     */
    public void clear() {
        sharedPreferences.edit().clear().apply();
    }
}