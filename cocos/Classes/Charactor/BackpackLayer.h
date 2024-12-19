#ifndef BACKPACK_LAYER_H
#define BACKPACK_LAYER_H

#include "cocos2d.h"

struct ItemSlot {
    std::string name;        // 物品名称
    int quantity;            // 物品数量
    cocos2d::Sprite* sprite; // 显示物品的精灵
};

class BackpackLayer : public cocos2d::Layer {
public:
    BackpackLayer();
    virtual ~BackpackLayer();

    static BackpackLayer* create();
    virtual bool init();

    // 鼠标点击事件处理函数
    void onMouseDown(cocos2d::Event* event);

    // 添加或移除物品
    bool BackpackLayer::addItem(const std::string& itemName, const int num = 1);
    bool BackpackLayer::removeItem(const std::string& itemName, const int num = 1);


	// 得到选中的物品
    std::string getSelectedItem() const;

    // 瓦片地图
    cocos2d::TMXTiledMap* tilemap;

private:

    float X0;
    float Y0;
    std::string selectedItem;
    // 更新和清除物品纹理
    void updateItemTexture(int slotIndex);
    void clearItemTexture(int slotIndex);

    // 背包格子数据
    std::vector<ItemSlot> itemSlots;
};

#endif // BACKPACK_LAYER_H
