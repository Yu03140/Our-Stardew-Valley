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


// ��ʼ������
bool MinesScene::init()
{
    // ���ø����ʼ������
    if (!Scene::init())
    {
        return false;
    }

    // ��ʼ����Ƭ��ͼ
    initTileMap();

    // ���������¼�������
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseDown = CC_CALLBACK_1(MinesScene::onMouseDown, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

    // ����update����
    this->scheduleUpdate();



    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /*
    //----------------------------------------------------
    // ���ܣ���ӱ���ͼ��
    // ˵������ӱ���ͼ�㵽��ǰ��������ʼ������
    // ͼ�㣺Backpacklayer
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
    // ���ܣ�����ƶ�����
    // ˵����������ǣ�����λ�ڵ�ͼ����
    // ͼ�㣺Playerlayer
    //----------------------------------------------------
    auto sprite_move = moveable_sprite_key_walk::create("Jas_Winter.plist", "Jas_Winter");
    if (sprite_move)
    {
        sprite_move->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        this->addChild(sprite_move, Playerlayer);
        sprite_move->init_keyboardlistener();

        sprite_move->schedule([this, sprite_move](float dt) { // ���� `this` �� `sprite_move`
            sprite_move->update(dt);                         // ���������ƶ��߼�
            }, "update_key_person");

    }
    // ���㾭�����ź��ʵ�ʳߴ�
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

// ��ʼ����Ƭ��ͼ
void MinesScene::initTileMap()
{
    // ����Mines.tmx��Ƭ��ͼ
    MinetileMap = TMXTiledMap::create("Mines.tmx");

    // ���ص�ͼ�������м�
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
    // ��ȡ��ײ�㣨������Ƭ��ͼ����һ����Ϊ"Collision"��ͼ�㣩
    _collisionLayer = _tileMap->getLayer("Collision");
    if (_collisionLayer)
    {
        // ����ͼ��Ϊ���ɼ����������߼���������Ҫ��ʾ��
        _collisionLayer->setVisible(false);
    }
    */
}

void MinesScene::onMouseDown(Event* event)
{
    // ��ȡ������¼�
    auto mouseEvent = dynamic_cast<EventMouse*>(event);
    if (!mouseEvent)
    {
        return;
    }

    // ��ȡ���λ��
    Vec2 clickLocation = mouseEvent->getLocationInView();
    CCLOG("clickLocation1: ( %f , %f )", clickLocation.x, clickLocation.y);
    clickLocation = Director::getInstance()->convertToGL(clickLocation);


    // �����λ��ת��Ϊ��Ƭ��ͼ����
    Vec2 mapCoord = MinetileMap->convertToNodeSpace(clickLocation);
    auto visibleSize = Director::getInstance()->getVisibleSize();
    mapCoord.y = visibleSize.height / MapSize - mapCoord.y;
    CCLOG("clickLocation2: ( %f , %f )", mapCoord.x, mapCoord.y);

    // ��ȡ�����
    auto objectGroup = MinetileMap->getObjectGroup("Button");
    if (!objectGroup)
    {
        CCLOG("Button object layer not found.");
        return;
    }

    // ��ȡ��Ϊ "Door" �Ķ���
    auto doorObject = objectGroup->getObject("Door");
    if (doorObject.empty())
    {
        CCLOG("Door object not found.");
        return;
    }

    // ��ȡ��������Ժͷ�Χ
    float x = doorObject["x"].asFloat();
    float y = doorObject["y"].asFloat();
    float width = doorObject["width"].asFloat();
    float height = doorObject["height"].asFloat();
    Rect doorRect = Rect(x, y, width, height);
    CCLOG("x:%f,y:%f", x, y);

    // ��������Ƿ��ڶ���Χ��
    if (doorRect.containsPoint(mapCoord))
    {
        /*
        if (backpackLayer)
            this->removeChild(backpackLayer);  // �Ƴ�������
        */
        CCLOG("Door clicked! Switching scenes...");
        Director::getInstance()->popScene();
    }
}


// ÿ֡����
void MinesScene::update(float delta)
{
    // ʾ����������������½�ɫ�߼���������̬����
    //CCLOG("MinesScene is updating...");
}

