#include "FarmGround.h"
using namespace cocos2d;
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
    tileMap = TMXTiledMap::create("Myfarm.tmx");
   // tileMap = TMXTiledMap::create("shed.tmx");

    if (tileMap) {
        // 获取屏幕的大小
        Size winSize = Director::getInstance()->getWinSize();

        // 设置锚点为中心（以地图中心作为参照点）
        tileMap->setAnchorPoint(Vec2(0.5, 0.5));

        tileMap->setScale(0.8f);

        // 获取地图的原始尺寸（不考虑缩放）
        Size mapSize = tileMap->getContentSize();

        // 计算地图的位置，将地图放置在屏幕中央
        float posX = winSize.width / 2;
        float posY = winSize.height / 2;
        tileMap->setPosition(Vec2(posX, posY));

        // 将地图添加到场景中
        this->addChild(tileMap, 0);
    }

    return true;
}
