package com.example.donturner.ads2018;

import android.content.res.AssetManager;
import android.os.Bundle;
import android.view.MotionEvent;

import androidx.appcompat.app.AppCompatActivity;


public class MainActivity extends AppCompatActivity {

    private native void stopEngine();
    private native void startEngine(AssetManager assetManager);
    private native void tap(boolean b);

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    protected void onStart(){
        super.onStart();
        startEngine(getAssets());
    }

    protected void onStop(){
        super.onStop();
        stopEngine();
    }


    @Override
    public boolean onTouchEvent(MotionEvent event) {

        if (event.getAction() == MotionEvent.ACTION_DOWN){
            tap(true);
        } else if (event.getAction() == MotionEvent.ACTION_UP){
            tap(false);
        }


        return super.onTouchEvent(event);
    }

}
