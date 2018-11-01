#include <jni.h>
#include <string>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include "utils/logging.h"
#include "AudioEngine.h"

AudioEngine engine;


extern "C" {


JNIEXPORT void JNICALL
Java_com_example_donturner_ads2018_MainActivity_createEngine(JNIEnv *env, jobject instance,
                                                             jobject jAssetManager) {

    AAssetManager *a = AAssetManager_fromJava(env, jAssetManager);
    engine.loadAmen(a);
}

JNIEXPORT void JNICALL
Java_com_example_donturner_ads2018_MainActivity_startEngine(JNIEnv *env, jobject instance) {

    // TODO
    engine.start();
}

JNIEXPORT void JNICALL
Java_com_example_donturner_ads2018_MainActivity_stopEngine(JNIEnv *env, jobject instance) {

    // TODO

}

JNIEXPORT void JNICALL
Java_com_example_donturner_ads2018_MainActivity_tap(JNIEnv *env, jobject instance, jboolean b) {

    engine.setWaveOn(b);

}

JNIEXPORT void JNICALL
Java_com_example_donturner_ads2018_MainActivity_setFrequency(
        JNIEnv *env, jobject instance,
        jfloat v) {

    engine.setF(v);

}

JNIEXPORT void JNICALL
Java_com_example_donturner_ads2018_MainActivity_setAmplitude(JNIEnv *env, jobject instance,
                                                             jfloat f) {

    engine.setA(f);

}

}