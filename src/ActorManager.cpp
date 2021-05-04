#include "ActorManager.h"
#include "Game.h"
#include "Actor.h"

namespace TowerDefense
{

	ActorManager::ActorManager(Game* game)
	{
		mGame = game;

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

	Game* ActorManager::GetGame() const
	{
		return mGame;
	}

	void ActorManager::Update(float deltaTime)
	{
		for (const auto& despawnedActor : mDespawnActors)
		{
			HandleDespawn(despawnedActor);
		}

		for (const auto& actor : mActors)
		{
			actor->Update(deltaTime);
		}

		for(const auto& spawnedActor : mSpawnActors)
		{
			HandleSpawn(spawnedActor);
		}
		
		mSpawnActors.clear();
		mDespawnActors.clear();

		// Updates the transformation Matrix on each actor.
		for (const auto& actor : mActors)
		{
			actor->UpdateTransform();
		}
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
		const auto& searchedActor = std::find(mActors.begin(), mActors.end(), actor);
		if (searchedActor != mActors.end())
		{
			mActors.erase(searchedActor);
		}

		delete actor;
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

		const auto& searchedDespawnGroup = std::find(mDespawnActors.begin(), mDespawnActors.end(), actor);
		if (searchedDespawnGroup != mDespawnActors.end())
		{
			return;
		}
		mDespawnActors.push_back(actor);
	}
}