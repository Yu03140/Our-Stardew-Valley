#include "ShedScene.h"
#include "FarmGround.h"

USING_NS_CC;

ShedScene* ShedScene::instance = nullptr;

//ʵ�ֵ���ģʽ
ShedScene* ShedScene::getInstance() {
    if (instance == nullptr) {
        instance = ShedScene::create();
    }
    return instance;
}

cocos2d::Scene* ShedScene::createScene() {
    return getInstance();
}

// ��ʼ����Ƭ��ͼ
void ShedScene::initTileMap()
{
    // ����shed.tmx��Ƭ��ͼ
    tileMap = TMXTiledMap::create("shed.tmx");

}

void ShedScene::changeScene(Event* event)
{
    // ��ȡ������¼�
    auto mouseEvent = dynamic_cast<EventMouse*>(event);
    if (!mouseEvent)
    {
        return;
    }

    // ��ȡ���λ��
    Vec2 clickLocation = mouseEvent->getLocationInView();
    CCLOG("clickLocation: ( %f , %f )", clickLocation.x, clickLocation.y);

    // ��ȡ�����
    auto objectGroup = tileMap->getObjectGroup("Button");
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

    // ��������Ƿ��ڶ���Χ��
    if (doorRect.containsPoint(clickLocation))
    {
        /*
        if (backpackLayer)
            this->removeChild(backpackLayer);  // �Ƴ�������
        */
        CCLOG("Door clicked! Switching scenes...");
        Director::getInstance()->popScene();
    }
}

