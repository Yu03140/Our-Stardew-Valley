#include "FarmGround.h"
USING_NS_CC;
FarmScene* FarmScene::instance = nullptr;

//----------------------------------------------------
// FarmScene::init()
// ���ܣ���ʼ������
// ˵������������������ũ�������й���
//----------------------------------------------------
bool FarmScene::init() {

    if (!Scene::init()) {
        return false;
    }
    init_mouselistener();
    //----------------------------------------------------
    // ���ܣ�������Ƭ��ͼ
    // ˵����������Ļ����
    //----------------------------------------------------
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    tileMap = TMXTiledMap::create("Myfarm.tmx");
    if (tileMap) {
        tileMap->setAnchorPoint(Vec2(0.5, 0.5));
        float Map_posX = visibleSize.width / 2;
        float Map_posY = visibleSize.height / 2;
        tileMap->setPosition(Vec2(Map_posX, Map_posY));
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
    // ���ܣ���ӽ����ﾫ��
    // ˵�������ں�������͸����
    //----------------------------------------------------
    // ��ӷ���
    house = Sprite::create("houses.png"); 
    house->setPosition(Vec2(600, 600)); 
    house->setScale(MapSize);
    this->addChild(house);
    // �������
    shed = Sprite::create("Big Shed.png"); 
    shed->setPosition(Vec2(0, 1100));
    shed->setScale(MapSize);
    this->addChild(shed);

    //----------------------------------------------------
    // ���ܣ������ʼ��
    // ˵��������������󣬳�ʼ����������
    //----------------------------------------------------
    Player* player = Player::getInstance("me");

    //----------------------------------------------------
    // ���ܣ���ӱ���ͼ��
    // ˵������ӱ���ͼ�㵽��ǰ��������ʼ������
    //----------------------------------------------------
    backpackLayer = BackpackLayer::getInstance();
    if (backpackLayer) {
        this->addChild(backpackLayer, Backpacklayer);
        backpackLayer->setName("backpackLayer");
    }
    else
        CCLOG("Failed to load the backpack layer");

    //----------------------------------------------------
    // ���ܣ�����ƶ�����
    // ˵����������ǣ�����λ�ڵ�ͼ����
    //----------------------------------------------------
    auto sprite_move = moveable_sprite_key_walk::create("Jas_Winter.plist", "Jas_Winter");
    if (sprite_move)
    {
        sprite_move->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        this->addChild(sprite_move, Playerlayer);
        sprite_move->init_keyboardlistener();
        // ���������ƶ��߼������λ��
        sprite_move->schedule([this, sprite_move](float dt) {
            sprite_move->update(dt);                         
            updateCameraPosition(dt, sprite_move);        
            }, "update_key_person");

        schedule([this, sprite_move](float dt) {
            this->update(dt, sprite_move);  
            }, "update_key_scene");
        CCLOG("diao yong cheng gong la");

    }
    Size originalSize = sprite_move->getContentSize();
    float scale = sprite_move->getScale();
    Size scaledSize = Size(originalSize.width * scale, originalSize.height * scale);

    //----------------------------------------------------
    // ���ܣ���ӹ���
    // ˵��������������ƶ��Ĺ���
    //----------------------------------------------------
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
            sprite->add_in(dict, sprite, "grass", tileMap);
            //����ݸ��ӹ�����
            grass_manager->add_goods(sprite);
        }
    }
    this->addChild(grass_manager);
    grass_manager->schedule([grass_manager](float delta) {
        grass_manager->random_access();
        }, 6.0f, "RandomAccessSchedulerKey");


	//----------------------------------------------------
	// ���ܣ��޸�����
	// ˵�����ڵ�ͼ���޸��ưܵĽ�������
    //----------------------------------------------------
    auto objectGroup_gh = tileMap->getObjectGroup("warmhouse");
    if (!objectGroup_gh) {
        CCLOG("Failed to get object group 'warmhouse'");
        return false;
    }
    auto objects_gh = objectGroup_gh->getObjects();
    for (const auto& object : objects_gh) {
        // ͨ�� object �е������ж��Ƿ�������Ϊ 'warmhouse' �Ķ���
        auto dict = object.asValueMap();
        std::string objectName = dict["name"].asString();
        if (objectName == "warmhouse") {
            auto sprite = getable_goods::create("goods.plist");
            sprite->add_in(dict, sprite, "badGreenhouse", tileMap);
        }
    }

    //----------------------------------------------------
    // ���ܣ�����ģ��
    // ˵����ͨ����ȡ����㣬�ڵ�ͼ�����������ӣ�������ֲ����
    //----------------------------------------------------
    auto objectGroup = tileMap->getObjectGroup("crops_layer"); 
    if (!objectGroup) {
        CCLOG("Failed to get object group 'crops_layer'");
        return false;
    }
    Vec2 map_pos = tileMap->getPosition();
    // ������ӹ�����36��
    crops.resize(36);
    for (int i = 0; i < 36; ++i) {
        // ������ 
        crops[i].name = "";     
        // ��ȡ�� i+1 ������
        auto object = objectGroup->getObject("crop" + std::to_string(i + 1)); 
        // ��ȡ�������ÿ�����ӵ�����
        float posX = object["x"].asFloat(); 
        float posY = object["y"].asFloat();
        float width = object["width"].asFloat();
        float height = object["height"].asFloat();
        // ����͸������ľ���
        auto sprite = crop::create("crop_m.plist", width, height);  
        sprite->setPosition(Vec2(posX, posY));     
        sprite->setAnchorPoint(Vec2(0, 0));   
        sprite->setContentSize(Size(width, height)); 
        tileMap->addChild(sprite, 2); 
        sprite->init_mouselistener();
        crops[i].sprite = sprite;

        sprite->schedule([sprite](float dt) {
            sprite->update_day(dt);
            }, "update_crop");

    }

    //----------------------------------------------------
    // ���ܣ����������̵�ģ��
    // ˵����������...
    //----------------------------------------------------
    taskBarLayer = TaskBarLayer::create();
    this->addChild(taskBarLayer, Backpacklayer);
	shop_board_layer = Shop_Board_Layer::create();
	this->addChild(shop_board_layer);

    board = Board::createBoard("normal", 0, 0);
    board->setScale(6);
    board->setPosition(0, 0);
    this->addChild(board, Backpacklayer);
    

	//----------------------------------------------------
	// ���ܣ�ʱ��ϵͳ
	// ˵�������ʱ��ϵͳ����ǰ����
	//----------------------------------------------------
    timeSystem = TimeSystem::getInstance();
    Node* parentNode = this;
    parentNode->addChild(timeSystem);
    // ÿ֡����ʱ���ʱ��
    schedule([this](float deltaTime) {
        timeSystem->checkForHoliday();
        }, "time_check_key");

    //----------------------------------------------------
    // ���ܣ���ʼ��NPC
    // ˵������ʼ��NPC����ӵ�������
    //----------------------------------------------------
    // NPC1�ĳ�ʼ��
    npc1 = NPC::create(cocos2d::Vec2(1050, 1050), "Bouncer", 50, {
        "Hello, traveler!",
        "My name is Bouncer.",
        "Could you please give me a favor?",
        "Check the taskbar please"
        });
    npc1->setScale(4);
    this->addChild(npc1);
    // NPC2�ĳ�ʼ��
    npc2 = NPC::create(cocos2d::Vec2(500, 500), "May", 80, {
    "Hello, traveler!",
    "How can I help you today?",
    "I hope you're having a good day!",
    "Bye~"
        });
    npc2->setScale(4); 
    this->addChild(npc2);
    //���ö�ʱ���º���
    this->schedule([this](float deltaTime) {
    //ÿ֡���ø��º���
        this->update(deltaTime);
        }, "update_key");

    //----------------------------------------------------
    // ���ܣ�����ģ��
    // ˵����ͨ����ȡ����㣬�жϿɵ����λ��
    //----------------------------------------------------
    //��ȡ�����
    auto barrierobjectGroup = tileMap->getObjectGroup("barriers");
    if (!barrierobjectGroup) {
        CCLOG("Failed to get object group 'barriers'");
        return false;
    }
    //��ȡ�������ˮ�ص�����
    fish.resize(1);
    fish[0].name = ""; 
    auto object = barrierobjectGroup->getObject("barrier9");
    float posX = object["x"].asFloat();
    float posY = object["y"].asFloat();
    float width = object["width"].asFloat();
    float height = object["height"].asFloat();
    //����͸������ľ���
    auto sprite1 = fish::create("crop_m.plist", width, height); 
    //����λ��
    sprite1->setPosition(Vec2(posX, posY));       
    sprite1->setAnchorPoint(Vec2(0, 0)); 
    sprite1->setContentSize(Size(width, height));
    tileMap->addChild(sprite1, 2); 
    sprite1->init_mouselistener();
    fish[0].sprite = sprite1;

    return true;
}

