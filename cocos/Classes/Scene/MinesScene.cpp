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

    return true;
}

// ��ʼ����Ƭ��ͼ
void MinesScene::initTileMap()
{
    // ����Mines.tmx��Ƭ��ͼ
    _tileMap = TMXTiledMap::create("Mines.tmx");
    this->addChild(_tileMap);

    // ��ȡ��ײ�㣨������Ƭ��ͼ����һ����Ϊ"Collision"��ͼ�㣩
    _collisionLayer = _tileMap->getLayer("Collision");
    if (_collisionLayer)
    {
        // ����ͼ��Ϊ���ɼ����������߼���������Ҫ��ʾ��
        _collisionLayer->setVisible(false);
    }
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
    clickLocation = Director::getInstance()->convertToGL(clickLocation);

    // �����λ��ת��Ϊ��Ƭ��ͼ����
    Vec2 mapCoord = _tileMap->convertToNodeSpace(clickLocation);

    // ��ȡ�����
    auto objectGroup = _tileMap->getObjectGroup("Button");
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

    // ��������Ƿ��ڶ���Χ��
    if (doorRect.containsPoint(mapCoord))
    {
        CCLOG("Door clicked! Switching scenes...");
        auto newScene = FarmScene::createScene(); 
        Director::getInstance()->replaceScene(TransitionFade::create(1.0f, newScene));
    }
}


// ÿ֡����
void MinesScene::update(float delta)
{
    // ʾ����������������½�ɫ�߼���������̬����
    CCLOG("MinesScene is updating...");
}
