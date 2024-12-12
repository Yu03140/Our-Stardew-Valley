
#include "FarmGround.h"
using namespace cocos2d;
USING_NS_CC;

FarmScene* FarmScene::createScene() {
    // 创建并返回 FarmScene 场景对象
    return FarmScene::create();
}

bool FarmScene::init() {
    // 调用父类的初始化函数
    if (!Scene::init()) {
        return false;
    }

    // 获取屏幕可见区域的大小和原点
    Size visibleSize = Director::getInstance()->getVisibleSize();
  //    Size winSize = Director::getInstance()->getWinSize();

    // 创建并添加TMX地图
    tileMap = TMXTiledMap::create("Myfarm.tmx");
    //tileMap = TMXTiledMap::create("shed.tmx");
    if (tileMap) {
        // 获取屏幕的大小
     //   Size winSize = Director::getInstance()->getWinSize();

        // 设置锚点为中心（以地图中心作为参照点）
        tileMap->setAnchorPoint(Vec2(0.5, 0.5));
        // 计算地图的位置，将地图放置在屏幕中央
        float posX = visibleSize.width / 2;
        float posY = visibleSize.height / 2;
        tileMap->setPosition(Vec2(posX, posY));

        // 将地图添加到场景中
        this->addChild(tileMap, 0);
    }


    // 获取对象层（每个背包格子的位置）
    auto objectGroup = tileMap->getObjectGroup("crops_layer");
    if (!objectGroup) {
        CCLOG("Failed to get object group 'crops_layer'");
        return false;
    }

    // 作物格子管理（假设最大36格）
    crops.resize(36);
    for (int i = 0; i < 36; ++i) {
    
            crops[i].name = "";      // 作物名
            //  crops[i].quantity = 0;   // 物品数量

            // 获取对象层中每个格子的坐标
            auto object = objectGroup->getObject("crop" + std::to_string(i + 1));  // 获取第 i+1 个格子
            float posX = object["x"].asFloat();
            float posY = object["y"].asFloat();
            float width = object["width"].asFloat();
            float height = object["height"].asFloat();
            log("Player Position: x=%d, y=%d", posX, posY);  // 打印坐标信息


            // 创建透明纹理的精灵
            auto sprite = Sprite::create("load1.png");  // 默认无纹理
            sprite->setPosition(Vec2(posX, posY));        // 设置位置
            sprite->setAnchorPoint(Vec2(0, 0));     // 设置锚点
            sprite->setContentSize(Size(width, height));  // 设置大小
            tileMap->addChild(sprite, 1);  // 添加到瓦片地图
            crops[i].sprite = sprite;

     
    }

    // 初始添加
  //  addItem("crop1");
  //  addItem("crop2");
  //  addItem("crop3");
  // addItem("crop4");

    return true;
}

void FarmScene::addItem(const std::string& itemName) {
    for (int i = 0; i < crops.size(); ++i) {
        if (crops[i].name == itemName) {
            // 如果物品已存在，更新显示
            updateItemTexture(i);
            return;
        }
    }
    for (int i = 0; i < crops.size(); ++i) {
        if (crops[i].name == "") {
            // 找到空格子，放入物品
            crops[i].name = itemName;
            updateItemTexture(i);
            return;
        }
    }
}


// 更新物品显示纹理
void FarmScene::updateItemTexture(int slotIndex) {
    // 检查槽位索引范围是否合法
    if (slotIndex < 0 || slotIndex >= crops.size()) {
        CCLOG("Invalid slot index: %d", slotIndex);
        return;
    }

    auto& slot = crops[slotIndex];

    // 检查槽位的精灵是否为空
    if (!slot.sprite) {
        CCLOG("Slot sprite is null for slot index: %d", slotIndex);
        return;
    }

    // 如果槽位没有物品名称，直接返回
    if (slot.name.empty()) {
        CCLOG("Slot %d is empty.", slotIndex);
        return;
    }

    // 拼接图片路径
    std::string texturePath = slot.name + ".png"; // 假设图片在 Resources 文件夹

    // 尝试从纹理缓存加载纹理
    auto texture = Director::getInstance()->getTextureCache()->addImage(texturePath);
    if (texture) {
        // 更新精灵的纹理
        slot.sprite->setTexture(texture);
        slot.sprite->setScale(3.0f); // 根据需要调整缩放
        CCLOG("Updated texture for slot %d: %s", slotIndex, texturePath.c_str());
    }
    else {
        CCLOG("Failed to load texture: %s", texturePath.c_str());
    }


}

// 清除物品纹理
void FarmScene::clearItemTexture(int slotIndex) {
    if (slotIndex < 0 || slotIndex >= crops.size()) return;

    auto& slot = crops[slotIndex];
    slot.sprite->setTexture(nullptr);  // 清空纹理
    slot.sprite->removeAllChildren();  // 清空子节点（如数量标签）
}