#ifndef ADS2018_AUDIOENGINE_H
#define ADS2018_AUDIOENGINE_H

// AudioEngine.h

#include <oboe/Oboe.h>
#include "Oscillator.h"
#include "Mixer.h"

using namespace oboe;

constexpr int kNumOscs = 200;

class AudioEngine : public AudioStreamCallback{

public:

    void start();

    DataCallbackResult
    onAudioReady(AudioStream *oboeStream, void *audioData, int32_t numFrames) override;

    AudioStream *stream;
    Oscillator<float> osc[kNumOscs];
    Mixer<float> mixer;

    void tap(bool i);

    void setFrequency(double d);

    void setSpread(double d);

    double baseFreq;

    LatencyTuner *tuner;
};


#endif //ADS2018_AUDIOENGINE_H