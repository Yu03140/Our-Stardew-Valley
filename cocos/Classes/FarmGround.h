#ifndef __FARM_GROUND_H__
#define __FARM_GROUND_H__

#include "cocos2d.h"

class FarmScene : public cocos2d::Scene {
    cocos2d::TMXTiledMap* tileMap;
    cocos2d::Sprite* player;
public:
    // 创建 FarmScene
    static FarmScene* createScene();

    // 初始化函数
    virtual bool init();

    // 宏定义，用于创建场景
    CREATE_FUNC(FarmScene);
};

#endif // __FARM_GROUND_H__
