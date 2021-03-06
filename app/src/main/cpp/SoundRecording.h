/*
 * Copyright 2018 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ADS2018_SOUNDRECORDING_H
#define ADS2018_SOUNDRECORDING_H

#include <cstdint>
#include <array>

#include <chrono>
#include <memory>
#include <atomic>

#include <android/asset_manager.h>

#include "RenderableAudio.h"

class SoundRecording : public RenderableAudio<float>{

public:
    SoundRecording(const float *sourceData, int32_t numFrames, int32_t channelCount)
            : mData(sourceData)
            , mTotalFrames(numFrames)
            , mChannelCount(channelCount)
    {};
    void renderAudio(float *targetData, int32_t numFrames);
    void resetPlayHead() { mReadFrameIndex = 0; };
    void setPlaying(bool isPlaying) { mIsPlaying = isPlaying; resetPlayHead(); };
    void setLooping(bool isLooping) { mIsLooping = isLooping; };

    static SoundRecording* loadFromAssets(AAssetManager *assetManager,
                                                          const char *filename,
                                                          const int32_t channelCount);

private:
    int32_t mChannelCount = 1; // TODO: move this into a konstant and maybe add as parameter to ctor
    int32_t mReadFrameIndex = 0;
    const float* mData = nullptr;
    int32_t mTotalFrames = 0;
    std::atomic<bool> mIsPlaying { false };
    std::atomic<bool> mIsLooping { false };

};

#endif //ADS2018_SOUNDRECORDING_H
