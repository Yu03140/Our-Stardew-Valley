#ifndef __BACKPACK_LAYER_H__
#define __BACKPACK_LAYER_H__

#include "cocos2d.h"

class BackpackLayer : public cocos2d::Layer
{
public:
    // 构造函数与析构函数
    BackpackLayer();
    ~BackpackLayer();

    // 创建背包界面
    static BackpackLayer* create();

    // 初始化函数
    virtual bool init();

    // 添加背包物品
    void addItem(const std::string& itemName, const std::string& itemImage);

    // 切换背包的可见性
    void toggleVisibility();

private:
    // 背包背景精灵
    cocos2d::Sprite* backpackBackground;

    // 物品容器
    std::vector<cocos2d::Sprite*> items;
};

#endif // __BACKPACK_LAYER_H__
