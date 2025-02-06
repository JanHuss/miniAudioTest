#include "Voice.h"

#include <algorithm>
#include <ostream>

void Voice::assignDataToBuffer(std::vector<float>& audioData)
{
    //std::clog << "Voice -> audio data size in voice: " << audioData.size() << std::endl;
    buffer = audioData;
    playHead = 0;
    isPlaying = true;
    if (!buffer.empty())
        std::clog << "Voice -> Buffer not empty. Audio data assigned to Buffer" << std::endl;
    std::clog << "Voice -> Buffer size: " << buffer.size() << std::endl;
}

void Voice::clearBuffer()
{
    buffer.clear();
    playHead = 0;
    isPlaying = false;
    std::clog << "Voice -> Buffer cleared" << std::endl;
    std::clog << "Voice -> buffer size: " << buffer.size() << std::endl;
}



void Voice::processAudio(float* outputBuffer, ma_uint32 frameCount)
{
    //std::clog << "Voice -> \"processAudio()\" being called" << std::endl;
    if (!isPlaying || buffer.empty())
    {
        memset(outputBuffer, 0, frameCount * sizeof(float)/* * channels*/);
        return;
    }

    for (ma_uint32 i = 0; i < frameCount; ++i)
    {
        //float sample = 0.0f;
        float sampleLeft = 0.0f;
        float sampleRight = 0.0f;
        
        if (playHead < buffer.size())
        {
            // sample = buffer[playHead++];
            if (channels == 1)
            {
                float sample = buffer[playHead];
                sampleLeft = sample * (1.0f - pan);
                sampleRight = sample * pan;
            }
            else if (channels == 2)
            {
                sampleLeft = buffer[playHead++];
                sampleRight = buffer[playHead++];
            }
        }
        else
        {
            // add looping here

            // add stop here
            isPlaying = false;
            break;
        }

        
        outputBuffer[i * 2] = sampleLeft;
        outputBuffer[i * 2 + 1] = sampleRight;
    }

    // if voice has stopped playing, fill outputbuffer with silence
    //if (!isPlaying)
    //    memset(outputBuffer + (frameCount * 2), 0, (frameCount - playHead) * sizeof(float) * 2);
}

//void Voice::increaseReadIndex()
//{
//    readIndex++;
//}
//
//void Voice::resetReadIndex()
//{
//    readIndex = 0;
//}
//
//size_t Voice::getReadIndex()
//{
//    return readIndex;
//}

std::vector<float> Voice::getBuffer()
{
    return buffer;
}
