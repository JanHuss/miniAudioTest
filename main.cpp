#pragma once

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

#include "Asset.h"
#include "PlaybackDevice.h"
#include "Track.h"
#include "Voice.h"

#include <iostream>
#include <thread>
#include <chrono>

Voice voice;

int main()
{
	std::cout << "Hello World!" << std::endl;

	// create the playback device that contains callback logic
	PlaybackDevice playbackDevice(&voice);
	playbackDevice.init();
	//Voice voice;
	// create and load assets
	Asset bigWave;
	bigWave.loadFile("BigWave.wav");
	//bigWave.loadFile("BigWave.wav"); // test to see if the file would load a second time.
	//std::clog << "Bigwave audiodata size called from main: " << bigWave.getAudioData().size() << std::endl;
	//std::clog << "Bigwave frame count called from main: " << bigWave.getTotalFrameCount() << std::endl;
	Asset trapDoor;
	trapDoor.loadFile("TrapDoor.wav");
	
	
	Track bigWaveTrack;
	bigWaveTrack.assignAssetToTrack(bigWave.getAudioData());
	//std::clog << "Bigwave audiodata size from Track Class called from main: " << bigWaveTrack.getAudioData().size() << std::endl;
	
	//std::clog << "Bigwave current volume on 100kth element: " << bigWaveTrack.getVolume()[100000] << std::endl;
	//bigWaveTrack.setVolume(0.5f);
	//std::clog << "Bigwave current volume on 100kth element: " << bigWaveTrack.getVolume()[100000] << std::endl;

	
	// assigning a voice to the audio track to playback audio. I think that this should be moved to track and instead,
	// a "Play()" function should be called. that way, I have high level interface on main and a track can get a "voice"
	// from the "voice" pool 
	//bigWaveTrack.assignTrackToVoice(voice);

	Track trapDoorTrack;
	trapDoorTrack.assignAssetToTrack(trapDoor.getAudioData());
	
	// start playback device which will run callback function and wait for any audio data to be passed through
	if (ma_device_start(&playbackDevice.device) != MA_SUCCESS)
	{
		std::cerr << "Failed to start playback device." << std::endl;
		ma_device_uninit(&playbackDevice.device);
		// this is already creating a red flag. all decoders should be uninitialised at once
		// making use of a resource manager or something. look into this later.
		ma_decoder_uninit(&bigWave.decoder); 
		return -4;
	}
	
	bigWaveTrack.play(voice);
	// Letting audio play before every device is shut down
	std::this_thread::sleep_for(std::chrono::seconds(5));
	bigWaveTrack.removeTrackFromVoice(voice);
	
	trapDoorTrack.play(voice);
	std::this_thread::sleep_for(std::chrono::seconds(5));
	trapDoorTrack.removeTrackFromVoice(voice);
	std::this_thread::sleep_for(std::chrono::seconds(5));
	// uninitialise the assets and stop the playback device from running. create a resource
	// manager to uninitialise all assets at once. 
	ma_decoder_uninit(&bigWave.decoder);
	//ma_decoder_uninit(&trapDoor.decoder);
	ma_device_uninit(&playbackDevice.device);
   

	return 0;
}