#include "Track.h"



void Track::assignAssetToTrack(std::vector<float> asset)
{
    audioData = asset;
    //std::clog << "Track -> Asset assigned to track. Audiodata size: " << audioData.size() << std::endl;
}

void Track::assignTrackToVoice(Voice& voice)
{
    // assign a voice to this track
    voice.assignDataToBuffer(audioData);
    //std::clog << "Track -> Track assigned to voice." << std::endl;
}

void Track::removeTrackFromVoice(Voice& voice)
{
    // remove the voice from this track
    voice.clearBuffer();
    //std::clog << "Track -> Voice removed from track." << std::endl;
}

void Track::play(Voice &voice)
{
    assignTrackToVoice(voice);
}

void Track::stop()
{
    //removeTrackFromVoice();
}

void Track::setVolume(float vol)
{
    volume = vol;
    adjustVolume();
}

std::vector<float> Track::getAudioData()
{
    return audioData;
}

void Track::adjustVolume()
{
    // the volume needs to be set for every sample within the audio file.
    // this is done by multiplying each sample by the volume value.
    for (auto& sample : audioData)
        sample *= volume;
}




