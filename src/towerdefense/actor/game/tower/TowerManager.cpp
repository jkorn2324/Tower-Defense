#include "TowerManager.h"

#include "Level.h"
#include "Game.h"
#include "CollisionComponent.h"
#include "Tower.h"

#include <algorithm>
#include <cmath>

namespace TowerDefense
{

    TowerManager::TowerManager(Level *level)
    {
        mLevel = level;
        mGame = level->GetGame();
        mTowers = std::vector<Tower*>();
    }

    const std::vector<Tower*>& TowerManager::GetTowers() const { return mTowers; }

    Level* TowerManager::GetLevel() const { return mLevel; }

    Tower* TowerManager::GetTowerAtPosition(const Vector2 &position) const
    {
        std::vector<TowerData> towers;
        for(const auto& tower : mTowers)
        {
            if(!tower->IsPlaced())
            {
                continue;
            }
            CollisionComponent* towerCollision = tower->GetCollisionComponent();
            if(towerCollision->ContainsPosition(position))
            {
                float calculatedDistance = std::abs(Vector2::Distance(
                        tower->GetTransform().GetPosition(), position));
                TowerData towerData;
                towerData.distance = calculatedDistance;
                towerData.tower = tower;
                towers.push_back(towerData);
            }
        }
        if(towers.empty())
        {
            return nullptr;
        }

        unsigned int towerSize = towers.size();
        if(towerSize == 1)
        {
            return towers[0].tower;
        }

        TowerData closestTower = towers[0];
        for(unsigned int i = 1; i < towerSize; i++)
        {
            auto testTowerData = towers[i];
            if(testTowerData.distance < closestTower.distance)
            {
                closestTower = testTowerData;
            }
        }
        return closestTower.tower;
    }

    bool TowerManager::CanPlaceTower(const Vector2 &point) const
    {
        Tower* tower = GetTowerAtPosition(point);
        return tower == nullptr;
    }

    void TowerManager::AddTower(class Tower *tower)
    {
        mTowers.push_back(tower);
    }

    void TowerManager::RemoveTower(class Tower *tower)
    {
        const auto& foundTower = std::find(mTowers.begin(), mTowers.end(), tower);
        mTowers.erase(foundTower);
    }

    void TowerManager::ClearTowers()
    {
        for(const auto& tower : mTowers)
        {
            tower->Despawn();
        }
    }
}