package com.angelde.fnadroid;

import android.app.ActivityManager;
import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.os.Environment;
import android.os.Handler;
import android.os.Looper;
import android.os.Vibrator;
import android.util.Log;
import android.widget.Toast;

import java.io.File;

public class FNADroidWrapper {

    //modify these for your obb versions
    public final static int OBB_VERSION_MAIN = 1;
    public final static int OBB_VERSION_PATCH = 1;

    private FNADroidWrapper() {
    }

    static {
        //basic dependencies: FNA
        System.loadLibrary("openal");
        System.loadLibrary("SDL2");
        System.loadLibrary("mojoshader");
        System.loadLibrary("vorbis");
        //basic dependencies: Mono and the wrapper
        System.loadLibrary("monosgen-2.0");
        System.loadLibrary("fnadroid-wrapper");
        //add your custom dependencies here; obligatory FEZ example
        System.loadLibrary("ogg");
        //System.loadLibrary("vorbisfile"); //enc and file already included in precompiled vorbis
    }

    public static WrapperActivity context;

    //Java-side helpers
    public static void setMonoDirsAuto() {
        File dir = context.getExternalFilesDir(null);
        if (dir == null) {
            return;
        }
        if (dir.getName().equals("files")) {
            dir = dir.getParentFile();
        }
        File monodir = new File(dir, "mono");
        File gamedir = new File(dir, "game");
        File homedir = new File(dir, "home");

        monodir.mkdirs();
        gamedir.mkdirs();
        homedir.mkdirs();

        Log.i("FNADroid", "Setting Mono dir to " + monodir.getAbsolutePath());
        setMonoDirs(fixPath(new File(monodir, "lib").getAbsolutePath()), fixPath(new File(monodir, "etc").getAbsolutePath()));
        Log.i("FNADroid", "Setting game dir to " + gamedir.getAbsolutePath());
        setGameDir(fixPath(gamedir.getAbsolutePath()));
        Log.i("FNADroid", "Setting home dir to " + homedir.getAbsolutePath());
        setHomeDir(fixPath(homedir.getAbsolutePath()));
    }

    public static String fixPath(String path) {
        return path.replace("/storage/emulated/0", "/sdcard");
    }

    public static String getObbPath(String obb, int version) {
        File file = new File(Environment.getExternalStorageDirectory() + "/Android/obb/" + context.getPackageName());
        file = new File(file, obb + "." + version + "." + context.getPackageName() + ".obb");
        //TODO check if we've downloaded the file / the app comes from the play store, otherwise return appropriately
        return fixPath(file.getAbsolutePath());
    }

    //j to cpp
    public native static void onCreate();
    public native static void onStart();
    public native static void onPause();
    public native static void onResume();
    public native static void onStop();
    public native static void setMonoDirs(String lib, String etc);
    public native static void setGameDir(String to);
    public native static void setHomeDir(String to);

    //cpp to j
    public static void showDebug(final String msg) {
        showMsg("FNADroid DEBUG", msg);
    }
    public static void showError(final String msg) {
        showMsg("FNADroid FATAL ERROR", msg);
    }
    public static void showMsg(final String title, final String msg) {
        final AlertDialog[] alert = {null};
        context.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                final AlertDialog alert_ = new AlertDialog.Builder(context).create();
                alert_.setTitle(title);
                alert_.setMessage(msg);
                alert_.setButton(AlertDialog.BUTTON_NEUTRAL, "OK", new DialogInterface.OnClickListener() {
                    public void onClick(DialogInterface dialog, int which) {
                        alert_.dismiss();
                    }
                });
                alert_.show();
                alert[0] = alert_;
            }
        });
        //showMsg is called from the native thread; keep it hanging
        while (alert[0] == null || alert[0].isShowing()) {
            try {
                Thread.sleep(100L);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    public static String getMainObbPath() {
        return getObbPath("main", OBB_VERSION_MAIN);
    }
    public static String getPatchObbPath() {
        return getObbPath("patch", OBB_VERSION_PATCH);
    }
    public static boolean canGLES3() {
        return ((ActivityManager) context.getSystemService(Context.ACTIVITY_SERVICE)).getDeviceConfigurationInfo().reqGlEsVersion >= 0x30000;
    }

    public static void vibrationCancel() {
        ((Vibrator) context.getSystemService(Context.VIBRATOR_SERVICE)).cancel();
    }
    public static boolean vibrationAvailable() {
        return ((Vibrator) context.getSystemService(Context.VIBRATOR_SERVICE)).hasVibrator();
    }
    public static void vibrate(long milliseconds) {
        ((Vibrator) context.getSystemService(Context.VIBRATOR_SERVICE)).vibrate(milliseconds);
    }

}
