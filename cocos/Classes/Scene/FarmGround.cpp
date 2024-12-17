#include "FarmGround.h"

USING_NS_CC;

bool FarmScene::init() {
    if (!Scene::init()) {
        return false;
    }

    // 加载地图，放在中间
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    tileMap = TMXTiledMap::create("Myfarm.tmx");
    if (tileMap) {
        tileMap->setAnchorPoint(Vec2(0.5, 0.5));
        float posX = visibleSize.width / 2;
        float posY = visibleSize.height / 2;
        tileMap->setPosition(Vec2(posX, posY));
        this->addChild(tileMap, 0);
        tileMap->setScale(2);
		SceneWidth = tileMap->getContentSize().width*2;
		SceneHeight = tileMap->getContentSize().height*2;

		CCLOG("Loaded the tile map successfully: (%f,%f)", SceneWidth, SceneHeight);
    }
    else {
        CCLOG("Failed to load the tile map");
    }

    //----------------------------------------------------
    // 功能：人物初始化
	// 说明：创建人物对象，初始化人物属性
    // 图层：
    //----------------------------------------------------
    Player* player = Player::getInstance("me");

    //----------------------------------------------------
    // 功能：添加背包图层
	// 说明：添加背包图层到当前场景，初始化背包
    // 图层：Backpacklayer
    //----------------------------------------------------
    backpackLayer = BackpackLayer::create();
    if (backpackLayer) {
        this->addChild(backpackLayer, Backpacklayer);
    }
    else
		CCLOG("Failed to load the backpack layer");


    //----------------------------------------------------
    // 功能：添加时间系统
    // 说明：添加时间系统到当前场景，初始化时间系统
    // 图层：Timesystemlayer
    //----------------------------------------------------
    timeSystem = TimeSystem::getInstance();  
    Node* parentNode = this;  
    parentNode->addChild(timeSystem, Timesystemlayer);


    //----------------------------------------------------
    // 功能：添加移动主角
    // 说明：添加主角，主角位于地图中央
    // 图层：Playerlayer
    //----------------------------------------------------
    auto sprite_move = moveable_sprite_key_walk::create("Jas_Winter.plist", "Jas_Winter");
    if(sprite_move)
    {
        sprite_move->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        this->addChild(sprite_move, Playerlayer);

        sprite_move->init_keyboardlistener();

        sprite_move->schedule([this, sprite_move](float dt) { // 捕获 `this` 和 `sprite_move`
            sprite_move->update(dt);                         // 更新人物移动逻辑
            this->updateCamera(sprite_move);                 // 更新相机位置
            }, "update_key_person");

    }

    //----------------------------------------------------
	// 功能：添加任务栏
    // 说明：添加任务栏到当前场景
    // 图层：Taskbarlayer
    //----------------------------------------------------
    TaskBarLayer* taskBarLayer = TaskBarLayer::create();
    tileMap->addChild(taskBarLayer,Taskbarlayer);


    //----------------------------------------------------
    // 功能：作物模块
	// 说明：在地图上添加作物格子，用于种植作物
    // 图层：Playerlayer
    //----------------------------------------------------
    // 获取对象层（每个作物格子的位置）
    auto objectGroup = tileMap->getObjectGroup("crops_layer");
    if (!objectGroup) {
        CCLOG("Failed to get object group 'crops_layer'");
        return false;
    }

    // 作物格子管理（假设最大36格）
    crops.resize(36);
    for (int i = 0; i < 36; ++i) {

		crops[i].isPlanted = false; // 是否种植了作物
        crops[i].name = "";      // 作物名

        // 获取对象层中每个格子的坐标
        auto object = objectGroup->getObject("crop" + std::to_string(i + 1));  // 获取第 i+1 个格子
        float posX = object["x"].asFloat();
        float posY = object["y"].asFloat();
        float width = object["width"].asFloat();
        float height = object["height"].asFloat();

        // 创建透明纹理的农作物精灵
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
    // 创建并返回 FarmScene 场景对象
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

void FarmScene::updateCamera(Node* player) {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Size mapSize = tileMap->getContentSize();
    float scale = tileMap->getScale();

    // 获取人物位置
    Vec2 playerPos = player->getPosition();

    // 计算地图的初始偏移量（由于锚点在中心）
    float mapOffsetX = visibleSize.width / 2;
    float mapOffsetY = visibleSize.height / 2;

    // 计算场景新的位置（人物在屏幕中央）
    float x = std::max(playerPos.x - visibleSize.width / 2, 0.0f);
    float y = std::max(playerPos.y - visibleSize.height / 2, 0.0f);

    // 限制场景边界（防止场景超出地图范围）
    float maxX = mapSize.width * scale - visibleSize.width;
    float maxY = mapSize.height * scale - visibleSize.height;

    x = std::min(x, maxX);
    y = std::min(y, maxY);

    // 设置场景位置，考虑锚点偏移
    tileMap->setPosition(Vec2(mapOffsetX - x, mapOffsetY - y));
	//CCLOG("Camera position: (%f, %f)", x, y);
}
