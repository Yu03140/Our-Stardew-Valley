#include "FarmGround.h"

USING_NS_CC;
FarmScene* FarmScene::createScene() {
    // ���������� FarmScene ��������
    return FarmScene::create();
}

bool FarmScene::init() {
    // ���ø���ĳ�ʼ������

    if (!Scene::init()) {
        return false;
    }
    init_mouselistener();
    // ���ص�ͼ�������м�
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
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

    }    
    main_char = sprite_move;

    tileMap = TMXTiledMap::create("Myfarm.tmx");
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
    backpackLayer = BackpackLayer::getInstance();
    if (backpackLayer) {
        this->addChild(backpackLayer, Backpacklayer);
        backpackLayer->setName("backpackLayer");
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

    // ���㾭�����ź��ʵ�ʳߴ�
    Size originalSize = sprite_move->getContentSize();
    float scale = sprite_move->getScale();
    Size scaledSize = Size(originalSize.width * scale, originalSize.height * scale);
    auto sprite_tool = moveable_sprite_key_tool::create("Tools.plist");
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

    //----------------------------------------------------
    // ���ܣ����������
    // ˵�����������������ǰ����
    // ͼ�㣺Taskbarlayer
    //----------------------------------------------------
    taskBarScene = TaskBarLayer::create(); 
    this->addChild(taskBarScene,3);     

    Vec2 map_pos = tileMap->getPosition();  // ��ȡ��Ƭ��ͼ��ƫ��λ��
    Size tileSize = tileMap->getTileSize(); // ��ȡ��Ƭ�ߴ�
    float mapscale = tileMap->getScale();      // ��ȡ��Ƭ��ͼ���������ӣ�����еĻ���
    /*--------------------------------------------renew2----------------------------------------*/
    
    //----------------------------------------------------
    // ���ܣ���ģ��
    // ˵�����ڵ�ͼ����������ӣ�����������
    // ͼ�㣺Playerlayer
    //----------------------------------------------------
    // ��ȡ����㣨ÿ��������ӵ�λ�ã�
    auto objectGroup_tree = tileMap->getObjectGroup("forest");
    if (!objectGroup_tree) {
        CCLOG("Failed to get object group 'tree'");
        return false;
    }

    // �����ӹ���
    GoodsManager* tree_manager = GoodsManager::create();
    auto objects_tree = objectGroup_tree->getObjects();

    for (const auto& object : objects_tree) {
        // ͨ�� object �е������ж��Ƿ�������Ϊ 'tree' �Ķ���
        auto dict = object.asValueMap();
        std::string objectName = dict["name"].asString();
        //������������Ϊ���Ķ���
        if (objectName == "trees") {
            auto sprite = getable_goods::create("goods.plist");
            sprite->add_in(dict, sprite, "tree", tileMap);
            //���������ӹ�����
            tree_manager->add_goods(sprite);
        }
    }
    this->addChild(tree_manager);
    tree_manager->schedule([tree_manager](float delta) {
        tree_manager->random_access();
        }, 6.0f, "RandomAccessSchedulerKey");
   
    //----------------------------------------------------
    // ���ܣ���ģ��
    // ˵�����ڵ�ͼ����Ӳݸ��ӣ��������ɲ�
    // ͼ�㣺Playerlayer
    //----------------------------------------------------
    // ��ȡ����㣨ÿ��������ӵ�λ�ã�
    auto objectGroup_grass = tileMap->getObjectGroup("grass");
    if (!objectGroup_grass) {
        CCLOG("Failed to get object group 'grass'");
        return false;
    }

    // �ݸ��ӹ���
    GoodsManager* grass_manager = GoodsManager::create();
    auto objects_grass = objectGroup_grass->getObjects();

    for (const auto& object : objects_grass) {
        // ͨ�� object �е������ж��Ƿ�������Ϊ 'grass' �Ķ���
        auto dict = object.asValueMap();
        std::string objectName = dict["name"].asString();
        //������������Ϊ�ݵĶ���
        if (objectName == "grass") {
            auto sprite = getable_goods::create("goods.plist");
            sprite->add_in(dict, sprite,"grass",tileMap);
            //����ݸ��ӹ�����
            grass_manager->add_goods(sprite);
        }
    }
    this->addChild(grass_manager);
    grass_manager->schedule([grass_manager](float delta) {
         grass_manager->random_access();
        }, 6.0f, "RandomAccessSchedulerKey");

    /*--------------------------------------------renew2----------------------------------------*/
    
    //----------------------------------------------------
    // ���ܣ�����ģ��
    // ˵�����ڵ�ͼ�����������ӣ�������ֲ����
    // ͼ�㣺Playerlayer
    //----------------------------------------------------
    // ��ȡ����㣨ÿ��������ӵ�λ�ã�
    auto objectGroup_crop = tileMap->getObjectGroup("crops_layer");
    if (!objectGroup_crop) {
        CCLOG("Failed to get object group 'crops_layer'");
        return false;
    }


    // ������ӹ����������36��
    crops.resize(36);
    for (int i = 0; i < 36; ++i) {

        crops[i].name = "";      // ������

        // ��ȡ�������ÿ�����ӵ�����
        auto object = objectGroup_crop->getObject("crop" + std::to_string(i + 1));  // ��ȡ�� i+1 ������
        float posX = object["x"].asFloat();
        float posY = object["y"].asFloat();
        float width = object["width"].asFloat();
        float height = object["height"].asFloat();

        // ����͸������ľ���
        auto sprite = crop::create("crop.plist", width, height); // Ĭ��������

        sprite->setPosition(Vec2(posX, posY));        // ����λ��
        sprite->setAnchorPoint(Vec2(0, 0));     // ����ê��
        sprite->setContentSize(Size(width, height));  // ���ô�С
        tileMap->addChild(sprite, 2);  // ��ӵ���Ƭ��ͼ
        sprite->init_mouselistener();
        crops[i].sprite = sprite;

        sprite->schedule([sprite](float dt) {
            sprite->update_day(dt);
            }, "update_crop");

    }
    return true;
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
    float cameraX = clamp(playerPosition.x, visibleSize.width - SceneWidth / 2, SceneWidth / 2);
    float cameraY = clamp(playerPosition.y, visibleSize.height - SceneHeight / 2, SceneHeight / 2);

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

/*------------------------------------------------------renew-------------------------------------------------------------*/

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

    checkForButtonClick(MOUSE_POS);
    CCLOG("Mouse Position(global): (%f, %f)", MOUSE_POS.x, MOUSE_POS.y);
    // 1.5��� MOUSE_POS ��Ϊ (0, 0)�����Ҳ�Ӱ��������������
    this->scheduleOnce([this](float dt) {
        MOUSE_POS = Vec2::ZERO;
        CCLOG("Mouse Position reset to: (%f, %f)", MOUSE_POS.x, MOUSE_POS.y);
        }, 1.5f, "reset_mouse_pos_key");
}

