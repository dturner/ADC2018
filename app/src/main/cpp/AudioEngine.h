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

    AudioEngine(AAssetManager *assetManager);

    void start();
    void stop();


    void tap(bool isDown);

    void setOscillatorFrequency(float f);
    void setOscillatorAmplitude(float f);

private:
    AudioStream *stream = nullptr;

    std::shared_ptr<Oscillator<float>> mOsc {nullptr};
    Mixer<float> mMixer;
    std::shared_ptr<SoundRecording> sr {nullptr};

    DataCallbackResult
    onAudioReady(AudioStream *oboeStream, void *audioData, int32_t numFrames) override;

};


#endif //ADS2018_AUDIOENGINE_H
