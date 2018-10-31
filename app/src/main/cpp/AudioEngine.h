//
// Created by Don Turner on 29/10/2018.
//

#ifndef ADS2018_AUDIOENGINE_H
#define ADS2018_AUDIOENGINE_H

#include <oboe/Oboe.h>
#include <android/asset_manager.h>
#include "Oscillator.h"
#include "Mixer.h"
#include "SoundRecording.h"

using namespace oboe;

class AudioEngine : AudioStreamCallback {

public:
    void start(AAssetManager *assetManager);
    void stop();


    void tap(bool isDown);

private:
    AudioStream *stream = nullptr;
    Oscillator<float> mOsc;
    Mixer<float> mMixer;
    SoundRecording* sr;

    DataCallbackResult
    onAudioReady(AudioStream *oboeStream, void *audioData, int32_t numFrames) override;

};


#endif //ADS2018_AUDIOENGINE_H
