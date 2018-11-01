#include "AudioEngine.h"
#include "SoundRecording.h"

void AudioEngine::start() {

    AudioStreamBuilder b;

    b.setPerformanceMode(PerformanceMode::LowLatency);
    b.setSharingMode(SharingMode::Exclusive);
    b.setFormat(AudioFormat::Float);
    b.setChannelCount(1);
    b.setCallback(this);

    b.openStream(&stream);

    osc.setAmplitude(0.3);
    osc.setFrequency(110.0);
    osc.setSampleRate(stream->getSampleRate());

    mixer.addTrack(amen);
    mixer.addTrack(&osc);

    stream->setBufferSizeInFrames(stream->getFramesPerBurst() * 2);
    stream->requestStart();

}

DataCallbackResult
AudioEngine::onAudioReady(AudioStream *oboeStream, void *audioData, int32_t numFrames) {

    mixer.renderAudio(static_cast<float *>(audioData), numFrames);
    return DataCallbackResult::Continue;
}

void AudioEngine::setWaveOn(bool isOn) {
    osc.setWaveOn(isOn);
}

void AudioEngine::loadAmen(AAssetManager *pManager) {

    amen = SoundRecording::loadFromAssets(pManager, "AMEN.raw", 1);
    amen->setPlaying(true);
    amen->setLooping(true);
}

void AudioEngine::setF(float d) {

    osc.setFrequency(d);

}

void AudioEngine::setA(float d) {
    osc.setAmplitude(d);
}

