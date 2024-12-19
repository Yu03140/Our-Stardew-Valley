#include "FarmGround.h"

USING_NS_CC;

FarmScene* FarmScene::createScene(){

    // ���������� FarmScene ��������
    return FarmScene::create();
}

bool FarmScene::init() {
    // ���ø���ĳ�ʼ������

    if (!Scene::init()) {
        return false;
    }

    //�����ʼ��
    Player* player = Player::getInstance("me");

    // ���ص�ͼ�������м�
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();//Ϊ��������ӵ�
    tileMap = TMXTiledMap::create("Myfarm.tmx");
    if (tileMap) {
        tileMap->setAnchorPoint(Vec2(0.5, 0.5));
        float posX = visibleSize.width / 2;
        float posY = visibleSize.height / 2;
        tileMap->setPosition(Vec2(posX, posY));
        this->addChild(tileMap, 0);
        tileMap->setScale(2);

    }
    else {
        CCLOG("Failed to load the tile map");
    }

    // ������ͼ����ӵ�������
    backpackLayer = BackpackLayer::create();
    if (backpackLayer) {
        this->addChild(backpackLayer, 2);
    }
    else
        CCLOG("Failed to load the backpack layer");

    //Board���棬��ʾʱ����������Ǯ��
    //--------------renew��dxn��-------------------------------------------------------------------------
      // 1. ���� Board ���󣬳�ʼ����Ϊ "normal"����ʼ��ǮΪ 0
    auto board = Board::createBoard("normal", 0,0);
    board->setScale(6);
    //board->setPosition(1050, 1050);
    //board->setPosition(Vec2(visibleSize.width / 4, visibleSize.height - 150));
    this->addChild(board);

    // ���ʱ��ϵͳ
    timeSystem = TimeSystem::getInstance();
    Node* parentNode = this;
    parentNode->addChild(timeSystem);
    // ÿ֡����ʱ���ʱ��
    schedule([this](float deltaTime) {
        timeSystem->checkForHoliday();
        }, "time_check_key");


    //��ʼ��NPC
    //�����޸�һ�����õ�λ��
    npc1 = NPC::create(cocos2d::Vec2(1050, 1050), "Bouncer", 50, {
        "Hello, traveler!",
        "My name is Bouncer.",
        "Could you please give me a favor?",
        "Check the taskbar please"
        });
    // 6. �� NPC ������ӵ���ǰ������
    npc1->setScale(4); // �Ŵ��ı�
    this->addChild(npc1);

    npc2 = NPC::create(cocos2d::Vec2(500, 500), "May", 80, {
    "Hello, traveler!",
    "How can I help you today?",
    "I hope you're having a good day!",
    "Bye~"
        });
    npc2->setScale(4); // �Ŵ��ı�
    // 6. �� NPC ������ӵ���ǰ������
    this->addChild(npc2);

    // 7. ���ö�ʱ���º���
    this->schedule([this](float deltaTime) {
        // 8. ÿ֡���ø��º���
        this->update(deltaTime);
        }, "update_key");
    
//-----------end-----------------------------------------------------------------------------

    // �������
    auto sprite_move = moveable_sprite_key_walk::create("Jas_Winter.plist", "Jas_Winter");
    if(sprite_move)
    {

        sprite_move->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        this->addChild(sprite_move, 1);

        sprite_move->init_keyboardlistener();

        sprite_move->schedule([sprite_move](float dt) {
            sprite_move->update(dt);
            }, "update_key_person");
    }

	// ���������
    taskBarScene = TaskBarLayer::create(); 
    tileMap->addChild(taskBarScene,3);     


    // ����ģ��
    // ��ȡ����㣨ÿ��������ӵ�λ�ã�
    auto objectGroup = tileMap->getObjectGroup("crops_layer");
    if (!objectGroup) {
        CCLOG("Failed to get object group 'crops_layer'");
        return false;
    }

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
        log("Player Position: x=%d, y=%d", posX, posY);  // ��ӡ������Ϣ


        // ����͸������ľ���
        auto sprite = Sprite::create("load1.png");  // Ĭ��������
        sprite->setPosition(Vec2(posX, posY));        // ����λ��
        sprite->setAnchorPoint(Vec2(0, 0));     // ����ê��
        sprite->setContentSize(Size(width, height));  // ���ô�С
        tileMap->addChild(sprite, 1);  // ��ӵ���Ƭ��ͼ
        crops[i].sprite = sprite;
    }

    return true;
}

void FarmScene::addItem(const std::string& itemName) {
    for (int i = 0; i < crops.size(); ++i) {
        if (crops[i].name == itemName) {
            // �����Ʒ�Ѵ��ڣ�������ʾ
            updateItemTexture(i);
            return;
        }
    }
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

//-----------renew(dxn)-------------------------------------------------------------------
void FarmScene::update(float delta) {
    // ��������NPC�Ľ���
    checkNPCInteraction();
   // Player* player = Player::getInstance("me");
    // ��������NPC�ľ��룬�����°�ť����ʾ״̬
    if (character_pos.distance(npc1->getPosition()) < 50) {
        npc1->showChatButton(true);  // �ڷ�Χ��ʱ��ʾ��ť
    }
    else {
        npc1->showChatButton(false);  // ���ڷ�Χ��ʱ���ذ�ť
    }
    if (character_pos.distance(npc2->getPosition()) < 50) {
        npc2->showChatButton(true);  // �ڷ�Χ��ʱ��ʾ��ť
    }
    else {
        npc2->showChatButton(false);  // ���ڷ�Χ��ʱ���ذ�ť
    }
}


void FarmScene::checkNPCInteraction() {
    // �����Һ�NPC֮��ľ����Ƿ�С��100��λ��
    // 100�Ǵ��������ķ�Χ��ֵ���������NPC�ľ���С��100ʱ�����п�����NPC������
    //Player* player = Player::getInstance("me");
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
//---------end--------------------------------------------------------------------
