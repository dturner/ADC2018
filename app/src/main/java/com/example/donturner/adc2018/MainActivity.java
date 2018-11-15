package com.example.donturner.adc2018;

import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.util.Log;
import android.view.MotionEvent;

import androidx.appcompat.app.AppCompatActivity;


public class MainActivity extends AppCompatActivity implements SensorEventListener {

    private final String TAG = this.getClass().getName();

    private native void startEngine();
    private native void tap(boolean b);
    private native void setFrequency(double frequency);
    private native void setSpread(double spread);


    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        startEngine();

        SensorManager sensorManager = (SensorManager) getSystemService(SENSOR_SERVICE);
        Sensor rotationSensor = sensorManager.getDefaultSensor(Sensor.TYPE_ROTATION_VECTOR);
        sensorManager.registerListener(this, rotationSensor,
        SensorManager.SENSOR_DELAY_FASTEST);
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

        float frequency = 50 + (30 * event.values[0]);
        //Log.d(TAG, "Frequency: " + frequency);
        setFrequency(frequency);

        double spread = 10 * event.values[1];
        //Log.d(TAG, "Spread: " + spread);
        setSpread(spread);
    }


    @Override
    public void onAccuracyChanged(Sensor sensor, int accuracy) {

    }
}
