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


public class MainActivity extends AppCompatActivity implements SensorEventListener {

    private static final String TAG = MainActivity.class.getName();

    private native void createEngine(AssetManager assetManager);
    private native void startEngine();
    private native void stopEngine();
    private native void tap(boolean b);
    private native void setOscillatorVolume(double v);
    private native void setOscillatorFrequency(float v);


    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        Log.d(TAG, "onCreate");
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        createEngine(getAssets());
    }

    protected void onStart(){
        Log.d(TAG, "onResume");

        super.onStart();
        startEngine();

        SensorManager sensorManager = (SensorManager) getSystemService(SENSOR_SERVICE);
        Sensor rotationSensor = sensorManager.getDefaultSensor(Sensor.TYPE_ROTATION_VECTOR);
        sensorManager.registerListener(this, rotationSensor,
                SensorManager.SENSOR_DELAY_FASTEST);
    }

    protected void onStop(){
        Log.d(TAG, "onPause");
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

    @Override
    public void onSensorChanged(SensorEvent event) {
        setOscillatorFrequency(50 + (event.values[0] * 150));
        setOscillatorVolume(0.5 + event.values[1]);
    }


    @Override
    public void onAccuracyChanged(Sensor sensor, int accuracy) {

    }
}
