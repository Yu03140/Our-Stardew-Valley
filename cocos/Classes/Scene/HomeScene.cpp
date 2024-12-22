#include "HomeScene.h"
#include "FarmGround.h"

USING_NS_CC;

HomeScene* HomeScene::instance = nullptr;

//实现单例模式
HomeScene* HomeScene::getInstance() {
    if (instance == nullptr) {
        instance = HomeScene::create();
    }
    return instance;
}

cocos2d::Scene* HomeScene::createScene() {
    return getInstance();
}

// 初始化瓦片地图
void HomeScene::initTileMap()
{
    // 加载Mines.tmx瓦片地图
    tileMap = TMXTiledMap::create("HomeScene.tmx");

}

void HomeScene::changeScene(Event* event)
{
    // 获取鼠标点击事件
    auto mouseEvent = dynamic_cast<EventMouse*>(event);
    if (!mouseEvent)
    {
        return;
    }

    // 获取点击位置
    Vec2 clickLocation = mouseEvent->getLocationInView();
    CCLOG("clickLocation: ( %f , %f )", clickLocation.x, clickLocation.y);

    // 获取对象层
    auto objectGroup = tileMap->getObjectGroup("Button");
    if (!objectGroup)
    {
        CCLOG("Button object layer not found.");
        return;
    }
    // 获取名为 "Door" 的对象
    auto doorObject = objectGroup->getObject("Door");
    if (doorObject.empty())
    {
        CCLOG("Door object not found.");
        return;
    }
    // 获取对象的属性和范围
    float x = doorObject["x"].asFloat();
    float y = doorObject["y"].asFloat();
    float width = doorObject["width"].asFloat() * MapSize;
    float height = doorObject["height"].asFloat() * MapSize;
    CCLOG("x:%f,y:%f", x, y);
    auto sprite = Sprite::create();
    sprite->setPosition(Vec2(x, y));
    sprite->setAnchorPoint(Vec2(0, 0));
    sprite->setContentSize(Size(width, height));
    tileMap->addChild(sprite);
    Vec2 pos = sprite->convertToWorldSpace(Vec2(0, 0));
    CCLOG("POS: %f, %f,%f,%f", pos.x, pos.y, width, height);

    Rect doorRect = Rect(pos.x, pos.y, width, height);

    // 检查点击点是否在对象范围内
    if (doorRect.containsPoint(clickLocation))
    {
        /*
        if (backpackLayer)
            this->removeChild(backpackLayer);  // 移除背包层
        */
        CCLOG("Door clicked! Switching scenes...");
        Director::getInstance()->popScene();
    }
}


// 每帧更新
void HomeScene::update(float delta)
{
    // 示例：可以在这里更新角色逻辑或其他动态内容
    //CCLOG("MinesScene is updating...");
}

