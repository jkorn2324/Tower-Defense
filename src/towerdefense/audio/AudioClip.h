#pragma once

#include <SDL2/SDL_mixer.h>
#include <string>

namespace TowerDefense
{

    class AudioClip
    {
    public:
        AudioClip(Mix_Chunk* chunk);

    public:
        void Play();
        void Play(int channelGroupID);
        bool IsPlaying() const;
        void Stop();
        void FadeIn(float time);
        void FadeIn(float time, int channelGroupID);
        void FadeOut(float time);

    public:
        void SetLooping(bool loop);
        bool IsLooping() const;

    public:
        void Pause(bool paused);
        bool IsPaused() const;

    public:
        void SetVolume(float volume);
        float GetVolume() const;

    private:
        Mix_Chunk* mMixChunk;
        int mChannelID;
        bool mLooping, mPlaying, mPaused;
        float mVolume;
    };
}