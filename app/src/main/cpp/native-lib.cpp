// native-lib.cpp

#include <jni.h>
#include <string>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include "utils/logging.h"
#include "AudioEngine.h"


AudioEngine engine;

extern "C" {

JNIEXPORT void JNICALL
Java_com_example_donturner_adc2018_MainActivity_startEngine(JNIEnv *env, jobject instance) {

    engine.start();

}

JNIEXPORT void JNICALL
Java_com_example_donturner_adc2018_MainActivity_tap(JNIEnv *env, jobject instance, jboolean b) {

    engine.tap(b);

}

JNIEXPORT void JNICALL
Java_com_example_donturner_adc2018_MainActivity_setFrequency(
        JNIEnv *env, jobject instance,
        jdouble frequency) {

    engine.setFrequency(frequency);

}

}extern "C"
JNIEXPORT void JNICALL
Java_com_example_donturner_adc2018_MainActivity_setSpread(JNIEnv *env, jobject instance,
                                                          jdouble spread) {

    engine.setSpread(spread);

}