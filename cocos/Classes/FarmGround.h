#ifndef __FARM_GROUND_H__
#define __FARM_GROUND_H__
#include "hover_button.h"
#include "moveable_sprite_key.h"
#include "BackpackLayer.h"
#include "TimeSystem.h"

#include "cocos2d.h"
struct Crops {
    std::string name;        // 物品名称
    //  int quantity;            // 物品数量
    cocos2d::Sprite* sprite; // 显示物品的精灵
};


class FarmScene : public cocos2d::Scene {
    cocos2d::TMXTiledMap* tileMap;

public:
    // 创建 FarmScene
    static FarmScene* createScene();

    // 初始化函数
    virtual bool init();
    // 添加或移除物品
    void addItem(const std::string& itemName);
  //  void removeItem(const std::string& itemName);

    // 宏定义，用于创建场景
    CREATE_FUNC(FarmScene);

private:
    // 更新和清除物品纹理
    void updateItemTexture(int slotIndex);
    void clearItemTexture(int slotIndex);

    // 农作物数据
    std::vector<Crops> crops;

    // 瓦片地图
    cocos2d::TMXTiledMap* tilemap;

    // 保存选择的物品
    std::string selectedItemImage;

};

#endif // __FARM_GROUND_H__
