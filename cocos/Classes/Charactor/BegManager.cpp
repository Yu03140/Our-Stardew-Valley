

#include "BegManager.h"

BackpackManager* BackpackManager::getInstance() {
    static BackpackManager instance;
    return &instance;
}

BackpackManager::BackpackManager() {}

BackpackManager::~BackpackManager() {
    items.clear();
}

void BackpackManager::addItem(const std::string& itemName, const std::string& itemImage) {
    items.push_back(std::make_pair(itemName, itemImage));
}

const std::vector<std::pair<std::string, std::string>>& BackpackManager::getItems() const {
    return items;
}

void BackpackManager::clear() {
    items.clear();
}
