#include "FarmGround.h"
USING_NS_CC;

bool FarmScene::init() {
    if (!Scene::init()) {
        return false;
    }

    // ���ص�ͼ�������м�
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    tileMap = TMXTiledMap::create("Myfarm.tmx");
    if (tileMap) {
        tileMap->setAnchorPoint(Vec2(0.5, 0.5));
        float posX = visibleSize.width / 2;
        float posY = visibleSize.height / 2;
        tileMap->setPosition(Vec2(posX, posY));
        this->addChild(tileMap, 0);
        tileMap->setScale(MapSize);
		SceneWidth = tileMap->getContentSize().width* MapSize;
		SceneHeight = tileMap->getContentSize().height* MapSize;

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
    backpackLayer = BackpackLayer::create();
    if (backpackLayer) {
        this->addChild(backpackLayer, Backpacklayer);
        backpackLayer->setPosition(Vec2(20, visibleSize.height - backpackLayer->getContentSize().height - 20));
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
    if(sprite_move)
    {
        sprite_move->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        this->addChild(sprite_move, Playerlayer);

        sprite_move->init_keyboardlistener();

        sprite_move->schedule([this, sprite_move](float dt) { // ���� `this` �� `sprite_move`
            sprite_move->update(dt);                         // ���������ƶ��߼�
            updateCameraPosition(dt, sprite_move);                 // �������λ��
            }, "update_key_person");

    }

    //----------------------------------------------------
	// ���ܣ����������
    // ˵�����������������ǰ����
    // ͼ�㣺Taskbarlayer
    //----------------------------------------------------
    TaskBarLayer* taskBarLayer = TaskBarLayer::create();
    tileMap->addChild(taskBarLayer,Taskbarlayer);


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

    // ������ӹ����������36��
    crops.resize(36);
    for (int i = 0; i < 36; ++i) {

		crops[i].isPlanted = false; // �Ƿ���ֲ������
        crops[i].name = "";      // ������

        // ��ȡ�������ÿ�����ӵ�����
        auto object = objectGroup->getObject("crop" + std::to_string(i + 1));  // ��ȡ�� i+1 ������
        float posX = object["x"].asFloat();
        float posY = object["y"].asFloat();
        float width = object["width"].asFloat();
        float height = object["height"].asFloat();

        // ����͸�������ũ���ﾫ��
        auto sprite = Sprite::create();  
        sprite->setPosition(Vec2(posX, posY));       
        sprite->setAnchorPoint(Vec2(0, 0));     
        sprite->setContentSize(Size(width, height));  
        tileMap->addChild(sprite, Playerlayer);
        crops[i].sprite = sprite;
    }

    return true;
}

FarmScene* FarmScene::createScene() {
    // ���������� FarmScene ��������
    return FarmScene::create();
}

void FarmScene::addItem(const std::string& itemName) {
    for (int i = 0; i < crops.size(); ++i) {
        if (crops[i].isPlanted==false) {
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
            float backpackX = cameraX - visibleSize.width / 2 ;
            float backpackY = cameraY - visibleSize.height / 2;

            // ���ñ������λ��
            backpackLayer->setPosition(Vec2(backpackX, backpackY));
        }
    }
}

