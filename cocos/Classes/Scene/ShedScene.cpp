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

bool ShedScene::init() 
{
    SubScene::init();
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto objectGroup_animals = tileMap->getObjectGroup("object");
    if (!objectGroup_animals) {
        CCLOG("Failed to get object group 'object'");
        return false;
    }
    animals_manager = AnimalsManager::create();
    auto objects = objectGroup_animals->getObjects();

    for (const auto& object : objects) {
        CCLOG("cccccccccccccccccccccccccccccccccccccccreate animal");
        // ͨ�� object �е������ж��Ƿ�������Ϊ 'grass' �Ķ���
        auto dict = object.asValueMap();
        std::string objectName = dict["animal"].asString();
        //������������Ϊ�ݵĶ���
        if (objectName == "animal") {

            float posX = dict["x"].asFloat();
            float posY = dict["y"].asFloat();
            float width = dict["width"].asFloat();
            float height = dict["height"].asFloat();
            //��������
            auto animal = animals::create("Animals.plist");
            animal->set_info("Pig", Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y), Size(100, 100));
            animal->set_imag();
            animal->setPosition(Vec2(posX, posY));        // ����λ��
            animal->setAnchorPoint(Vec2(0, 0));     // ����ê��
            animal->setContentSize(Size(width, height));  // ���ô�С
            tileMap->addChild(animal, 2);  // ��ӵ���Ƭ��ͼ
            animal->init_mouselistener();
            animals_manager->add_animals(animal);
            animal->schedule([animal](float dt) {
                animal->update_day(dt);
                }, "update_animal");

        }

    }
    return true;
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

