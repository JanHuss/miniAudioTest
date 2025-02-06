﻿#include "PlaybackDevice.h"

#include "Asset.h"

PlaybackDevice::PlaybackDevice(Voice* v) : voice(v)
{
}

void PlaybackDevice::data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount)
{
    //std::clog << "Playback Device -> Getting Buffer size: " << voi->getBuffer().size() << std::endl;
    //std::clog << "Playback Device -> Callback framecount: " << frameCount << std::endl;
    //std::clog << "Playback Device -> Callback pOutput: " << &out << std::endl;
    
    // as the callback is a static function, I can't access any member variables inside of the
    // playback class. I need to first set the ma_device `pDevice` to a playback class first
    // and have a `voice` accessible within the Playback class.
    
    PlaybackDevice* playbackDevice = static_cast<PlaybackDevice*>(pDevice->pUserData);
    if (!playbackDevice)
    {
        memset(pOutput, 0, frameCount * sizeof(float) * pDevice->playback.channels);
        return;
    }

    // create a voice pointer to get a voice within the playback device class
    Voice* voice = playbackDevice->getVoice();
    if (!voice)
    {
        memset(pOutput, 0, frameCount * sizeof(float) * pDevice->playback.channels);
        return;
    }
    
    // Then I can call the `processAudio` within the `voice`.
    voice->processAudio(static_cast<float*>(pOutput), frameCount);
    
}

int PlaybackDevice::init()
{
    deviceConfig = ma_device_config_init(ma_device_type_playback);
    deviceConfig.playback.format   = ma_format_f32;   // Set to ma_format_unknown to use the device's native format.
    deviceConfig.playback.channels = channels;               // Set to 0 to use the device's native channel count.
    deviceConfig.sampleRate        = sampleRate;           // Set to 0 to use the device's native sample rate.
    deviceConfig.dataCallback      = PlaybackDevice::data_callback;   // This function will be called when miniaudio needs more data.
    deviceConfig.pUserData         = this;   // Can be accessed from the device object (device.pUserData).
    
    if (ma_device_init(NULL, &deviceConfig, &device) != MA_SUCCESS)
    {
        std::cerr << "Failed to open playback device!" << std::endl;
        return -3;  // Failed to initialize the device.
    }
    else
    {
        std::clog << "Playback device initialised" << std::endl;
    }
    
    return true;
}

Voice* PlaybackDevice::getVoice()
{
    return voice;
}

