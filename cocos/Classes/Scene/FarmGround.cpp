#include "FarmGround.h"

USING_NS_CC;

FarmScene* FarmScene::instance = nullptr;
moveable_sprite_key_walk* sprite_move = nullptr;

bool FarmScene::init() {
    // ���ø���ĳ�ʼ������

    if (!Scene::init()) {
        return false;
    }
    //=====================================12.22========================================================================




    //=====================================12.22=================================================================================

    init_mouselistener();
        // ���ص�ͼ�������м�
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    tileMap = TMXTiledMap::create("Myfarma.tmx");
    if (tileMap) {
        tileMap->setAnchorPoint(Vec2(0.5, 0.5));
        float posX = visibleSize.width / 2;
        float posY = visibleSize.height / 2;
        tileMap->setPosition(Vec2(posX, posY));
        this->addChild(tileMap, 0);
        tileMap->setScale(MapSize);
        SceneWidth = tileMap->getContentSize().width * MapSize;
        SceneHeight = tileMap->getContentSize().height * MapSize;

        CCLOG("Loaded the tile map successfully: (%f,%f)", SceneWidth, SceneHeight);
    }
    else {
        CCLOG("Failed to load the tile map");
    }
    //===========================================================================================================================
    house = Sprite::create("houses.png"); // �滻Ϊ��ķ���ͼƬ·��
    house->setPosition(Vec2(600, 600)); // ���÷��ӵĳ�ʼλ��
    house->setScale(MapSize);
    this->addChild(house);

    shed= Sprite::create("Big Shed.png"); // �滻Ϊ��ķ���ͼƬ·��
    shed->setPosition(Vec2(0, 1100)); // ���÷��ӵĳ�ʼλ��
    shed->setScale(MapSize);
    this->addChild(shed);

    badWarmHouse = Sprite::create("badGreenhouse.png"); // �滻Ϊ��ķ���ͼƬ·��
    badWarmHouse->setPosition(Vec2(-330, 0)); // ���÷��ӵĳ�ʼλ��
    badWarmHouse->setScale(MapSize);
    this->addChild(badWarmHouse);


    //===========================================================================================================================

    //----------------------------------------------------
    // ���ܣ������ʼ��
    // ˵��������������󣬳�ʼ����������
    // ͼ�㣺
    //----------------------------------------------------
    Player* player = Player::getInstance("me");

    //----------------------------------------------------
    // ���ܣ���ӱ���ͼ��
    // ˵������ӱ���ͼ�㵽��ǰ��������ʼ������
    // ͼ�㣺Backpacklayer
    //----------------------------------------------------
    backpackLayer = BackpackLayer::create();
    if (backpackLayer) {
        this->addChild(backpackLayer, Backpacklayer);
    }
    else
        CCLOG("Failed to load the backpack layer");


    //----------------------------------------------------
    // ���ܣ����ʱ��ϵͳ
    // ˵�������ʱ��ϵͳ����ǰ��������ʼ��ʱ��ϵͳ
    // ͼ�㣺Timesystemlayer
    //----------------------------------------------------
    timeSystem = TimeSystem::getInstance();
    Node* parentNode = this;
    if (timeSystem->getParent() == nullptr) {
        parentNode->addChild(timeSystem, Timesystemlayer);
    }

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
            updateCameraPosition(dt, sprite_move);                 // �������λ��
            }, "update_key_person");
 //===========================================================================================================================

        schedule([this, sprite_move](float dt) {
            this->update(dt, sprite_move);  // ���� sprite_move ��Ϊ����
            }, "update_key_scene");
        CCLOG("diao yong cheng gong la");

    }
