#include <jni.h>
#include <string>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include "AudioEngine.h"
#include "utils/logging.h"

AudioEngine engine;


extern "C"
JNIEXPORT void JNICALL
Java_com_example_donturner_ads2018_MainActivity_startEngine(JNIEnv *env, jobject instance, jobject jAssetManager) {

    LOGD("Starting engine");

    AAssetManager *a = AAssetManager_fromJava(env, jAssetManager);
    engine.start(a);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_donturner_ads2018_MainActivity_stopEngine(JNIEnv *env, jobject instance) {

    engine.stop();

}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_donturner_ads2018_MainActivity_tap(JNIEnv *env, jobject instance, jboolean b) {

    engine.tap(b);

}