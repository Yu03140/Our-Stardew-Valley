#include "FarmGround.h"
#include "Charactor/BackpackLayer.h"
#include "TimeSystem/TimeSystem.h"

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
    auto tileMap = Sprite::create("homepage.jpg");
    //auto tileMap = TMXTiledMap::create("Farm.tmx");

    if (tileMap) {
        // 成功加载地图，将其作为场景的子节点
        this->addChild(tileMap);
    }
    else {
        CCLOG("Failed to load the tile map");
    }

    // 创建背包图层，并将其添加到场景中
    auto backpackLayer = BackpackLayer::create(); 
    if (backpackLayer) {
        // 设置背景图的尺寸为 2560x1600
        tileMap->setContentSize(Size(2560, 1600)); // 设置背景图的大小

        // 将背景图的位置设置为场景的中心
        tileMap->setPosition(Director::getInstance()->getVisibleSize() / 2);
        
        // 将背包图层添加到场景的子节点，确保它在背景图层上方
        this->addChild(backpackLayer, 1);  
    }

	// 创建时间系统实例
    // 假设 TimeSystem 继承自 Node
    TimeSystem* timeSystem = TimeSystem::getInstance();  // 获取 TimeSystem 的实例

    // 确保当前节点是 Node 类型（通常是 Layer 或 Scene）
    Node* parentNode = this;  

    // 添加 TimeSystem 到 parentNode 中
    parentNode->addChild(timeSystem);



    return true;
}
