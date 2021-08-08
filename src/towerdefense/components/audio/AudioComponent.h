//
// Created by jkorn on 8/7/2021.
//

#pragma once

#include <unordered_map>
#include <string>

#include "Component.h"

namespace TowerDefense
{

    class AudioComponent : public Component
    {
    public:
        AudioComponent(class Actor* owner);
        virtual ~AudioComponent();

    public:
        virtual class AudioClip* AddClip(const std::string& clipName, const std::string& pathName);
        virtual class AudioClip* GetClip(const std::string& clipName) const;
        virtual void PlayClip(const std::string& clipName)=0;
        virtual void PlayClip(const std::string& clipName, int groupChannel)=0;

    protected:
        std::unordered_map<std::string, class AudioClip*> mAudioClips;
        class MixChunkAudioManager* mMixChunkAudioManager;
    };
}
