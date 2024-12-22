#ifndef __FARM_GROUND_H__
#define __FARM_GROUND_H__

#include "cocos2d.h"
#include "Charactor/BackpackLayer.h"
#include "Moveable/moveable_sprite_key.h"
#include "Global/Global.h"
#include "GetableItem/Crop.h"
#include "GetableItem/Animals.h"
#include "NPC/NPC.h"
#include "MinesScene.h"
#include "HomeScene.h"
#include "ShedScene.h"

#define MapSize 4
#define TOOL_WIDTH 40
#define TOOL_HEIGHT 60

    struct Crops {
        std::string name;        // 物品名称
        crop* sprite; // 显示物品的精灵
    };

    class FarmScene : public cocos2d::Scene {

    public:
        // 创建 FarmScene
        static FarmScene* getInstance();
        static Scene* createScene();
        // 初始化函数
        virtual bool init();
        // 添加或移除物品
        void addItem(const std::string& itemName);

        CREATE_FUNC(FarmScene); // 使用 CREATE_FUNC 宏

        // 瓦片地图
        cocos2d::TMXTiledMap* tileMap;


		// 鼠标点击事件处理函数


    private:
        // 更新和清除物品纹理
        void updateItemTexture(int slotIndex);
        void clearItemTexture(int slotIndex);

        // 更新摄像机位置
        void updateCameraPosition(float dt, Node* player);

        // 农作物数据
        std::vector<Crops> crops;

        static FarmScene* instance;

        // 初始化鼠标监听器
        void init_mouselistener();

        // 鼠标回调
        void on_mouse_click(cocos2d::Event* event);

        void checkForButtonClick(Vec2 mousePosition);

        void onEnter();

        NPC* npc1;                      // NPC对象
        NPC* npc2;
        // 检查玩家是否与NPC接近并触发互动
        void update(float delta);
        void checkNPCInteraction();

		Board* board;
		TaskBarLayer* taskBarLayer;

    };

#endif // __FARM_GROUND_H__于创建场景