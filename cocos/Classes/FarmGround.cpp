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


    // 加载瓦片地图（需要将 example.tmx 放在 Resources/ 目录中）
    auto tileMap = TMXTiledMap::create("Farm.tmx");

    if (tileMap) {
        // 成功加载地图，将其作为场景的子节点
        this->addChild(tileMap);
    }
    else {
        CCLOG("Failed to load the tile map");
    }


    // 示例：获取一个对象组并读取对象
    auto objectGroup = tileMap->getObjectGroup("Objects"); // 假设对象组名为 "Objects"
    if (objectGroup) {
        // 获取一个对象（例如：PlayerStart）的位置
        auto playerStart = objectGroup->getObject("PlayerStart");
        float x = playerStart["x"].asFloat();
        float y = playerStart["y"].asFloat();
        CCLOG("Player spawn point: (%f, %f)", x, y);
    }

    return true;
}
