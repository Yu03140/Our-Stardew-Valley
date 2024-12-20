#ifndef __MINES_SCENE_H__
#define __MINES_SCENE_H__

#include "cocos2d.h"

class MinesScene : public cocos2d::Scene
{
public:

    static MinesScene* getInstance();
    static Scene* createScene();

    // 初始化场景
    virtual bool init();

    // 添加一个初始化地图的函数
    void initTileMap();

    // 重写update方法，便于扩展动态逻辑
    virtual void update(float delta) override;

    // 鼠标点击事件处理
    void onMouseDown(cocos2d::Event* event);

    // 使用CREATE_FUNC宏定义create方法
    CREATE_FUNC(MinesScene);

private:
    // 瓦片地图的指针
    cocos2d::TMXTiledMap* _tileMap;

    // 碰撞层或特定的瓦片图层（如果需要处理障碍物或特殊逻辑）
    cocos2d::TMXLayer* _collisionLayer;

    static MinesScene* instance;
};

#endif // __MINES_SCENE_H__