//===========================================================================================================================

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


    //auto animal = animals::create("Animals.plist", "Pig", Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y),Size(100,100));
    //if (animal)
    //{
    //    animal->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    //    this->addChild(animal, 1);
    //    animal->init_mouselistener();
    //    animal->scheduleRandomMove(tileMap);
    //    animal->schedule([animal](float dt) {
    //        animal->update(dt);
    //        }, "update_animal");
    //}


    //----------------------------------------------------
    // ���ܣ����������
    // ˵�����������������ǰ����
    // ͼ�㣺Taskbarlayer
    //----------------------------------------------------
    auto taskBarScene = TaskBarLayer::create();
    tileMap->addChild(taskBarScene, 3);

    //----------------------------------------------------
    // ���ܣ�����ģ��
    // ˵�����ڵ�ͼ�����������ӣ�������ֲ����
    // ͼ�㣺Playerlayer
    //----------------------------------------------------
    // ��ȡ����㣨ÿ��������ӵ�λ�ã�
    auto objectGroup = tileMap->getObjectGroup("crops_layer");
    if (!objectGroup) {
        CCLOG("Failed to get object group 'crops_layer'");
        return false;
    }

    Vec2 map_pos = tileMap->getPosition();
    // ������ӹ����������36��
    crops.resize(36);
    for (int i = 0; i < 36; ++i) {

        crops[i].name = "";      // ������

        // ��ȡ�������ÿ�����ӵ�����
        auto object = objectGroup->getObject("crop" + std::to_string(i + 1));  // ��ȡ�� i+1 ������
        float posX = object["x"].asFloat();
        float posY = object["y"].asFloat();
        float width = object["width"].asFloat();
        float height = object["height"].asFloat();

		CCLOG("Crop %d: x=%f, y=%f, width=%f, height=%f", i, posX, posY, width, height);


        // ����͸������ľ���
        auto sprite = crop::create("crop_m.plist", width, height); // Ĭ��������

        sprite->setPosition(Vec2(posX, posY));        // ����λ��
        sprite->setAnchorPoint(Vec2(0, 0));     // ����ê��
        sprite->setContentSize(Size(width, height));  // ���ô�С
        tileMap->addChild(sprite, 2);  // ��ӵ���Ƭ��ͼ
        sprite->init_mouselistener();
        crops[i].sprite = sprite;
        //Vec2 worldPos = sprite->convertToWorldSpace(Vec2(0, 0));
        //log("World Position: x=%f, y=%f", worldPos.x, worldPos.y);


        sprite->schedule([sprite](float dt) {
            sprite->update_day(dt);
            }, "update_crop");

    }
//===========================================================================================================================

    //----------------------------------------------------
    // ���ܣ�����ģ��
    // ˵����
    // ͼ�㣺
    //----------------------------------------------------
    // ��ȡ����㣨ÿ����λ�ã�
    auto barriersobjectGroup = tileMap->getObjectGroup("barriers");
    if (!objectGroup) {
        CCLOG("Failed to get object group 'barriers'");
        return false;
    }

   // Vec2 map_pos = tileMap->getPosition();

    auto object = barriersobjectGroup->getObject("barrier9");
    float posX = object["x"].asFloat();
    float posY = object["y"].asFloat();
    float width = object["width"].asFloat() * MapSize;
    float height = object["height"].asFloat() * MapSize;
    // ���� barrier ����
    auto sprite = Sprite::create();
    sprite->setPosition(Vec2(posX, posY));
    sprite->setAnchorPoint(Vec2(0, 0));
    sprite->setContentSize(Size(width, height));
    tileMap->addChild(sprite);
    Vec2 pos = sprite->convertToWorldSpace(Vec2(0, 0));
    CCLOG("POS: %f, %f", pos.x, pos.y);

    // ���� Fish ��ʵ��
    Fish* fish = Fish::create("bluefish.png");

    if (fish) {
        // ȷ�����ʵ���ɹ�����
        CCLOG("Fish created successfully.");
        // ���������Ϣ���鿴�����ڴ��ַ
        CCLOG("Fish instance address: %p", fish); // ���fish������ڴ��ַ

        // ����Ƿ�����ȷ��Sprite
        CCLOG("Fish sprite texture: %s", fish->getTexture());

        // �趨����ӵ�����
        // fish->setBarrierProperties(Vec2(posX, posY), width, height);  // ���� barrier ��λ�úʹ�С
        this->addChild(fish);
    }
    else {
        // ���û�гɹ��������ʵ��
        CCLOG("Failed to create fish.");
    }

    // ���fishָ���״̬
    CCLOG("Fish pointer address after creation: %p", fish);


    return true;
}

