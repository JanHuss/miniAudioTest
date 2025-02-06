#pragma once

#include <vector>

#include "Voice.h"

class Track
{
public:
    void assignAssetToTrack(std::vector<float> asset);

    // low-level interface
    void assignTrackToVoice(Voice& voice);
    void removeTrackFromVoice(Voice& voice);
    void adjustVolume();
    
    // high-level interface:
    // would like to remove the voice parameter later on
    void play(Voice& voice);
    void stop();
    void setVolume(float vol);

    // getters
    std::vector<float> getAudioData();

    


private:
    std::vector<float> audioData;
    float volume;
    bool loop;
    bool isPlaying;
    //float pan; // consider this for later
};
