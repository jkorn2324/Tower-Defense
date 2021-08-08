//
// Created by jkorn on 8/7/2021.
//

#include "AudioComponent.h"
#include "Actor.h"
#include "Game.h"
#include "MixChunkAudioManager.h"
#include "AudioClip.h"

#include <SDL2/SDL_mixer.h>

namespace TowerDefense
{

    AudioComponent::AudioComponent(Actor *owner)
            : Component(owner)
    {
        mMixChunkAudioManager = (MixChunkAudioManager*)owner
                ->GetGame()->GetMixChunkAudioManager();
        mAudioClips = std::unordered_map<std::string, AudioClip*>();
    }

    AudioComponent::~AudioComponent()
    {
        for(const auto& pair : mAudioClips)
        {
            AudioClip* currentClip = pair.second;
            if(currentClip != nullptr
                && currentClip->IsPlaying())
            {
                currentClip->Stop();
            }
            delete currentClip;
        }
        mAudioClips.clear();
    }

    AudioClip* AudioComponent::AddClip(const std::string &clipName, const std::string &pathName)
    {
        AudioClip* newClip = GetClip(clipName);
        if(newClip != nullptr)
        {
            return newClip;
        }

        Mix_Chunk* chunk = mMixChunkAudioManager->GetMixChunk(pathName);
        if(chunk == nullptr)
        {
            SDL_Log("Failed to add audio clip to component with path of %s", pathName.c_str());
            return nullptr;
        }
        newClip = new AudioClip(chunk);
        mAudioClips.emplace(clipName, newClip);
        return newClip;
    }

    AudioClip* AudioComponent::GetClip(const std::string &clipName) const
    {
        const auto& searchedClip = mAudioClips.find(clipName);
        if(searchedClip != mAudioClips.end())
        {
            return (*searchedClip).second;
        }
        return nullptr;
    }
}