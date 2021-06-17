#pragma once

#include "Actor.h"
#include "Vector2.h"

#include <string>

#ifndef DEFAULT_TOWER
#define DEFAULT_TOWER "DefaultTower"
#endif

namespace TowerDefense
{

    enum TowerTargetType
    {
        TARGET_CLOSEST_ENEMY,
        TARGET_FARTHEST_ENEMY,
        TARGET_FARTHEST_ALONG_TRACK,
        TARGET_STRONGEST
    };


	class Tower : public Actor
	{

	public:
		explicit Tower(class Game* game);
		virtual ~Tower();

	public:
	    virtual void PlaceTower();
	    bool IsPlaced() const;

	public:
	    virtual float GetRange() const =0;
	    void HighlightTowerRange(bool highlight);

	public:
        void SetTargetType(const TowerTargetType& type);
        const TowerTargetType& GetTargetType() const;

	public:
        const std::string& GetName() const;
        class CollisionComponent* GetCollisionComponent() const;

	protected:
	    virtual void UpdateClosestEnemy(float deltaTime);
	    virtual void UpdateFarthestEnemy(float deltaTime);
	    virtual void UpdateFarthestEnemyAlongTrack(float deltaTime);
	    virtual void UpdateStrongestEnemy(float deltaTime);

	protected:
	    virtual void UpdateNonPlacedTower(float deltaTime)=0;
	    virtual void UpdatePlacedTower(float deltaTime)=0;
	    virtual void OnSpawn() override;
	    virtual void OnUpdate(float deltaTime) override;

	private:
	    Actor* SetupRangeHighlight();
		void OnSizeChanged(const Vector2& vec);

	protected:
		class TileSpriteComponent* mSpriteComponent;
		class CollisionComponent* mCollisionComponent;

		class EnemyManager* mEnemyManager;
        class Enemy* mTarget;

	private:
        class Actor* mRangeHighlight;
        class Level* mLevel;

	private:
        TowerTargetType mTargetType;
        std::string mName;
	    bool mPlaced, mHighlighted;
	};
}