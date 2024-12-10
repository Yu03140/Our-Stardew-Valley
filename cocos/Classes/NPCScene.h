
#ifndef __NPC_SCENE_H__
#define __NPC_SCENE_H__

#include "cocos2d.h"
#include "NPC.h"

class NPCScene : public cocos2d::Scene {
public:
    NPCScene();
    ~NPCScene();

    // 初始化场景，创建NPC和玩家
    bool init();

    // 创建NPC场景对象
    //static cocos2d::Scene* createScene();

    static NPCScene* create();

    // 更新游戏场景，处理玩家与NPC的交互
    void update(float delta);

private:
    cocos2d::Sprite* playerSprite; // 玩家精灵
    NPC* npc;                      // NPC对象

    // 检查玩家是否与NPC接近并触发互动
    void checkNPCInteraction();
};

#endif // __NPC_SCENE_H__

