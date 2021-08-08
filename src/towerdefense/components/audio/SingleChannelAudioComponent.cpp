//
// Created by jkorn on 8/7/2021.
//

#include "SingleChannelAudioComponent.h"

#include "Actor.h"
#include "AudioClip.h"

namespace TowerDefense
{

    SingleChannelAudioComponent::SingleChannelAudioComponent(Actor *owner)
            : AudioComponent(owner)
    {
        mPlayingClip = "";
    }

    AudioClip* SingleChannelAudioComponent::GetPlayingClip() const
    {
        return GetClip(mPlayingClip);
    }

    void SingleChannelAudioComponent::PlayClip(const std::string &clipName)
    {
        PlayClip(clipName, -1);
    }

    void SingleChannelAudioComponent::PlayClip(const std::string &clipName, int channelGroup)
    {
        PlayClip(clipName, channelGroup, 0.0f);
    }

    void SingleChannelAudioComponent::PlayClip(const std::string &clipName, float fadeInOutTime)
    {
        PlayClip(clipName, -1, fadeInOutTime);
    }

    void SingleChannelAudioComponent::PlayClip(const std::string &clipName, int channelGroup, float fadeInOutTime)
    {
        AudioClip* newAudioClip = GetClip(clipName);
        if(newAudioClip == nullptr)
        {
            return;
        }

        AudioClip* currentAudioClip = (AudioClip*)GetPlayingClip();
        if(fadeInOutTime > 0.0f)
        {
            if(currentAudioClip != nullptr)
            {
                currentAudioClip->FadeOut(fadeInOutTime);
            }
            newAudioClip->FadeIn(fadeInOutTime, channelGroup);
        }
        else
        {
            if(currentAudioClip != nullptr)
            {
                currentAudioClip->Stop();
            }
            newAudioClip->Play(channelGroup);
        }
    }

    bool SingleChannelAudioComponent::IsClipPlaying() const
    {
        return IsClipPlaying(mPlayingClip);
    }

    bool SingleChannelAudioComponent::IsClipPlaying(const std::string &name) const
    {
        AudioClip* currentPlayingClip = GetPlayingClip();
        AudioClip* searchedClip = GetClip(name);
        return searchedClip == currentPlayingClip
            && searchedClip->IsPlaying();
    }

    bool SingleChannelAudioComponent::IsClipPaused() const
    {
        AudioClip* currentActiveClip = GetPlayingClip();
        return currentActiveClip != nullptr
            && currentActiveClip->IsPaused();
    }

    void SingleChannelAudioComponent::PauseClip(bool paused)
    {
        AudioClip* currentPlayingClip = GetPlayingClip();
        if(currentPlayingClip != nullptr)
        {
            currentPlayingClip->Pause(paused);
        }
    }

    void SingleChannelAudioComponent::StopPlayingClip()
    {
        StopPlayingClip(0.0f);
    }

    void SingleChannelAudioComponent::StopPlayingClip(float fadeOutTime)
    {
        AudioClip* currentAudioClip = (AudioClip*)GetPlayingClip();
        if(currentAudioClip != nullptr)
        {
            if(fadeOutTime > 0.0f)
            {
                currentAudioClip->FadeIn(fadeOutTime);
            }
            else
            {
                currentAudioClip->Stop();
            }
        }
        mPlayingClip = "";
    }
}