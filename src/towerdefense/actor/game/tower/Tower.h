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

    enum TowerType
    {
        DEFAULT_TOWER_TYPE,
        GREEN_CANNON_TOWER_TYPE
    };


	class Tower : public Actor
	{

	public:
		explicit Tower(class Game* game);
		virtual ~Tower();

	public:
	    virtual void OnSelected();
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
        const TowerType& GetType() const;
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
	    virtual void OnDespawn() override;
	    virtual void OnUpdate(float deltaTime) override;
        virtual bool ShouldUpdateTarget() const;

	private:
        void GenerateName();
        Actor* SetupRangeHighlight();
		void OnSizeChanged(const Vector2& vec);

	protected:
        class ScaleSelectAnimationComponent* mScaleSelectAnimationComponent;
        class TileSpriteComponent* mSpriteComponent;
		class CollisionComponent* mCollisionComponent;

		class EnemyManager* mEnemyManager;
        class Enemy* mTarget;

	private:
        class Actor* mRangeHighlight;
        class Level* mLevel;

	private:
	    TowerType mTowerType;
        TowerTargetType mTargetType;
        std::string mName;
	    bool mPlaced, mHighlighted;

	public:
	    static Tower* CreateTowerFromType(class Game* game, const TowerType& towerType);
	};
}