void FarmScene::update(float dt,moveable_sprite_key_walk* sprite_move) {

    if (!sprite_move ) {
        CCLOG("wandanla");
        return;
    }
    // ��ȡ���ӵı߽�
    Vec2 housePos = house->getPosition();  // ���ӵ�����λ��
    Size houseSize = house->getContentSize() * MapSize;  // ���ӵĳߴ�

    // ��ȡ���������λ��
    Vec2 playerPos = sprite_move->getPosition();

    // �ж������Ƿ��ڷ��ݵľ���������
    bool isPlayerInsideHouse = playerPos.x > housePos.x - houseSize.width / 2 &&
        playerPos.x < housePos.x + houseSize.width / 2 &&
        playerPos.y > housePos.y - houseSize.height / 2 &&
        playerPos.y < housePos.y + houseSize.height / 2;


    // ��ȡ���ӵı߽�
    Vec2 shedPos = shed->getPosition();  // ���ӵ�����λ��
    Size shedSize = shed->getContentSize() * MapSize;  // ���ӵĳߴ�


    // �ж������Ƿ������ݵľ���������
    bool isPlayerInsideshed = playerPos.x > shedPos.x - shedSize.width / 2 &&
        playerPos.x < shedPos.x + shedSize.width / 2 &&
        playerPos.y > shedPos.y - shedSize.height / 2 &&
        playerPos.y < shedPos.y + shedSize.height / 2;

//====================================12.20=================================================================================
//===================================12.21==================================================================================

    // ���������Ƿ��ڷ��������ڣ��������ӵ�͸����
    house->setOpacity(isPlayerInsideHouse ? 128 : 255);
    shed->setOpacity(isPlayerInsideshed ? 128 : 255);

}
//void FarmScene::startFishing(Vec2 fishingPosition) {
//    // ��ʼ�� Fish �������û�еĻ�        
//    CCLOG("jinlailejinlailejinlailejinlailejinlailejinlailejinlailejinlailejinlailejinlailejinlailejinlailejinlailejinlailejinlailejinlailejinlailejinlailejinlailejinlaile");
//
//    if (fish->isFishing()) {
//        CCLOG("ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffish");
//
//        fish->startFishingAtPosition(fishingPosition);
//        CCLOG("diaoyonglediaoyonglediaoyonglediaoyonglediaoyonglediaoyonglediaoyonglediaoyonglediaoyonglediaoyonglediaoyonglediaoyonglediaoyonglediaoyongle");
//
//        isFishing = true;
//    }
//}
// 
// 
// 
// 
// 
// 
// 