// ���ܣ�����Ƿ�����Button���л�����
void FarmScene::checkForButtonClick(Vec2 mousePosition)
{
    // ��ȡ Button ����㣨Button �������Ϊ "Button"��
    auto objectGroup = tileMap->getObjectGroup("Button");
    if (!objectGroup) {
        CCLOG("Failed to get object group 'Button'");
        return;
    }

    CCLOG("Successed to get object grouo 'Button'");

    // ��ȡ Door ���������ͳߴ�

    std::string Objectname[3] = { "Mines_Door","Home_Door","Shed_Door" };
    Scene* nextScene = nullptr;

    for (int i = 0; i < 3; i++) {
        auto object = objectGroup->getObject(Objectname[i]);
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

            if (backpackLayer) 
                this->removeChild(backpackLayer);  // �Ƴ�������
            CCLOG("remove backpacklayer successfully!");
            CCLOG("Door clicked! Switching to MinesScene...");

            switch (i) {
            case 0:
                // �л��� MinesScene
                nextScene = MinesScene::createScene();
                break;
            case 1:
                // �л��� HomeScene
                nextScene = HomeScene::createScene();
                break;
            case 2:
                // �л��� ShedScene
                nextScene = ShedScene::createScene();
                break;
            }

            // ������ǳɹ���ȡ����һ��������������ջ��
            if (nextScene) {
                nextScene->retain();  // �������������ⱻ����
                Director::getInstance()->pushScene(nextScene);
            }
            return;
        }
    }
}

// ���볡��ʱ���¼��뱳����
void FarmScene::onEnter()
{
    Scene::onEnter();
    is_infarm = 1;
    CCLOG("IN FARM");
    // ��������㲻�����ڵ�ǰ�������������
    if (backpackLayer && !this->getChildByName("backpackLayer")) {
        this->addChild(backpackLayer, Backpacklayer);
        backpackLayer->setName("backpackLayer");
        CCLOG("readd backpacklayer");
    }
}
void FarmScene::onExit()
{
    Scene::onExit();
    is_infarm = 0;
    CCLOG("LEAVE FARM");

}


/*------------------------------------------------------renew-------------------------------------------------------------*/
