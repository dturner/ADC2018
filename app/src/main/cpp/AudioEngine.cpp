// AudioEngine.cpp

#include "AudioEngine.h"

void AudioEngine::start() {

    AudioStreamBuilder b;

    b.setPerformanceMode(PerformanceMode::LowLatency);
    b.setSharingMode(SharingMode::Exclusive);

    b.setCallback(this);
    b.setFormat(AudioFormat::Float);
    b.setChannelCount(1);

    b.openStream(&stream);

    //stream->setBufferSizeInFrames(stream->getFramesPerBurst());

    for (auto &i : osc) {
        i.setAmplitude(0.009);
        mixer.addTrack(&i);
    }

    tuner = new LatencyTuner(*stream, stream->getFramesPerBurst() * 4);
    tuner->requestReset();

    stream->requestStart();
}

DataCallbackResult
AudioEngine::onAudioReady(AudioStream *oboeStream, void *audioData, int32_t numFrames) {

    tuner->tune();
    mixer.renderAudio(static_cast<float *>(audioData), numFrames);
    return DataCallbackResult::Continue;
}

void AudioEngine::tap(bool b) {

    for (auto &i : osc) {
        i.setWaveOn(b);
    }
}

void AudioEngine::setFrequency(double d) {

    baseFreq = d;
}

void AudioEngine::setSpread(double d) {

    double freqInc = d / kNumOscs;

    for (int i = 0; i < kNumOscs; ++i) {
        osc[i].setFrequency(baseFreq + (freqInc * i));
    }
}
