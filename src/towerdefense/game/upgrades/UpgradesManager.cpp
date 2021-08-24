//
// Created by jkorn on 8/24/2021.
//

#include "UpgradesManager.h"


namespace TowerDefense
{

    UpgradesManager::UpgradesManager(class Game *game)
    {
        mGame = game;
        mUpgradeTrees = std::unordered_map<std::string, UpgradeTree*>();
        InitializeUpgrades();
    }

    UpgradesManager::~UpgradesManager()
    {
        for(const auto& upgradeTree : mUpgradeTrees)
        {
            UpgradeTree* tree = upgradeTree.second;
            while(tree->nextUpgrade != nullptr)
            {
                UpgradeTree* nextTreeTemp = tree->nextUpgrade;
                delete tree;
                tree = nextTreeTemp;
            }
        }
        mUpgradeTrees.clear();
    }

    void UpgradesManager::InitializeUpgrades()
    {
        // TODO: Implementation
    }

    void UpgradesManager::AddUpgradeTree(const std::string &treeName, UpgradeTree *tree)
    {
        const auto& searchedUpgradeTree = mUpgradeTrees.find(treeName);
        if(searchedUpgradeTree == mUpgradeTrees.end())
        {
            mUpgradeTrees.emplace(treeName, tree);
        }
    }

    UpgradeTree* UpgradesManager::GetUpgradeTree(const std::string &upgradeTree) const
    {
        const auto& searchedUpgradeTree = mUpgradeTrees.find(upgradeTree);
        if(searchedUpgradeTree != mUpgradeTrees.end())
        {
            return searchedUpgradeTree->second;
        }
        return nullptr;
    }
}