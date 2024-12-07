#ifndef __BACKPACK_MANAGER_H__
#define __BACKPACK_MANAGER_H__

#include "cocos2d.h"
#include <vector>

class BackpackManager {
public:
    // 获取背包管理器的单例
    static BackpackManager* getInstance();

    // 添加物品到背包
    void addItem(const std::string& itemName, const std::string& itemImage);

    // 获取背包中的物品列表
    const std::vector<std::pair<std::string, std::string>>& getItems() const;

    // 清空背包
    void clear();

private:
    BackpackManager();
    ~BackpackManager();

    // 保存背包物品的列表
    std::vector<std::pair<std::string, std::string>> items;
};

#endif // __BACKPACK_MANAGER_H__
