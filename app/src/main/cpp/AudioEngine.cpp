// AudioEngine.cpp

#include "AudioEngine.h"

void AudioEngine::start() {

    AudioStreamBuilder b;

    b.setPerformanceMode(PerformanceMode::LowLatency);
    b.setSharingMode(SharingMode::Exclusive);

    b.setFormat(AudioFormat::Float);
    b.setChannelCount(1);

    b.setCallback(this);

    b.openStream(&stream);

    stream->setBufferSizeInFrames(stream->getFramesPerBurst());

    osc.setFrequency(80.0);
    osc.setAmplitude(0.3);
    osc.setSampleRate(stream->getSampleRate());

    stream->requestStart();
}

DataCallbackResult
AudioEngine::onAudioReady(AudioStream *oboeStream, void *audioData, int32_t numFrames) {

    osc.renderAudio(static_cast<float *>(audioData), numFrames);
    return DataCallbackResult::Continue;
}

void AudioEngine::tap(bool b) {

    osc.setWaveOn(b);
}
