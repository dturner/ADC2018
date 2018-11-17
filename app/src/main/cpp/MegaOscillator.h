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


#ifndef ADC2018_MEGAOSCILLATOR_H
#define ADC2018_MEGAOSCILLATOR_H


#include <cstdint>

#include "RenderableAudio.h"
#include "Mixer.h"
#include "Oscillator.h"


constexpr int kNumOscs = 200;

template <typename T>
class MegaOscillator : RenderableAudio<T> {

public:
    MegaOscillator(){
        for (auto &o : oscs){
            mixer.addTrack(&o);
        }
    }

    void setWaveOn(bool isWaveOn){
        for (auto &o : oscs){
            o.setWaveOn(isWaveOn);
        }
    };

    void setSampleRate(int32_t sampleRate){
        for (auto &o : oscs){
            o.setSampleRate(sampleRate);
        }
    };

    void setFrequency(double frequency) {
        mBaseFrequency = frequency;
        updateFrequencies();
    };

    void setAmplitude(float amplitude){

        float perOscAmplitude = amplitude / (float) kNumOscs;

        for (auto &o : oscs){
            o.setAmplitude(perOscAmplitude);
        }
    };

    void renderAudio(T *audioData, int32_t numFrames) override {
        mixer.renderAudio(audioData, numFrames);
    }

    /**
     * Set the spread of oscillator frequencies above and below the base frequency
     * @param spread in Hz
     */
    void setSpread(double spread) {
        mSpread = spread;
        updateFrequencies();
    }

private:

    Mixer<T> mixer;
    Oscillator<T> oscs[kNumOscs];
    double mBaseFrequency = 440.0;
    double mSpread = 0.01;

    void updateFrequencies(){

        double currentFrequency = mBaseFrequency - (mSpread / 2);
        double frequencyIncrement = mSpread / kNumOscs;
        for (int i = 0; i < kNumOscs; ++i) {
            currentFrequency += (frequencyIncrement * i);
            oscs[i].setFrequency(currentFrequency);
        }
    }
};


#endif //ADC2018_MEGAOSCILLATOR_H
