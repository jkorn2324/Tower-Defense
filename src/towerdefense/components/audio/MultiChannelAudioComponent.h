//
// Created by jkorn on 8/7/2021.
//

#pragma once

#include "AudioComponent.h"
#include "EventCallback.h"

#include <string>
#include <vector>

namespace TowerDefense
{



    class MultiChannelAudioComponent : public AudioComponent
    {
    public:
        struct AudioClipDelayData
        {
            class AudioClip* mClip;
            float mDelayTime;
            GenericEventCallback<class AudioClip*> callback;
        };

    public:
        MultiChannelAudioComponent(class Actor* actor);

    public:
        virtual void Update(float deltaTime) override;

    public:
        void PlayClip(const std::string& clipName) override;
        void PlayClip(const std::string& clipName, int channel) override;
        void PlayClip(const std::string& clipName, bool unpauseIfPaused);
        void PlayClip(const std::string& clipName, int channel, bool unpauseIfPaused);

    public:
        bool GetClipsPlaying(std::vector<class AudioClip*>& clips);

    private:
        std::vector<AudioClipDelayData> mAudioDelay;
    };
}