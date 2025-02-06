#pragma once

#include <vector>
#include <iostream>

#include "miniaudio.h"

class Voice
{
public:
    enum VOICESTATE {REAL, VIRTUAL};
    VOICESTATE voiceState;
    void assignDataToBuffer(std::vector<float>& audioData);
    void clearBuffer();
    void processAudio(float* outputBuffer, ma_uint32 frameCount);
    
    //void increaseReadIndex();
    //void resetReadIndex();
    //size_t getReadIndex();

    // has to be removed. just used for testing what the buffer is looking like in callback
    std::vector<float> getBuffer();

private:
    std::vector<float> buffer;
    size_t playHead = 0; // playhead to keep track of playback position
    bool isPlaying = false;
    int channels = 2;
    int pan = 0.5f;
};
