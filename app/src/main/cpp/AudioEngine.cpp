//
// Created by Don Turner on 29/10/2018.
//

#include <android/asset_manager.h>
#include "AudioEngine.h"
#include "utils/logging.h"


void AudioEngine::start(AAssetManager *assetManager) {

    LOGD("START");

    // Load the AMEN break
    sr = SoundRecording::loadFromAssets(assetManager, "AMEN.raw", 1);
    sr->setPlaying(true);
    sr->setLooping(true);

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


    mOsc.setSampleRate(stream->getSampleRate());
    mOsc.setFrequency(440.0);
    mOsc.setAmplitude(0.2);

    // Make a std::shared_ptr from our SoundRecording
    std::shared_ptr<RenderableAudio<float>> pSoundRecording(sr);
    std::shared_ptr<RenderableAudio<float>> pOsc(&mOsc);

    mMixer.addTrack(pSoundRecording);
    mMixer.addTrack(pOsc);

    r = stream->requestStart();
    if (r != Result::OK){
        LOGE("Error starting stream: %s", convertToText(r));
        stream->close();
        return;
    }

}

DataCallbackResult
AudioEngine::onAudioReady(AudioStream *oboeStream, void *audioData, int32_t numFrames) {

    //mOsc.renderAudio(static_cast<float *>(audioData), numFrames);
    mMixer.renderAudio(static_cast<float *>(audioData), numFrames);
    return DataCallbackResult::Continue;
}

void AudioEngine::stop() {
    if (stream != nullptr){
        stream->close();
    }
}

void AudioEngine::tap(bool isDown) {

    mOsc.setWaveOn(isDown);
}
