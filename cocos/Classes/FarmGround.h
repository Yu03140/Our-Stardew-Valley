#ifndef __FARM_GROUND_H__
#define __FARM_GROUND_H__

#include "cocos2d.h"

class FarmScene : public cocos2d::Scene {
    cocos2d::TMXTiledMap* tileMap;
    cocos2d::Sprite* player;
public:
    // ���� FarmScene
    static FarmScene* createScene();

    // ��ʼ������
    virtual bool init();

    // �궨�壬���ڴ�������
    CREATE_FUNC(FarmScene);
};

#endif // __FARM_GROUND_H__
