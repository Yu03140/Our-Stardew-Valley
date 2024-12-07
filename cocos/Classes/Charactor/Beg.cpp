#include "Beg.h"
#include "BegManager.h"

USING_NS_CC;

BackpackLayer::BackpackLayer()
    : backpackBackground(nullptr) {
}

BackpackLayer::~BackpackLayer() {
    items.clear();
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

    // ������������
    auto visibleSize = Director::getInstance()->getVisibleSize();
    backpackBackground = Sprite::create("backpack_bg.png");
    if (!backpackBackground) {
        CCLOG("Failed to load backpack background image.");
        return false;
    }
    backpackBackground->setPosition(Vec2(visibleSize.width / 2, backpackBackground->getContentSize().height / 2));
    this->addChild(backpackBackground, 1);

    // ��ȡ������������������Ʒ
    const auto& itemsList = BackpackManager::getInstance()->getItems();
    for (const auto& item : itemsList) {
        addItem(item.first, item.second);
    }

    return true;
}

void BackpackLayer::addItem(const std::string& itemName, const std::string& itemImage) {
    auto item = Sprite::create(itemImage);
    if (item) {
        item->setPosition(Vec2(100 + items.size() * 50, backpackBackground->getPositionY()));
        this->addChild(item);
        items.push_back(item);
    }
}

void BackpackLayer::toggleVisibility() {
    backpackBackground->setVisible(!backpackBackground->isVisible());
    for (auto& item : items) {
        item->setVisible(backpackBackground->isVisible());
    }
}
