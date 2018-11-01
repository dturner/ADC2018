#include <jni.h>
#include <string>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include "AudioEngine.h"
#include "utils/logging.h"

static std::unique_ptr<AudioEngine> engine = nullptr;


extern "C"
JNIEXPORT void JNICALL
Java_com_example_donturner_ads2018_MainActivity_createEngine(JNIEnv *env, jobject instance, jobject jAssetManager) {

    if (engine == nullptr){
        AAssetManager *a = AAssetManager_fromJava(env, jAssetManager);
        engine = std::make_unique<AudioEngine>(a);
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_donturner_ads2018_MainActivity_startEngine(JNIEnv *env, jobject instance) {

    LOGD("Starting engine");
    engine->start();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_donturner_ads2018_MainActivity_stopEngine(JNIEnv *env, jobject instance) {

    engine->stop();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_donturner_ads2018_MainActivity_tap(JNIEnv *env, jobject instance, jboolean b) {

    engine->tap(b);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_donturner_ads2018_MainActivity_setOscillatorFrequency(JNIEnv *env,
                                                                       jobject instance, jfloat v) {

    engine->setOscillatorFrequency(v);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_donturner_ads2018_MainActivity_setOscillatorVolume(JNIEnv *env, jobject instance,
                                                                    jdouble v) {

    engine->setOscillatorAmplitude(v);

}