//----------------------------------------------------
// FarmScene::update()
// ���ܣ���������ƶ������޸�͸����
// ˵�������������Ƿ��ڷ��������ڣ��������ӵ�͸����
//----------------------------------------------------
void FarmScene::update(float dt, moveable_sprite_key_walk* sprite_move) {

    // ��ȡ��������λ��
    Vec2 housePos = house->getPosition();  
    // ���ӵĳߴ�
    Size houseSize = house->getContentSize() * MapSize;  
    // ��ȡ���������λ��
    Vec2 playerPos = sprite_move->getPosition();
    // �ж������Ƿ��ڷ��ݵľ���������
    bool isPlayerInsideHouse = playerPos.x > housePos.x - houseSize.width / 2 &&
        playerPos.x < housePos.x + houseSize.width / 2 &&
        playerPos.y > housePos.y - houseSize.height / 2 &&
        playerPos.y < housePos.y + houseSize.height / 2;
    // ��ȡ��������λ��
    Vec2 shedPos = shed->getPosition(); 
    // ���ӵĳߴ�
    Size shedSize = shed->getContentSize() * MapSize;  
    // �ж������Ƿ������ݵľ���������
    bool isPlayerInsideshed = playerPos.x > shedPos.x - shedSize.width / 2 &&
        playerPos.x < shedPos.x + shedSize.width / 2 &&
        playerPos.y > shedPos.y - shedSize.height / 2 &&
        playerPos.y < shedPos.y + shedSize.height / 2;
    //͸�����޸�
    house->setOpacity(isPlayerInsideHouse ? 128 : 255);
    shed->setOpacity(isPlayerInsideshed ? 128 : 255);
}

