package com.xuanhuong.Model;

import android.app.Activity;
import android.content.Context;
import android.content.SharedPreferences;

/**
 * Created by huong.tx on 1/25/2018.
 */
public class SharePref {
    private static SharedPreferences mSharePref = null;
    public static final String EMAIL = "MAIL";
    public static final String PASS = "PASSWORD";
    public static final String ISCHECK = "REMEMBER";
    private SharePref() {

    }
    public static SharedPreferences getInstance(Context context) {
        if (mSharePref == null) {
            mSharePref = context.getSharedPreferences(context.getPackageName(), Activity.MODE_PRIVATE);
        }
        return mSharePref;
    }

    public static String readString(String key, String defValue) {
        return mSharePref.getString(key, defValue);
    }

    public static void writeString(String key, String value) {
        SharedPreferences.Editor prefsEditor = mSharePref.edit();
        prefsEditor.putString(key, value).commit();
    }
    public static Boolean readBoolean(String key, Boolean defValue) {
        return mSharePref.getBoolean(key, defValue);
    }

    public static void writeBoolean(String key, Boolean value) {
        SharedPreferences.Editor prefsEditor = mSharePref.edit();
        prefsEditor.putBoolean(key, value).commit();
    }
}