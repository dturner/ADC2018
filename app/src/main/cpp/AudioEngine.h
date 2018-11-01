//
// Created by Don Turner on 2018-11-01.
//

#ifndef ADS2018_AUDIOENGINE_H
#define ADS2018_AUDIOENGINE_H

#include <oboe/Oboe.h>
#include <android/asset_manager.h>
#include "Oscillator.h"
#include "SoundRecording.h"
#include "Mixer.h"

using namespace oboe;

class AudioEngine : AudioStreamCallback {

public:

    void start();
    void stop();
    void setWaveOn(bool isOn);

    DataCallbackResult
    onAudioReady(AudioStream *oboeStream, void *audioData, int32_t numFrames) override ;

    void loadAmen(AAssetManager *pManager);

    void setF(float d);

    void setA(float d);

private:

    AudioStream *stream;
    Oscillator<float> osc;
    SoundRecording *amen;
    Mixer<float> mixer;
};


#endif //ADS2018_AUDIOENGINE_H
