//
// Created by jkorn on 8/7/2021.
//

#pragma once

#include "AudioComponent.h"

#include <string>

namespace TowerDefense
{
    class SingleChannelAudioComponent : public AudioComponent
    {
    public:
        SingleChannelAudioComponent(class Actor* owner);

    public:
        void PlayClip(const std::string& clipName) override;
        void PlayClip(const std::string& clipName, int channelGroup) override;
        void PlayClip(const std::string& clipName, float fadeInOutTime);
        void PlayClip(const std::string& clipName, int channelGroup, float fadeInOutTime);
        bool IsClipPlaying() const;
        bool IsClipPlaying(const std::string& name) const;
        void StopPlayingClip();
        void StopPlayingClip(float fadeOutTime);

    public:
        void PauseClip(bool paused);
        bool IsClipPaused() const;

    private:
        class AudioClip* GetPlayingClip() const;

    private:
        std::string mPlayingClip;
    };
}
