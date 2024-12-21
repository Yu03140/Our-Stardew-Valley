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



    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /*
    //----------------------------------------------------
    // 功能：添加背包图层
    // 说明：添加背包图层到当前场景，初始化背包
    // 图层：Backpacklayer
    //----------------------------------------------------
    backpackLayer = BackpackLayer::create();
    if (backpackLayer) {
        this->addChild(backpackLayer, Backpacklayer);
        backpackLayer->setName("backpackLayer");
    }
    else
        CCLOG("Failed to load the backpack layer");

    CCLOG("BackpackLayer position: (%f, %f)", backpackLayer->getPositionX(), backpackLayer->getPositionY());
    CCLOG("BackpackLayer size: (%f, %f)", backpackLayer->getContentSize().width, backpackLayer->getContentSize().height);




    //----------------------------------------------------
    // 功能：添加移动主角
    // 说明：添加主角，主角位于地图中央
    // 图层：Playerlayer
    //----------------------------------------------------
    auto sprite_move = moveable_sprite_key_walk::create("Jas_Winter.plist", "Jas_Winter");
    if (sprite_move)
    {
        sprite_move->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        this->addChild(sprite_move, Playerlayer);
        sprite_move->init_keyboardlistener();

        sprite_move->schedule([this, sprite_move](float dt) { // 捕获 `this` 和 `sprite_move`
            sprite_move->update(dt);                         // 更新人物移动逻辑
            }, "update_key_person");

    }
    // 计算经过缩放后的实际尺寸
    Size originalSize = sprite_move->getContentSize();
    float scale = sprite_move->getScale();
    Size scaledSize = Size(originalSize.width * scale, originalSize.height * scale);
    auto sprite_tool = moveable_sprite_key_tool::create("Tools.plist", TOOL_WIDTH, TOOL_HEIGHT);
    if (sprite_tool)
    {
        sprite_tool->setPosition(Vec2(visibleSize.width / 2 + origin.x + scaledSize.width / 2, visibleSize.height / 2 + origin.y));
        this->addChild(sprite_tool, 1);
        sprite_tool->init_keyboardlistener();
        sprite_tool->init_mouselistener();
        sprite_tool->schedule([sprite_tool](float dt) {
            sprite_tool->update(dt);
            }, "update_key_tool");
    }

    */

    return true;
}

// 初始化瓦片地图
void MinesScene::initTileMap()
{
    // 加载Mines.tmx瓦片地图
    MinetileMap = TMXTiledMap::create("Mines.tmx");

    // 加载地图，放在中间
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    MinetileMap = TMXTiledMap::create("Mines.tmx");
    if (MinetileMap) {
        MinetileMap->setAnchorPoint(Vec2(0.5, 0.5));
        float Map_posX = visibleSize.width / 2;
        float Map_posY = visibleSize.height / 2;
        MinetileMap->setPosition(Vec2(Map_posX, Map_posY));
        this->addChild(MinetileMap, 0);
        MinetileMap->setScale(MapSize);
    }
    else {
        CCLOG("Failed to load the tile map");
    }

    /*
    // 获取碰撞层（假设瓦片地图中有一个名为"Collision"的图层）
    _collisionLayer = _tileMap->getLayer("Collision");
    if (_collisionLayer)
    {
        // 设置图层为不可见（仅用于逻辑处理，不需要显示）
        _collisionLayer->setVisible(false);
    }
    */
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
    CCLOG("clickLocation1: ( %f , %f )", clickLocation.x, clickLocation.y);
    clickLocation = Director::getInstance()->convertToGL(clickLocation);


    // 将点击位置转换为瓦片地图坐标
    Vec2 mapCoord = MinetileMap->convertToNodeSpace(clickLocation);
    auto visibleSize = Director::getInstance()->getVisibleSize();
    mapCoord.y = visibleSize.height / MapSize - mapCoord.y;
    CCLOG("clickLocation2: ( %f , %f )", mapCoord.x, mapCoord.y);

    // 获取对象层
    auto objectGroup = MinetileMap->getObjectGroup("Button");
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
    CCLOG("x:%f,y:%f", x, y);

    // 检查点击点是否在对象范围内
    if (doorRect.containsPoint(mapCoord))
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
void MinesScene::update(float delta)
{
    // 示例：可以在这里更新角色逻辑或其他动态内容
    //CCLOG("MinesScene is updating...");
}