//----------------------------------------------------
// FarmScene::getInstance()
// ���ܣ���ȡȫ��Ψһ����
//----------------------------------------------------
FarmScene* FarmScene::getInstance() {
    if (instance == nullptr) {
        instance = FarmScene::create();
    }
    return instance;
}

//----------------------------------------------------
// FarmScene::createScene()
// ���ܣ�����������һ�� FarmScene ������ʵ��
//----------------------------------------------------
Scene* FarmScene::createScene() {
    return getInstance();
}

//----------------------------------------------------
// FarmScene::addItem()
// ���ܣ��ڱ����������Ʒ
//----------------------------------------------------
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

//----------------------------------------------------
// FarmScene::updateItemTexture()
// ���ܣ�������Ʒ��ʾ����
//----------------------------------------------------
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
    std::string texturePath = slot.name + ".png"; 
    // ���������������
    auto texture = Director::getInstance()->getTextureCache()->addImage(texturePath);
    if (texture) {
        // ���¾��������
        slot.sprite->setTexture(texture);
        slot.sprite->setScale(3.0f);
        CCLOG("Updated texture for slot %d: %s", slotIndex, texturePath.c_str());
    }
    else {
        CCLOG("Failed to load texture: %s", texturePath.c_str());
    }
}

//----------------------------------------------------
// FarmScene::updateItemTexture()
// ���ܣ������Ʒ��ʾ����
//----------------------------------------------------
void FarmScene::clearItemTexture(int slotIndex) {
    if (slotIndex < 0 || slotIndex >= crops.size())
        return;
    auto& slot = crops[slotIndex];
    // �������
    slot.sprite->setTexture(nullptr);  
    // ����ӽڵ�
    slot.sprite->removeAllChildren();  
}

//����ֵ�ķ�Χ��ʹ�䱣����ָ������Сֵ�����ֵ֮��
template <typename T>
T clamp(T value, T low, T high) {
    if (value < low) return low;
    if (value > high) return high;
    return value;
}

//----------------------------------------------------
// FarmScene::updateCameraPosition()
// ���ܣ��������������λ��
//----------------------------------------------------
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
		float Posx = cameraX - visibleSize.width / 2;
		float Posy = cameraY - visibleSize.height / 2;
        if (backpackLayer)
            backpackLayer->setPosition(Vec2(Posx, Posy));
        if (board)
            board->setPosition(Vec2(Posx, Posy));
		if (taskBarLayer)
			taskBarLayer->setPosition(Vec2(Posx, Posy));
    }
}

