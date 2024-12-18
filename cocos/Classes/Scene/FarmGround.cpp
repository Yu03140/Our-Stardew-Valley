#include "FarmGround.h"

USING_NS_CC;
#define MAG_TIMES 4.0f
FarmScene* FarmScene::createScene() {
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
        tileMap->setScale(MAG_TIMES);
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

	// ���ʱ��ϵͳ
    timeSystem = TimeSystem::getInstance();  
    Node* parentNode = this;  
    parentNode->addChild(timeSystem);

    // �������
    auto sprite_move = moveable_sprite_key_walk::create("Jas_Winter.plist", "Jas_Winter");
    if(sprite_move)
    {
        sprite_move->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        character_pos = Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
        this->addChild(sprite_move, 1);
        sprite_move->init_keyboardlistener();
        sprite_move->schedule([sprite_move](float dt) {
            sprite_move->update(dt);
            }, "update_key_person");
    }
    auto animal = animals::create("Animals.plist", "Pig", Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y),Size(100,100));
    if (animal)
    {
        animal->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        this->addChild(animal, 1);
        animal->init_mouselistener();
        animal->scheduleRandomMove(tileMap);
        animal->schedule([animal](float dt) {
            animal->update(dt);
            }, "update_animal");
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
        auto sprite = crop::create("crop_m.plist", width, height); // Ĭ��������

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

