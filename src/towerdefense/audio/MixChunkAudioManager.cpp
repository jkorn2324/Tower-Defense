//
// Created by jkorn on 6/29/2021.
//

#include "MixChunkAudioManager.h"
#include "GameParameters.h"

#include <SDL2/SDL_log.h>

namespace TowerDefense
{

    MixChunkAudioManager::MixChunkAudioManager()
    {
        mInitialized = false;
        mNumberOfChannels = 32;
        mMixChunks = std::unordered_map<std::string, Mix_Chunk*>();
    }

    bool MixChunkAudioManager::Initialize()
    {
        if(mInitialized)
        {
            return true;
        }

        int openAudio = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
        if(openAudio == -1)
        {
            if(DISPLAY_LOGS)
            {
                SDL_Log("Audio failed to open: %s", Mix_GetError);
            }
            return false;
        }
        mInitialized = true;
        SetAllocatedChannels(mNumberOfChannels);
        return true;
    }

    void MixChunkAudioManager::CreateChannelGroup(int minChannel, int maxChannel, int groupID)
    {
        if(!mInitialized)
        {
            return;
        }
        Mix_GroupChannels(minChannel, maxChannel, groupID);
    }

    void MixChunkAudioManager::SetAllocatedChannels(int channelNums)
    {
        mNumberOfChannels = channelNums;
        if(!mInitialized)
        {
            return;
        }
        Mix_AllocateChannels(channelNums);
    }

    int MixChunkAudioManager::GetTotalAllocatedChannels() const
    {
        return mNumberOfChannels;
    }

    void MixChunkAudioManager::FreeChunks()
    {
        for(const auto& chunkPair : mMixChunks)
        {
            Mix_Chunk* chunk = chunkPair.second;
            Mix_FreeChunk(chunk);
        }
        mMixChunks.clear();
    }

    Mix_Chunk* MixChunkAudioManager::GetMixChunk(const std::string &path)
    {
        const auto& foundChunk = mMixChunks.find(path);
        if(foundChunk != mMixChunks.end())
        {
            return (*foundChunk).second;
        }
        return GenerateMixChunk(path);
    }

    Mix_Chunk* MixChunkAudioManager::GenerateMixChunk(const std::string& audioClipPath)
    {
        if (!mInitialized)
        {
            SDL_Log("Failed to load chunk mix: SDL Mixer is not initialized.");
            return nullptr;
        }

        Mix_Chunk* chunkClip = Mix_LoadWAV(audioClipPath.c_str());
        if (chunkClip == nullptr)
        {
            SDL_Log("Failed to load chunk mix %s: %s", audioClipPath.c_str(), Mix_GetError);
            return nullptr;
        }
        mMixChunks.emplace(audioClipPath, chunkClip);
        return chunkClip;
    }
}