//----------------------------------------------------
// FarmScene::init_mouselistener()
// ���ܣ���ʼ����������
//----------------------------------------------------
void FarmScene::init_mouselistener()
{
    // ������������
    auto listener = cocos2d::EventListenerMouse::create();

    // ���ص�
    listener->onMouseDown = CC_CALLBACK_1(FarmScene::on_mouse_click, this);

    // ��ȡ�¼��ַ�������Ӽ�����
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

//----------------------------------------------------
// FarmScene::on_mouse_click()
// ���ܣ���갴��ʱ�Ļص�
//----------------------------------------------------
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
    checkForButtonClick(mouse_pos);
    // 0.1��� MOUSE_POS ��Ϊ (0, 0)�����Ҳ�Ӱ��������������
    this->scheduleOnce([this](float dt) {
        MOUSE_POS = Vec2::ZERO;
        CCLOG("Mouse Position reset to: (%f, %f)", MOUSE_POS.x, MOUSE_POS.y);
        }, 1.5f, "reset_mouse_pos_key");
}

//----------------------------------------------------
// FarmScene::checkForButtonClick()
// ���ܣ�����Ƿ�����Button���л�����
//----------------------------------------------------
void FarmScene::checkForButtonClick(Vec2 mousePosition)
{
    // ��ȡ Button �����
    auto objectGroup = tileMap->getObjectGroup("Button");
    if (!objectGroup) {
        CCLOG("Failed to get object group 'Button'");
        return ;
    }
    // ��ȡ Door ���������ͳߴ�
    std::string Objectname[3] = { "Mines_Door","Home_Door","Shed_Door" };
    Scene* nextScene = nullptr;
    for(int i=0;i<3;i++){
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
        if (backpackLayer) {
            // �ӵ�ǰ�������Ƴ������㣬�������������ڴ�
            backpackLayer->removeFromParent();
            CCLOG("remove backpackLayer successfully!");
        }
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
            // �������������ⱻ����
            nextScene->retain();  
            Director::getInstance()->pushScene(nextScene);
        }
        return ;
        }
    }
}

//----------------------------------------------------
// FarmScene::update()
// ���ܣ����������NPC������״̬
//----------------------------------------------------
void FarmScene::update(float delta) {
	// ��������NPC�Ľ���
    checkNPCInteraction();
     // ��������NPC�ľ��룬�����°�ť����ʾ״̬
    if (character_pos.distance(npc1->getPosition()) < 50) {
        // �ڷ�Χ��ʱ��ʾ��ť
        npc1->showChatButton(true); 
    }
    else {
        // ���ڷ�Χ��ʱ���ذ�ť
        npc1->showChatButton(false); 
    }
    if (character_pos.distance(npc2->getPosition()) < 50) {
        // �ڷ�Χ��ʱ��ʾ��ť
        npc2->showChatButton(true);  
    }
    else {
        // ���ڷ�Χ��ʱ���ذ�ť
        npc2->showChatButton(false); 
    }
}

//----------------------------------------------------
// FarmScene::checkNPCInteraction()
// ���ܣ������Һ�NPC֮��ľ����Ƿ�С��100��λ
// ˵����100�Ǵ��������ķ�Χ��ֵ���������NPC�ľ���С��100ʱ�����п�����NPC����
//----------------------------------------------------
void FarmScene::checkNPCInteraction() {
    if (character_pos.distance(npc1->getPosition()) < 50) {
        // ���NPC��ǰ��������״̬����NPCû����������ҶԻ���������ʾ������ʾ��
        if (!npc1->isChattingStatus()) {
            // �����־����ʾ��Ұ��¡�Chat������NPC������
            CCLOG("Press 'Chat' to interact with NPC.");
        }
        if (!npc2->isChattingStatus()) {
            // �����־����ʾ��Ұ��¡�Chat������NPC������
            CCLOG("Press 'Chat' to interact with NPC.");
        }
    }
}

//----------------------------------------------------
// FarmScene::onEnter()
// ���ܣ�����������ʱ���õĳ�ʼ������
//       ��Ҫ����ȷ����������ڲ���ӵ���ǰ������
//----------------------------------------------------
void FarmScene::onEnter() {
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

