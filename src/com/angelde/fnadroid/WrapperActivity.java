package com.angelde.fnadroid;

import android.os.Bundle;
import org.libsdl.app.SDLActivity;

public class WrapperActivity extends SDLActivity {

    @Override
    public void onCreate(Bundle savedInstanceState) {
        FNADroidWrapper.context = this;
        FNADroidWrapper.setMonoDirsAuto();

        super.onCreate(savedInstanceState);

        FNADroidWrapper.onCreate();
    }

    @Override
    protected void onStart() {
        super.onStart();

        FNADroidWrapper.onStart();
    }

    @Override
    protected void onPause() {
        super.onPause();

        FNADroidWrapper.onPause();
    }

    @Override
    protected void onResume() {
        super.onResume();

        FNADroidWrapper.onResume();
    }

    @Override
    protected void onStop() {
        super.onStop();

        FNADroidWrapper.onStop();
    }

}