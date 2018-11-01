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


public class MainActivity extends AppCompatActivity implements SensorEventListener{

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

        SensorManager sensorManager = (SensorManager) getSystemService(SENSOR_SERVICE);
        Sensor rotationSensor = sensorManager.getDefaultSensor(Sensor.TYPE_ROTATION_VECTOR);
        sensorManager.registerListener(this, rotationSensor,
                SensorManager.SENSOR_DELAY_FASTEST);

    }

    protected void onStop(){
        super.onStop();
        stopEngine();
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {

        if (event.getAction() == MotionEvent.ACTION_DOWN){
            tap(true);

        }else if (event.getAction() == MotionEvent.ACTION_UP){
            tap(false);
        }
        return true;
    }

    @Override
    public void onSensorChanged(SensorEvent event) {
        setFrequency(150 + (event.values[0] * 100));
        setAmplitude((float) 0.5 + (event.values[1]));
    }

    @Override
    public void onAccuracyChanged(Sensor sensor, int accuracy) {

    }
}
