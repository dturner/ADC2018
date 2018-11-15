// native-lib.cpp

#include <jni.h>
#include <string>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include "utils/logging.h"
#include "AudioEngine.h"

extern "C" {

JNIEXPORT void JNICALL
Java_com_example_donturner_adc2018_MainActivity_startEngine(JNIEnv *env, jobject instance) {

    // TODO
}

JNIEXPORT void JNICALL
Java_com_example_donturner_adc2018_MainActivity_tap(JNIEnv *env, jobject instance, jboolean b) {

    // TODO
}

JNIEXPORT void JNICALL
Java_com_example_donturner_adc2018_MainActivity_setFrequency(
        JNIEnv *env, jobject instance,
        jdouble frequency) {

    // TODO
}

}extern "C"
JNIEXPORT void JNICALL
Java_com_example_donturner_adc2018_MainActivity_setSpread(JNIEnv *env, jobject instance,
                                                          jdouble spread) {

    // TODO
}