#ifndef __FARM_GROUND_H__
#define __FARM_GROUND_H__

#include "cocos2d.h"
#include "Charactor/BackpackLayer.h"
#include "Moveable/moveable_sprite_key.h"
#include "Global/Global.h"
#include "NPC/NPC.h"//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@2这里！！！！记得修改文件夹路径
#include "TimeSystem/TimeSystem.h"


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
    //-------renew(dxn)-------------------------------------------------------
    NPC* npc1;                      // NPC对象
    NPC* npc2;
    // 检查玩家是否与NPC接近并触发互动
    void update(float delta);
    void checkNPCInteraction();
    //--------------end----------------------------------------------------------

};

#endif // __FARM_GROUND_H__