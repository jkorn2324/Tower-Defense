//
// Created by jkorn on 8/24/2021.
//

#pragma once

#include <string>
#include <unordered_map>

namespace TowerDefense
{

#pragma region upgrade_data

    struct UpgradeTree
    {
        std::string name;
        unsigned int cost;
        bool canceled;
        UpgradeTree* nextUpgrade;

        bool IsMaxed() const { return nextUpgrade == nullptr; }
    };

#pragma endregion

#pragma region upgrades_manager

    class UpgradesManager
    {
    public:
        UpgradesManager(class Game* game);
        ~UpgradesManager();

    public:
        void AddUpgradeTree(const std::string& treeName, UpgradeTree* tree);
        UpgradeTree* GetUpgradeTree(const std::string& upgradeTree) const;

    private:
        void InitializeUpgrades();

    private:
        Game* mGame;
        std::unordered_map<std::string, UpgradeTree*> mUpgradeTrees;
    };

#pragma endregion
}
