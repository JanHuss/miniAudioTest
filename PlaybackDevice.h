#pragma once

#include "miniaudio.h"
#include "Voice.h"
#include <iostream>

class PlaybackDevice
{
public:
    PlaybackDevice(Voice* v);
    static void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount);
    int init();
    Voice* getVoice();

    // the voice pointer needs to be set to pUserData on initialisation
    // then, the voice will be able to pass through the buffer
    // what I don't have is the voice pointer being assigned.
    Voice* voice;

    // public varaibles
    ma_device device;
    ma_device_config deviceConfig;

private:
    int channels = 2;
    int sampleRate = 41000;
    //int readIndex; // audio playhead 
};
