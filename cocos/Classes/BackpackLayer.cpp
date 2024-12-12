#include "BackpackLayer.h"
#include "cocos2d.h"

USING_NS_CC;

BackpackLayer::BackpackLayer()
    : selectedItemImage(""), tilemap(nullptr) {}

BackpackLayer::~BackpackLayer() {
    itemSlots.clear();
}

// 创建背包界面
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

// 初始化函数
bool BackpackLayer::init() {
    if (!Layer::init()) {
        return false;
    }

    // 获取瓦片地图背景
    auto visibleSize = Director::getInstance()->getVisibleSize();
    tilemap = TMXTiledMap::create("backpack_map.tmx");  // 假设背包是瓦片地图的一部分
    if (!tilemap) {
        CCLOG("Failed to load backpack_map.tmx");
        return false;
    }

    this->addChild(tilemap, 0);
    auto mapSize = tilemap->getContentSize();

    // 设置瓦片地图位置
    float x = (visibleSize.width - mapSize.width) / 2;  // 居中
    float y = visibleSize.height * 0.05f;              // 距底部偏移一点
    tilemap->setPosition(Vec2(x, y));

    // 获取对象层（每个背包格子的位置）
    auto objectGroup = tilemap->getObjectGroup("Slots");  // 假设名为 "Slots"
    if (!objectGroup) {
        CCLOG("Failed to get object group 'Slots'");
        return false;
    }

    // 背包格子管理（假设最大12格）
    itemSlots.resize(12);
    for (int i = 0; i < 12; ++i) {
        itemSlots[i].name = "";      // 物品名
        itemSlots[i].quantity = 0;   // 物品数量

        // 获取对象层中每个格子的坐标
        auto object = objectGroup->getObject("Slot" + std::to_string(i + 1));  // 获取第 i+1 个格子
        float posX = object["x"].asFloat();
        float posY = object["y"].asFloat();
        float width = object["width"].asFloat();
        float height = object["height"].asFloat();
        log("Player Position: x=%d, y=%d", posX, posY);  // 打印坐标信息


        // 创建透明纹理的精灵
        auto sprite = Sprite::create();  // 默认无纹理
		sprite->setPosition(Vec2(posX, posY));        // 设置位置
		sprite->setAnchorPoint(Vec2(0, 0));     // 设置锚点
		sprite->setContentSize(Size(width, height));  // 设置大小
        tilemap->addChild(sprite, 1);  // 添加到瓦片地图
        itemSlots[i].sprite = sprite;
    }

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Tools.plist");        //传入纹理图集

	// 初始添加五件工具
    addItem("Axe1");
    addItem("Can1");
    addItem("Hoe1");
    addItem("Pick1");
    addItem("Axe1");
    removeItem("Can1");
    addItem("Rod1");
    return true;
}

// 添加物品
void BackpackLayer::addItem(const std::string& itemName) {
    for (int i = 0; i < itemSlots.size(); ++i) {
        if (itemSlots[i].name == itemName) {
            // 如果物品已存在，增加数量并更新显示
            itemSlots[i].quantity++;
            updateItemTexture(i);
            return;
        }
    }
    for (int i = 0; i < itemSlots.size(); ++i) {
        if (itemSlots[i].name == "") {
            // 找到空格子，放入物品
            itemSlots[i].name = itemName;
            itemSlots[i].quantity = 1;
            updateItemTexture(i);
            return;
        }
    }
}

// 减少物品
void BackpackLayer::removeItem(const std::string& itemName) {
    for (int i = 0; i < itemSlots.size(); ++i) {
        if (itemSlots[i].name == itemName && itemSlots[i].quantity > 0) {
            itemSlots[i].quantity--;
            if (itemSlots[i].quantity == 0) {
                // 物品数量为 0，清空该位置的纹理
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

// 更新物品显示纹理
void BackpackLayer::updateItemTexture(int slotIndex) {
    if (slotIndex < 0 || slotIndex >= itemSlots.size()) return;

    auto& slot = itemSlots[slotIndex];
    if (slot.name != "") {
        std::string spriteFrameName = slot.name + "-right.png";  
        auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameName);
        if (spriteFrame) {
            slot.sprite->setSpriteFrame(spriteFrame);  // 使用spriteFrame更新纹理
            slot.sprite->setScale(3.0f);
        }
        else {
            CCLOG("Failed to find sprite frame: %s", spriteFrameName.c_str());
        }

		// 移除之前的数量标签
        slot.sprite->removeChildByTag(1001);

        // 更新数量显示
        auto label = Label::createWithSystemFont(std::to_string(slot.quantity), "Arial", 8);
        label->setAnchorPoint(Vec2(0.0f, 0.6f));
        label->setPosition(slot.sprite->getContentSize().width, 0);
        label->setTextColor(Color4B::BLACK);
        slot.sprite->addChild(label, 1);
		label->setTag(1001);// 设置tag值
    }
}

// 清除物品纹理
void BackpackLayer::clearItemTexture(int slotIndex) {
    if (slotIndex < 0 || slotIndex >= itemSlots.size()) return;

    auto& slot = itemSlots[slotIndex];
    slot.sprite->setTexture(nullptr);  // 清空纹理
    slot.sprite->removeAllChildren();  // 清空子节点（如数量标签）
}
