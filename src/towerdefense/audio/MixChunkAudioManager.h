#pragma once

#include <SDL2/SDL_audio.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <unordered_map>

namespace TowerDefense
{

    class MixChunkAudioManager
    {
    public:
        MixChunkAudioManager();

    public:
        Mix_Chunk* GetMixChunk(const std::string& path);
        void FreeChunks();
        void CreateChannelGroup(int minChannel, int maxChannel, int groupID);

    public:
        bool Initialize();
        void SetAllocatedChannels(int channelNums);
        int GetTotalAllocatedChannels() const;

    private:
        Mix_Chunk* GenerateMixChunk(const std::string& path);

    private:
        std::unordered_map<std::string, Mix_Chunk*> mMixChunks;
        int mNumberOfChannels;
        bool mInitialized;
    };
}