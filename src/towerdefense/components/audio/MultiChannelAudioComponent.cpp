//
// Created by jkorn on 8/7/2021.
//

#include "MultiChannelAudioComponent.h"

#include "Actor.h"
#include "AudioClip.h"

namespace TowerDefense
{

    MultiChannelAudioComponent::MultiChannelAudioComponent(Actor *actor)
            : AudioComponent(actor)
    {
        mAudioDelay = std::vector<AudioClipDelayData>();
    }

    void MultiChannelAudioComponent::Update(float deltaTime)
    {

    }

    void MultiChannelAudioComponent::PlayClip(const std::string &clipName)
    {
        PlayClip(clipName, -1);
    }

    void MultiChannelAudioComponent::PlayClip(const std::string &clipName, int channel)
    {
        PlayClip(clipName, channel, true);
    }

    void MultiChannelAudioComponent::PlayClip(const std::string &clipName, bool unpauseIfPaused)
    {
        PlayClip(clipName, -1, unpauseIfPaused);
    }

    void MultiChannelAudioComponent::PlayClip(const std::string &clipName, int channel, bool unpauseIfPaused)
    {
        // TODO: Implementation
    }

    bool MultiChannelAudioComponent::GetClipsPlaying(std::vector<class AudioClip *> &clips)
    {
        bool hasClipsPlaying = false;
        for(const auto& audioClipPair : mAudioClips)
        {
            AudioClip* clip = audioClipPair.second;
            if(clip != nullptr
                && clip->IsPlaying())
            {
                clips.push_back(clip);
                hasClipsPlaying = true;
            }
        }
        return hasClipsPlaying;
    }
}