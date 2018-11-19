#ifndef ADC2018_AUDIOENGINE_H
#define ADC2018_AUDIOENGINE_H

// AudioEngine.h

#include <oboe/Oboe.h>
#include "Oscillator.h"

using namespace oboe;

class AudioEngine : public AudioStreamCallback{

public:
    void start();

    DataCallbackResult
    onAudioReady(AudioStream *oboeStream, void *audioData, int32_t numFrames) override;

    AudioStream *stream;
    Oscillator<float> osc;

    void tap(bool b);
};


#endif //ADC2018_AUDIOENGINE_H