#include "BackpackLayer.h"
#include "cocos2d.h"

USING_NS_CC;

BackpackLayer::BackpackLayer()
    : selectedItemImage(""), tilemap(nullptr) {}

BackpackLayer::~BackpackLayer() {
    itemSlots.clear();
}

// ������������
BackpackLayer* BackpackLayer::create() {
    BackpackLayer* ret = new BackpackLayer();
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    else {
        delete ret;
        return nullptr;
    }
}

// ��ʼ������
bool BackpackLayer::init() {
    if (!Layer::init()) {
        return false;
    }

    // ��ȡ��Ƭ��ͼ����
    auto visibleSize = Director::getInstance()->getVisibleSize();
    tilemap = TMXTiledMap::create("backpack_map.tmx");  // ���豳������Ƭ��ͼ��һ����
    if (!tilemap) {
        CCLOG("Failed to load backpack_map.tmx");
        return false;
    }

    this->addChild(tilemap, 0);
    auto mapSize = tilemap->getContentSize();

    // ������Ƭ��ͼλ��
    float x = (visibleSize.width - mapSize.width) / 2;  // ����
    float y = visibleSize.height * 0.05f;              // ��ײ�ƫ��һ��
    tilemap->setPosition(Vec2(x, y));

    // ��ȡ����㣨ÿ���������ӵ�λ�ã�
    auto objectGroup = tilemap->getObjectGroup("Slots");  // ������Ϊ "Slots"
    if (!objectGroup) {
        CCLOG("Failed to get object group 'Slots'");
        return false;
    }

    // �������ӹ����������12��
    itemSlots.resize(12);
    for (int i = 0; i < 12; ++i) {
        itemSlots[i].name = "";      // ��Ʒ��
        itemSlots[i].quantity = 0;   // ��Ʒ����

        // ��ȡ�������ÿ�����ӵ�����
        auto object = objectGroup->getObject("Slot" + std::to_string(i + 1));  // ��ȡ�� i+1 ������
        float posX = object["x"].asFloat();
        float posY = object["y"].asFloat();
        float width = object["width"].asFloat();
        float height = object["height"].asFloat();
        log("Player Position: x=%d, y=%d", posX, posY);  // ��ӡ������Ϣ


        // ����͸������ľ���
        auto sprite = Sprite::create();  // Ĭ��������
		sprite->setPosition(Vec2(posX, posY));        // ����λ��
		sprite->setAnchorPoint(Vec2(0, 0));     // ����ê��
		sprite->setContentSize(Size(width, height));  // ���ô�С
        tilemap->addChild(sprite, 1);  // ��ӵ���Ƭ��ͼ
        itemSlots[i].sprite = sprite;
    }

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Tools.plist");        //��������ͼ��

	// ��ʼ����������
    addItem("Axe1");
    addItem("Can1");
    addItem("Hoe1");
    addItem("Pick1");
    addItem("Axe1");
    removeItem("Can1");
    addItem("Rod1");
    return true;
}

// �����Ʒ
void BackpackLayer::addItem(const std::string& itemName) {
    for (int i = 0; i < itemSlots.size(); ++i) {
        if (itemSlots[i].name == itemName) {
            // �����Ʒ�Ѵ��ڣ�����������������ʾ
            itemSlots[i].quantity++;
            updateItemTexture(i);
            return;
        }
    }
    for (int i = 0; i < itemSlots.size(); ++i) {
        if (itemSlots[i].name == "") {
            // �ҵ��ո��ӣ�������Ʒ
            itemSlots[i].name = itemName;
            itemSlots[i].quantity = 1;
            updateItemTexture(i);
            return;
        }
    }
}

// ������Ʒ
void BackpackLayer::removeItem(const std::string& itemName) {
    for (int i = 0; i < itemSlots.size(); ++i) {
        if (itemSlots[i].name == itemName && itemSlots[i].quantity > 0) {
            itemSlots[i].quantity--;
            if (itemSlots[i].quantity == 0) {
                // ��Ʒ����Ϊ 0����ո�λ�õ�����
                itemSlots[i].name = "";
                clearItemTexture(i);
            }
            else {
                updateItemTexture(i);
            }
            return;
        }
    }
}

// ������Ʒ��ʾ����
void BackpackLayer::updateItemTexture(int slotIndex) {
    if (slotIndex < 0 || slotIndex >= itemSlots.size()) return;

    auto& slot = itemSlots[slotIndex];
    if (slot.name != "") {
        std::string spriteFrameName = slot.name + "-right.png";  
        auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameName);
        if (spriteFrame) {
            slot.sprite->setSpriteFrame(spriteFrame);  // ʹ��spriteFrame��������
            slot.sprite->setScale(3.0f);
        }
        else {
            CCLOG("Failed to find sprite frame: %s", spriteFrameName.c_str());
        }

		// �Ƴ�֮ǰ��������ǩ
        slot.sprite->removeChildByTag(1001);

        // ����������ʾ
        auto label = Label::createWithSystemFont(std::to_string(slot.quantity), "Arial", 8);
        label->setAnchorPoint(Vec2(0.0f, 0.6f));
        label->setPosition(slot.sprite->getContentSize().width, 0);
        label->setTextColor(Color4B::BLACK);
        slot.sprite->addChild(label, 1);
		label->setTag(1001);// ����tagֵ
    }
}

// �����Ʒ����
void BackpackLayer::clearItemTexture(int slotIndex) {
    if (slotIndex < 0 || slotIndex >= itemSlots.size()) return;

    auto& slot = itemSlots[slotIndex];
    slot.sprite->setTexture(nullptr);  // �������
    slot.sprite->removeAllChildren();  // ����ӽڵ㣨��������ǩ��
}
