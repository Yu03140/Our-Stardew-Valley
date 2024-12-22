#include "HomeScene.h"
#include "FarmGround.h"

USING_NS_CC;

HomeScene* HomeScene::instance = nullptr;

//ʵ�ֵ���ģʽ
HomeScene* HomeScene::getInstance() {
    if (instance == nullptr) {
        instance = HomeScene::create();
    }
    return instance;
}

cocos2d::Scene* HomeScene::createScene() {
    return getInstance();
}

// ��ʼ����Ƭ��ͼ
void HomeScene::initTileMap()
{
    // ����Mines.tmx��Ƭ��ͼ
    tileMap = TMXTiledMap::create("HomeScene.tmx");

}

void HomeScene::changeScene(Event* event)
{
    // ��ȡ������¼�
    auto mouseEvent = dynamic_cast<EventMouse*>(event);
    if (!mouseEvent)
    {
        return;
    }

    Vec2 clickLocation = mouseEvent->getLocationInView();       // ��ȡ���λ��
    auto objectGroup = tileMap->getObjectGroup("Button");       // ��ȡ�����
    if (!objectGroup)
    {
        CCLOG("Button object layer not found.");
        return;
    }

    auto doorObject = objectGroup->getObject("Door");
    auto kitchenObject = objectGroup->getObject("Kitchen");

    // �����л���ť
    auto sprite1 = Sprite::create();
    sprite1->setPosition(Vec2(doorObject["x"].asFloat(), doorObject["y"].asFloat()));
    sprite1->setAnchorPoint(Vec2(0, 0));
    sprite1->setContentSize(Size(doorObject["width"].asFloat() * MapSize, doorObject["height"].asFloat() * MapSize));
    tileMap->addChild(sprite1);
    Vec2 pos1 = sprite1->convertToWorldSpace(Vec2(0, 0));
    CCLOG("POS: %f, %f,%f,%f", clickLocation.x, clickLocation.y, doorObject["width"].asFloat() * MapSize, doorObject["height"].asFloat() * MapSize);
    Rect doorRect = Rect(pos1.x, pos1.y, doorObject["width"].asFloat() * MapSize, doorObject["height"].asFloat() * MapSize);
    if (doorRect.containsPoint(clickLocation))
    {
        CCLOG("Door clicked! Switching scenes...");
        Director::getInstance()->popScene();
    }

    // ����ʳ�ﰴť
    auto sprite2 = Sprite::create();
    sprite2->setPosition(Vec2(kitchenObject["x"].asFloat(), kitchenObject["y"].asFloat()));
    sprite2->setAnchorPoint(Vec2(0, 0));
    sprite2->setContentSize(Size(kitchenObject["width"].asFloat() * MapSize, kitchenObject["height"].asFloat() * MapSize));
    tileMap->addChild(sprite2);
    Vec2 pos2 = sprite2->convertToWorldSpace(Vec2(0, 0));
    //CCLOG("POS: %f, %f,%f,%f", pos.x, pos.y, width, height);
    Rect kitchenRect = Rect(pos2.x, pos2.y, kitchenObject["width"].asFloat() * MapSize, kitchenObject["height"].asFloat() * MapSize);

	if (kitchenRect.containsPoint(clickLocation))
	{
        auto recipeLayer = RecipeLayer::create();
        this->addChild(recipeLayer, Taskbarlayer);
	}
}


// ÿ֡����
void HomeScene::update(float delta)
{
    // ʾ����������������½�ɫ�߼���������̬����
    //CCLOG("MinesScene is updating...");
}

