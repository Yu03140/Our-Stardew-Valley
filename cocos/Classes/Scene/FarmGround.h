#ifndef __FARM_GROUND_H__
#define __FARM_GROUND_H__

#include "cocos2d.h"
#include "Charactor/BackpackLayer.h"
#include "Moveable/moveable_sprite_key.h"
#include "Global/Global.h"
#include "GetableItem/Crop.h"
#include "GetableItem/Animals.h"
#include "Fish.h"


#define MapSize 4
#define TOOL_WIDTH 40
#define TOOL_HEIGHT 60

    struct Crops {
        std::string name;        // 物品名称
        crop* sprite; // 显示物品的精灵
    };
    struct Barrier {
        std::string name;        // 障碍物名称
        Sprite* sprite; // 显示物品的精灵
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
        //  void removeItem(const std::string& itemName);

        CREATE_FUNC(FarmScene); // 使用 CREATE_FUNC 宏

        // 瓦片地图
        cocos2d::TMXTiledMap* tileMap;
//===========================================================================================================================
        // 更新方法，每帧调用
        void update(float dt, moveable_sprite_key_walk* sprite_move);
        bool checkCollisionWithBorder(cocos2d::Vec2 position);  // 新增的碰撞检测函数

        // 替换房子图片
        void replaceHouseImage();

        // 精灵指针
        cocos2d::Sprite* badWarmHouse;
        void checkForwarmhouseClick(Vec2 mousePosition);
     //   void createFish(Vec2 mousePosition);

        void checkForPoolClick(Vec2 mousePosition);

        // 启动钓鱼的方法
     //   void startFishing(Vec2 fishingPosition);

//===========================================================================================================================


    private:
//===========================================================================================================================
        cocos2d::Sprite* house;                   // 房子精灵
        cocos2d::Sprite* shed;                   // 棚屋精灵
        bool isFishing = false;  // 是否正在钓鱼
      //  cocos2d::Vec2 fishingTarget;  // 钓鱼目标位置
        Fish* fish;
        // 创建鱼实例
       moveable_sprite_key_walk* sprite_move;  // 人物控制类的引用
//===========================================================================================================================


        // 更新和清除物品纹理
        void updateItemTexture(int slotIndex);
        void clearItemTexture(int slotIndex);

        // 更新摄像机位置
        void updateCameraPosition(float dt, Node* player);

        // 农作物数据
        std::vector<Crops> crops;
//===========================================================================================================================
        std::vector<Barrier> barrier;
//===========================================================================================================================

        static FarmScene* instance;

        // 初始化鼠标监听器
        void init_mouselistener();

        // 鼠标回调
        void on_mouse_click(cocos2d::Event* event);


    };

#endif // __FARM_GROUND_H__于创建场景