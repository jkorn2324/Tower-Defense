#include "LevelTowerAreaRect.h"

#include "Level.h"

namespace TowerDefense
{

    LevelTowerAreaRect::LevelTowerAreaRect(const Vector2& size, const Vector2& pos)
    {
        this->size = size;
        this->pos = pos;
    }

    bool LevelTowerAreaRect::IsWithinBounds(const Vector2 &point) const
    {
        Vector2 min = GetMin();
        Vector2 max = GetMax();
        return point.x >= min.x && point.x <= max.x
            && point.y >= min.y && point.y <= max.y;
    }

    Vector2 LevelTowerAreaRect::GetMin() const
    {
        Vector2 min(pos);
        min.y -= size.y;
        return min;
    }

    Vector2 LevelTowerAreaRect::GetMax() const
    {
        Vector2 max(pos);
        max.x += size.x;
        return max;
    }

    LevelTowersAreaManager::LevelTowersAreaManager(Level *level)
    {
        mLevel = level;
        mTowerAreas = std::vector<LevelTowerAreaRect*>();
    }

    LevelTowersAreaManager::~LevelTowersAreaManager()
    {
        for(const auto& levelTower : mTowerAreas)
        {
            delete levelTower;
        }
        mTowerAreas.clear();
    }

    void LevelTowersAreaManager::AddTowerArea(const Vector2 &size, const Vector2 &pos)
    {
        LevelTowerAreaRect* rect = new LevelTowerAreaRect(size, pos);
        mTowerAreas.push_back(rect);
    }

    bool LevelTowersAreaManager::CanPlaceTower(const Vector2 &point) const
    {
        for(const auto& rect : mTowerAreas)
        {
            if(rect->IsWithinBounds(point))
            {
                return true;
            }
        }
        return false;
    }
}