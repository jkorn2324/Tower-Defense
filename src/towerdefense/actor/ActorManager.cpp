#include "ActorManager.h"
#include "Game.h"
#include "Actor.h"

#include "Player.h"
#include "Enemy.h"

namespace TowerDefense
{

	ActorManager::ActorManager(Game* game)
	{
		mGame = game;
        mPlayer = nullptr;
		mSpawnActors = std::vector<Actor*>();
		mDespawnActors = std::vector<Actor*>();
		mActors = std::vector<Actor*>();
	}

	ActorManager::~ActorManager()
	{
		for (Actor* actor : mActors)
		{
			delete actor;
		}

		for (Actor* spawnActor : mSpawnActors)
		{
			delete spawnActor;
		}
		for (Actor* despawnActors : mDespawnActors)
		{
			delete despawnActors;
		}
		mActors.clear();
		mSpawnActors.clear();
		mDespawnActors.clear();
	}

	void ActorManager::InitActors()
	{
	    mPlayer = new Player(mGame);
	}

	Game* ActorManager::GetGame() const
	{
		return mGame;
	}

	Player* ActorManager::GetPlayer() const
	{
	    return mPlayer;
	}

	void ActorManager::ProcessInput(const Uint8* keyState)
	{
		for (const auto& actor : mActors)
		{
			actor->ProcessInput(keyState);
		}
	}

	void ActorManager::Update(float deltaTime)
	{
		for (int i = 0; i < mDespawnActors.size(); i++)
		{
		    Actor* despawnedActor = mDespawnActors[i];
			HandleDespawn(despawnedActor);
			delete despawnedActor;
		}
		mDespawnActors.clear();

		for (const auto& actor : mActors)
		{
			actor->Update(deltaTime);
		}

		for(const auto& spawnedActor : mSpawnActors)
		{
			HandleSpawn(spawnedActor);
		}
		mSpawnActors.clear();
	}

	void ActorManager::HandleSpawn(Actor* actor)
	{
		const auto& spawnedActorFound = std::find(mActors.begin(), mActors.end(), actor);
		if (spawnedActorFound != mActors.end())
		{
			return;
		}
		actor->OnActorSpawn();
		mActors.push_back(actor);
	}

	void ActorManager::HandleDespawn(Actor* actor)
	{
		const auto& searchedActor = std::find(
		        mActors.begin(), mActors.end(), actor);
        mActors.erase(searchedActor);
	}

	void ActorManager::AddActor(Actor* actor)
	{
		const auto& spawnActorSearch = std::find(mSpawnActors.begin(), mSpawnActors.end(), actor);
		if (spawnActorSearch != mSpawnActors.end())
		{
			return;
		}
		mSpawnActors.push_back(actor);
	}

	void ActorManager::RemoveActor(Actor* actor)
	{
		if (actor == nullptr)
		{
			return;
		}
		const auto& searchedDespawnGroup = std::find(
		        mDespawnActors.begin(), mDespawnActors.end(), actor);
		if (searchedDespawnGroup != mDespawnActors.end())
		{
			return;
		}
		mDespawnActors.push_back(actor);
	}
}