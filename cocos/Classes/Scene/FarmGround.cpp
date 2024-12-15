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

    // ��������ͼ�㣬��������ӵ�������
    backpackLayer = BackpackLayer::create();
    if (backpackLayer) {
        this->addChild(backpackLayer, 2);  
    }
    else
		CCLOG("Failed to load the backpack layer");

	// ����ʱ��ϵͳʵ��
    timeSystem = TimeSystem::getInstance();  
    Node* parentNode = this;  
    parentNode->addChild(timeSystem);

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

