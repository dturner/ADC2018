//
// Created by Don Turner on 29/10/2018.
//

#include <android/asset_manager.h>
#include "AudioEngine.h"
#include "utils/logging.h"


AudioEngine::AudioEngine(AAssetManager *assetManager) {
    mOsc = std::make_shared<Oscillator<float>>();

    // Load the AMEN break
    sr = SoundRecording::loadFromAssets(assetManager, "AMEN.raw", 1);
    sr->setPlaying(true);
    sr->setLooping(true);
}


void AudioEngine::start() {

    LOGD("AudioEngine::start");

    if (stream != nullptr){
        LOGE("Stream already created");
        return;
    }

    // Set up the playback stream
    AudioStreamBuilder b;
    b.setPerformanceMode(PerformanceMode::LowLatency);
    b.setSharingMode(SharingMode::Exclusive);
    b.setFormat(AudioFormat::Float);
    b.setChannelCount(1);
    b.setCallback(this);
    Result r = b.openStream(&stream);
    if (r != Result::OK){
        LOGE("Error opening stream. Error: %s", convertToText(r));
        return;
    }

    mOsc->setSampleRate(stream->getSampleRate());
    mOsc->setFrequency(50.0);
    mOsc->setAmplitude(0.2);

    mMixer.addTrack(sr);
    mMixer.addTrack(mOsc);

    r = stream->requestStart();
    if (r != Result::OK){
        LOGE("Error starting stream: %s", convertToText(r));
        stream->close();
        return;
    }
}

DataCallbackResult
AudioEngine::onAudioReady(AudioStream *oboeStream, void *audioData, int32_t numFrames) {

    mMixer.renderAudio(static_cast<float *>(audioData), numFrames);
    return DataCallbackResult::Continue;
}

void AudioEngine::stop() {

    LOGD("AudioEngine::stop");

    mMixer.clearTracks();
    if (stream != nullptr){
        stream->close();
        stream = nullptr;
    }
}

void AudioEngine::tap(bool isDown) {
    mOsc->setWaveOn(isDown);
}

void AudioEngine::setOscillatorFrequency(float f) {
    mOsc->setFrequency(f);
}

void AudioEngine::setOscillatorAmplitude(float f) {
    mOsc->setAmplitude(f);
}




