#include "MinesScene.h"
#include "FarmGround.h"

USING_NS_CC;

MinesScene* MinesScene::instance = nullptr;

MinesScene* MinesScene::getInstance() {
    if (instance == nullptr) {
        instance = MinesScene::create();
    }
    return instance;
}

Scene* MinesScene::createScene() {
    return getInstance();
}


// 初始化场景
bool MinesScene::init()
{
    // 调用父类初始化方法
    if (!Scene::init())
    {
        return false;
    }

    // 初始化瓦片地图
    initTileMap();

    // 添加鼠标点击事件监听器
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseDown = CC_CALLBACK_1(MinesScene::onMouseDown, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

    // 开启update函数
    this->scheduleUpdate();

    return true;
}

// 初始化瓦片地图
void MinesScene::initTileMap()
{
    // 加载Mines.tmx瓦片地图
    _tileMap = TMXTiledMap::create("Mines.tmx");
    this->addChild(_tileMap);

    // 获取碰撞层（假设瓦片地图中有一个名为"Collision"的图层）
    _collisionLayer = _tileMap->getLayer("Collision");
    if (_collisionLayer)
    {
        // 设置图层为不可见（仅用于逻辑处理，不需要显示）
        _collisionLayer->setVisible(false);
    }
}

void MinesScene::onMouseDown(Event* event)
{
    // 获取鼠标点击事件
    auto mouseEvent = dynamic_cast<EventMouse*>(event);
    if (!mouseEvent)
    {
        return;
    }

    // 获取点击位置
    Vec2 clickLocation = mouseEvent->getLocationInView();
    clickLocation = Director::getInstance()->convertToGL(clickLocation);

    // 将点击位置转换为瓦片地图坐标
    Vec2 mapCoord = _tileMap->convertToNodeSpace(clickLocation);

    // 获取对象层
    auto objectGroup = _tileMap->getObjectGroup("Button");
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
    float width = doorObject["width"].asFloat();
    float height = doorObject["height"].asFloat();
    Rect doorRect = Rect(x, y, width, height);

    // 检查点击点是否在对象范围内
    if (doorRect.containsPoint(mapCoord))
    {
        CCLOG("Door clicked! Switching scenes...");
        auto newScene = FarmScene::createScene(); 
        Director::getInstance()->replaceScene(TransitionFade::create(1.0f, newScene));
    }
}


// 每帧更新
void MinesScene::update(float delta)
{
    // 示例：可以在这里更新角色逻辑或其他动态内容
    CCLOG("MinesScene is updating...");
}
