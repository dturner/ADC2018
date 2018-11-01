package com.example.donturner.ads2018;

import android.content.res.AssetManager;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.util.Log;
import android.view.MotionEvent;

import androidx.appcompat.app.AppCompatActivity;


public class MainActivity extends AppCompatActivity {

    private native void createEngine(AssetManager assets);
    private native void startEngine();
    private native void stopEngine();
    private native void tap(boolean b);
    private native void setFrequency(float f);
    private native void setAmplitude(float f);

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        createEngine(getAssets());
    }


    protected void onStart(){
        super.onStart();
        startEngine();

    }

    protected void onStop(){
        super.onStop();
        stopEngine();
    }

}