// ��ʼ����������
void FarmScene::init_mouselistener()
{
    // ������������
    auto listener = cocos2d::EventListenerMouse::create();

    // ���ص�
    listener->onMouseDown = CC_CALLBACK_1(FarmScene::on_mouse_click, this);

    // ��ȡ�¼��ַ�������Ӽ�����
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

// ��갴��ʱ�Ļص�
void FarmScene::on_mouse_click(cocos2d::Event* event)
{
    //��ȡ����ڴ����е�λ��,ת������ͼ����
    auto mouse_event = dynamic_cast<cocos2d::EventMouse*>(event);
    Vec2 mousePosition = mouse_event->getLocationInView();
    auto camera = Director::getInstance()->getRunningScene()->getDefaultCamera();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 windowOrigin = camera->getPosition() - Vec2(visibleSize.width / 2, visibleSize.height / 2);
    Vec2 mouse_pos = mousePosition + windowOrigin;
    MOUSE_POS = mouse_pos;
    CCLOG("Mouse Position(global): (%f, %f)", MOUSE_POS.x, MOUSE_POS.y);
    checkForwarmhouseClick(mouse_pos);
   // fish->checkForPoolClick(mouse_pos);
    checkForPoolClick(mouse_pos);
    //CCLOG("Fish barrier properties: Pos(%f, %f), Width: %f, Height: %f", fish->barrierPos.x, fish->barrierPos.y, fish->barrierWidth, fish->barrierHeight);

    // 0.1��� MOUSE_POS ��Ϊ (0, 0)�����Ҳ�Ӱ��������������
    this->scheduleOnce([this](float dt) {
        MOUSE_POS = Vec2::ZERO;
        CCLOG("Mouse Position reset to: (%f, %f)", MOUSE_POS.x, MOUSE_POS.y);
        }, 1.5f, "reset_mouse_pos_key");
}


// ���ܣ�����Ƿ�����warmhouse���л�����
void FarmScene::checkForwarmhouseClick(Vec2 mousePosition)
{
    // ��ȡ warmhouse ����㣨warmhouse �������Ϊ "warmhouse"��
    auto objectGroup = tileMap->getObjectGroup("warmhouse");
    if (!objectGroup) {
        CCLOG("Failed to get object group 'warmhouse'");
        return;
    }

    CCLOG("Successed to get object group 'warmhouse'");


    std::string Objectname = "warmhouse";
    Sprite* new_warmhouse = nullptr;


    auto object = objectGroup->getObject(Objectname);
    float posX = object["x"].asFloat();
    float posY = object["y"].asFloat();
    float width = object["width"].asFloat() * MapSize;
    float height = object["height"].asFloat() * MapSize;
    auto sprite = Sprite::create();
    sprite->setPosition(Vec2(posX, posY));
    sprite->setAnchorPoint(Vec2(0, 0));
    sprite->setContentSize(Size(width, height));
    tileMap->addChild(sprite);
    Vec2 pos = sprite->convertToWorldSpace(Vec2(0, 0));
    CCLOG("POS: %f, %f", pos.x, pos.y);

    // �жϵ��λ���Ƿ��� Door ������
    if (mousePosition.x >= pos.x && mousePosition.x <= pos.x + width &&
        mousePosition.y >= pos.y && mousePosition.y <= pos.y + height) {

        replaceHouseImage();


        return;
    }



}


// ���ܣ�����Ƿ�����Pool���л�����
void FarmScene::checkForPoolClick(Vec2 mousePosition)
{
   // Vec2 playerPos = sprite_move->getPosition();

    // ��ȡ barriers ����㣨barriers �������Ϊ "barriers"��
    auto objectGroup = tileMap->getObjectGroup("barriers");
    if (!objectGroup) {
        CCLOG("Failed to get object group 'barriers'");
        return;
    }

    CCLOG("Successed to get object group 'barriers'");


    std::string Objectname = "barrier9";
    // Sprite* new_warmhouse = nullptr;
//    CCLOG("ddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd");


    auto object = objectGroup->getObject(Objectname);
    float posX = object["x"].asFloat();
    float posY = object["y"].asFloat();
    float width = object["width"].asFloat() * MapSize;
    float height = object["height"].asFloat() * MapSize;
    auto sprite = Sprite::create();
    sprite->setPosition(Vec2(posX, posY));
    sprite->setAnchorPoint(Vec2(0, 0));
    sprite->setContentSize(Size(width, height));
    tileMap->addChild(sprite);
    Vec2 pos = sprite->convertToWorldSpace(Vec2(0, 0));
    CCLOG("POS: %f, %f", pos.x, pos.y);

    // �жϵ��λ���Ƿ���������
    if (mousePosition.x >= pos.x && mousePosition.x <= pos.x + width &&
        mousePosition.y >= pos.y && mousePosition.y <= pos.y + height) {
        // ��ȡѡ�е���Ʒ
        std::string selectedItem = backpackLayer->getSelectedItem();
        if (selectedItem == "Rod1") {
            // ��ʼ����
            CCLOG("yyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy");
            CCLOG("%d",fish);

            fish->carry_fishing(mousePosition);
            CCLOG("wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww");

        }
        else {
            CCLOG("Please select a fishing rod first.");
        }
        return;
    }
    
}



// �滻�����ͼƬ
void FarmScene::replaceHouseImage() {
    // �滻Ϊ�µľ���ͼƬ
    badWarmHouse->setTexture("newGreenhouse.png");  // �滻Ϊ�µķ���ͼƬ
}

bool FarmScene::checkCollisionWithBorder(cocos2d::Vec2 position) {
    // ��ȡ��ͼ��ͼ������
    auto layer = tileMap->getLayer("Border");

    // ���ͼ���Ƿ���Ч
    if (!layer) {
        CCLOG("Failed to get Border layer!");
        return false;
    }

    // ��ȡ��ͼ��ͼ���С�͵�����Ƭ�Ĵ�С
    cocos2d::Size layerSize = layer->getLayerSize();
    cocos2d::Size tileSize = layer->getMapTileSize();

    // ��ȡ�������ƫ��λ��
    auto camera = Director::getInstance()->getRunningScene()->getDefaultCamera();
    cocos2d::Vec2 cameraPos = cocos2d::Vec2(camera->getPosition3D().x, camera->getPosition3D().y);  // ��ȡx, y����

    // �����λ��ת��Ϊ����������������
    cocos2d::Vec2 relativePos = position - cameraPos;

    // �����λ��ת��Ϊ tile ����
    cocos2d::Vec2 tileCoord = cocos2d::Vec2(relativePos.x / tileSize.width, relativePos.y / tileSize.height);

    // ��������Ƿ�����Ч��Χ��
    if (tileCoord.x < 0 || tileCoord.x >= layerSize.width || tileCoord.y < 0 || tileCoord.y >= layerSize.height) {
     //   CCLOG("Position is out of bounds: (%f, %f)", relativePos.x, relativePos.y);
        return false;  // ���������Χ������ false
    }

    // ��ȡ�����Ӧ�� tile GID
    int tileGID = layer->getTileGIDAt(tileCoord);

    // �жϸ�λ���Ƿ�Ϊ�ϰ���
    return tileGID != 0; // ��� GID ��Ϊ 0����˵����λ�����ϰ���
}

//===================================12.21==================================================================================
FarmScene* FarmScene::getInstance() {
    if (instance == nullptr) {
        instance = FarmScene::create();
    }
    return instance;
}

Scene* FarmScene::createScene() {
    return getInstance();
}

void FarmScene::addItem(const std::string& itemName) {
    for (int i = 0; i < crops.size(); ++i) {
        if (crops[i].name == "") {
            // �ҵ��ո��ӣ�������Ʒ
            crops[i].name = itemName;
            updateItemTexture(i);
            return;
        }
    }
}

// ������Ʒ��ʾ����
void FarmScene::updateItemTexture(int slotIndex) {
    // ����λ������Χ�Ƿ�Ϸ�
    if (slotIndex < 0 || slotIndex >= crops.size()) {
        CCLOG("Invalid slot index: %d", slotIndex);
        return;
    }

    auto& slot = crops[slotIndex];

    // ����λ�ľ����Ƿ�Ϊ��
    if (!slot.sprite) {
        CCLOG("Slot sprite is null for slot index: %d", slotIndex);
        return;
    }

    // �����λû����Ʒ���ƣ�ֱ�ӷ���
    if (slot.name.empty()) {
        CCLOG("Slot %d is empty.", slotIndex);
        return;
    }

    // ƴ��ͼƬ·��
    std::string texturePath = slot.name + ".png"; // ����ͼƬ�� Resources �ļ���

    // ���Դ��������������
    auto texture = Director::getInstance()->getTextureCache()->addImage(texturePath);
    if (texture) {
        // ���¾��������
        slot.sprite->setTexture(texture);
        slot.sprite->setScale(3.0f); // ������Ҫ��������
        CCLOG("Updated texture for slot %d: %s", slotIndex, texturePath.c_str());
    }
    else {
        CCLOG("Failed to load texture: %s", texturePath.c_str());
    }


}

// �����Ʒ����
void FarmScene::clearItemTexture(int slotIndex) {
    if (slotIndex < 0 || slotIndex >= crops.size()) return;

    auto& slot = crops[slotIndex];
    slot.sprite->setTexture(nullptr);  // �������
    slot.sprite->removeAllChildren();  // ����ӽڵ㣨��������ǩ��
}


template <typename T>
T clamp(T value, T low, T high) {
    if (value < low) return low;
    if (value > high) return high;
    return value;
}


void FarmScene::updateCameraPosition(float dt, Node* player)
{
    auto playerPosition = player->getPosition();
    auto visibleSize = Director::getInstance()->getVisibleSize();

    // ��ͷλ��Ҫ�����ڵ�ͼ�߽���
    float cameraX = clamp(playerPosition.x, visibleSize.width / 2 - SceneWidth, SceneWidth - visibleSize.width / 2);
    float cameraY = clamp(playerPosition.y, visibleSize.height / 2 - SceneHeight, SceneHeight - visibleSize.height / 2);

    // ��ȡĬ������ͷ
    auto camera = Director::getInstance()->getRunningScene()->getDefaultCamera();

    // ��������ͷλ��
    if (camera) {
        camera->setPosition3D(Vec3(cameraX, cameraY, camera->getPosition3D().z));
        //CCLOG("Camera position: (%f, %f)", cameraX, cameraY);
        if (backpackLayer) {
            // ��ȡ��Ļ�Ŀɼ���С
            float backpackX = cameraX - visibleSize.width / 2;
            float backpackY = cameraY - visibleSize.height / 2;

            // ���ñ������λ��
            backpackLayer->setPosition(Vec2(backpackX, backpackY));
        }
    }
}

