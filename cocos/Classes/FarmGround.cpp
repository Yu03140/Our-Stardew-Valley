#include "FarmGround.h"

USING_NS_CC;

FarmScene* FarmScene::createScene() {
    // 创建并返回 FarmScene 场景对象
    return FarmScene::create();
}


bool FarmScene::init() {
    // 调用父类的初始化函数
    if (!Scene::init()) {
        return false;
    }
    // 获取屏幕可见区域的大小和原点
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 创建并添加TMX地图
    tileMap = TMXTiledMap::create("Content/Maps/Farm.tmx");
    if (tileMap) {
        CCLOG("TileMap loaded successfully. Map size: %f x %f",
            tileMap->getContentSize().width,
            tileMap->getContentSize().height);
        Size visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        tileMap->setPosition(Vec2(origin.x + visibleSize.width / 2 - tileMap->getContentSize().width / 2,
            origin.y + visibleSize.height / 2 - tileMap->getContentSize().height / 2));

        addChild(tileMap, 0, 100);
    }
    else {
        CCLOG("Failed to load TMX file: csva.tmx");
        return false;
    }

    //addChild(sprite); // 如果图片加载成功，它将显示在场景中


    // 将玩家精灵添加到场景中
    //addChild(player, 2, 200);


    return true;
}
