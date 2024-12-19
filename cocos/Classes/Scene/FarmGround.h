#ifndef __FARM_GROUND_H__
#define __FARM_GROUND_H__

#include "cocos2d.h"
#include "Charactor/BackpackLayer.h"
#include "Moveable/moveable_sprite_key.h"
#include "Global/Global.h"
#include "GetableItem/crop.h"
#include "GetableItem/animals.h"

#define MapSize 4
#define TOOL_WIDTH 40
#define TOOL_HEIGHT 60

struct Crops {
    std::string name;        // 物品名称
    crop* sprite; // 显示物品的精灵
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

    // 更新摄像机位置
    void updateCameraPosition(float dt, Node* player);

    // 农作物数据
    std::vector<Crops> crops;

    // 瓦片地图
    cocos2d::TMXTiledMap* tilemap;

};

#endif // __FARM_GROUND_H__