#include "MinesScene.h"

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


// ��ʼ����Ƭ��ͼ
void MinesScene::initTileMap()
{
    // ����Mines.tmx��Ƭ��ͼ
    tileMap = TMXTiledMap::create("Mines.tmx");

    //----------------------------------------------------
    // ���ܣ���ʯģ��
    // ˵�����ڵ�ͼ����ӿ�ʯ���ӣ��������ɿ�ʯ
    // ͼ�㣺Playerlayer
    //----------------------------------------------------
    // ��ȡ����㣨ÿ��������ӵ�λ�ã�
    auto objectGroup_stone = tileMap->getObjectGroup("stone");
    if (!objectGroup_stone) {
        CCLOG("Failed to get object group 'stone'");
    }

    // ʯͷ���ӹ���
    GoodsManager* stone_manager = GoodsManager::create();
    GoodsManager* mine_manager = GoodsManager::create();
    GoodsManager* bigstone_manager = GoodsManager::create();
    auto objects = objectGroup_stone->getObjects();

    for (const auto& object : objects) {
        // ͨ�� object �е������ж��Ƿ�������Ϊ 'stone' �Ķ���
        auto dict = object.asValueMap();
        std::string objectName = dict["name"].asString();
        auto sprite = getable_goods::create("goods.plist");
        CCLOG("objectName: %s", objectName.c_str());
        //����ʯͷ
        if (objectName == "stone") {
            sprite->add_in(dict, sprite, "stones", tileMap);
            //����ʯͷ���ӹ�����
            stone_manager->add_goods(sprite);
        }
        //�����ʯ
        else if (objectName == "mine") {
            sprite->add_in(dict, sprite, "mine", tileMap);
            //�����ʯ���ӹ�����
            mine_manager->add_goods(sprite);
        }
        //�����ʯͷ
        else if (objectName == "big_stone") {
            sprite->add_in(dict, sprite, "bigstone", tileMap);
            //�����ʯͷ���ӹ�����
            bigstone_manager->add_goods(sprite);
        }
    }
    this->addChild(stone_manager);
    stone_manager->schedule([stone_manager](float delta) {
        stone_manager->random_access();
        }, 6.0f, "RandomAccessSchedulerKey");
    this->addChild(mine_manager);
    mine_manager->schedule([mine_manager](float delta) {
        mine_manager->random_access();
        }, 6.0f, "RandomAccessSchedulerKey");
    this->addChild(bigstone_manager);
    bigstone_manager->schedule([bigstone_manager](float delta) {
        bigstone_manager->random_access();
        }, 6.0f, "RandomAccessSchedulerKey");

}

void MinesScene::changeScene(Event* event)
{
    // ��ȡ������¼�
    auto mouseEvent = dynamic_cast<EventMouse*>(event);
    if (!mouseEvent)
    {
        return;
    }

    // ��ȡ���λ��
    Vec2 clickLocation = mouseEvent->getLocationInView();

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
        CCLOG("Door clicked! Switching scenes...");
        Director::getInstance()->popScene();
    }
}