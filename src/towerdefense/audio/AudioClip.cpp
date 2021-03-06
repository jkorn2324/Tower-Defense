//
// Created by jkorn on 6/29/2021.
//

#include "AudioClip.h"
#include "GameMath.h"

namespace TowerDefense
{

    AudioClip::AudioClip(Mix_Chunk *chunk)
    {
        mVolume = 1.0f;
        mMixChunk = chunk;
        mPlaying = mLooping = mPaused = false;
        mChannelID = 0;
    }

    void AudioClip::SetLooping(bool loop)
    {
        mLooping = loop;
    }

    bool AudioClip::IsLooping() const
    {
        return mLooping;
    }

    bool AudioClip::IsPlaying() const
    {
        return mPlaying && !mPaused;
    }

    bool AudioClip::IsPaused() const
    {
        return mPlaying && mPaused;
    }

    void AudioClip::Play(int channelGroupID)
    {
        if(mMixChunk == nullptr)
        {
            return;
        }

        if(mPlaying)
        {
            Stop();
        }

        int groupAvailable = channelGroupID < 0 ? -1
                : Mix_GroupAvailable(channelGroupID);
        mChannelID = Mix_PlayChannel(
                groupAvailable, mMixChunk, -(int)mLooping);
        mPlaying = true;
    }

    void AudioClip::Play()
    {
        Play(-1);
    }

    void AudioClip::Pause(bool paused)
    {
        if(!mPlaying)
        {
            return;
        }
        if(paused != mPaused)
        {
            if(mPaused)
            {
                Mix_Resume(mChannelID);
            }
            else
            {
                Mix_Pause(mChannelID);
            }
            mPaused = paused;
        }
    }

    void AudioClip::Stop()
    {
        if(!mPlaying)
        {
            return;
        }
        mPlaying = false;
        Mix_HaltChannel(mChannelID);
    }

    void AudioClip::FadeIn(float time)
    {
        FadeIn(time, -1);
    }

    void AudioClip::FadeIn(float time, int channelGroupID)
    {
        if(mMixChunk == nullptr)
        {
            return;
        }
        if(mPlaying)
        {
            Stop();
        }
        int groupAvailable = channelGroupID < 0 ? -1
                : Mix_GroupAvailable(channelGroupID);
        unsigned int milliseconds = (unsigned int)(time * 1000);
        mChannelID = Mix_FadeInChannel(
                groupAvailable, mMixChunk, -((int)mLooping), milliseconds);
        mPlaying = true;
    }

    void AudioClip::FadeOut(float time)
    {
        if (!mPlaying)
        {
            return;
        }
        unsigned int millis = (unsigned int)(time * 1000);
        Mix_FadeOutChannel(mChannelID, millis);
    }

    void AudioClip::SetVolume(float volume)
    {
        volume = Clamp(volume, 0.0f, 1.0f);
        if (mPlaying && volume != mVolume && mMixChunk != nullptr)
        {
            Uint32 actualVolume = static_cast<Uint32>(MIX_MAX_VOLUME * volume);
            Mix_VolumeChunk(mMixChunk, actualVolume);
        }
        mVolume = volume;
    }

    float AudioClip::GetVolume() const
    {
        return mVolume;
    }
}