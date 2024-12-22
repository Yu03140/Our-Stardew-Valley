#include "FarmGround.h"

USING_NS_CC;

FarmScene* FarmScene::instance = nullptr;
moveable_sprite_key_walk* sprite_move = nullptr;

bool FarmScene::init() {
    // 调用父类的初始化函数

    if (!Scene::init()) {
        return false;
    }
    //=====================================12.22========================================================================




    //=====================================12.22=================================================================================

    init_mouselistener();
        // 加载地图，放在中间
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    tileMap = TMXTiledMap::create("Myfarma.tmx");
    if (tileMap) {
        tileMap->setAnchorPoint(Vec2(0.5, 0.5));
        float posX = visibleSize.width / 2;
        float posY = visibleSize.height / 2;
        tileMap->setPosition(Vec2(posX, posY));
        this->addChild(tileMap, 0);
        tileMap->setScale(MapSize);
        SceneWidth = tileMap->getContentSize().width * MapSize;
        SceneHeight = tileMap->getContentSize().height * MapSize;

        CCLOG("Loaded the tile map successfully: (%f,%f)", SceneWidth, SceneHeight);
    }
    else {
        CCLOG("Failed to load the tile map");
    }
    //===========================================================================================================================
    house = Sprite::create("houses.png"); // 替换为你的房子图片路径
    house->setPosition(Vec2(600, 600)); // 设置房子的初始位置
    house->setScale(MapSize);
    this->addChild(house);

    shed= Sprite::create("Big Shed.png"); // 替换为你的房子图片路径
    shed->setPosition(Vec2(0, 1100)); // 设置房子的初始位置
    shed->setScale(MapSize);
    this->addChild(shed);

    badWarmHouse = Sprite::create("badGreenhouse.png"); // 替换为你的房子图片路径
    badWarmHouse->setPosition(Vec2(-330, 0)); // 设置房子的初始位置
    badWarmHouse->setScale(MapSize);
    this->addChild(badWarmHouse);


    //===========================================================================================================================

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
    if (timeSystem->getParent() == nullptr) {
        parentNode->addChild(timeSystem, Timesystemlayer);
    }

    //----------------------------------------------------
    // 功能：添加移动主角
    // 说明：添加主角，主角位于地图中央
    // 图层：Playerlayer
    //----------------------------------------------------
    auto sprite_move = moveable_sprite_key_walk::create("Jas_Winter.plist", "Jas_Winter");
    if (sprite_move)
    {
        sprite_move->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        this->addChild(sprite_move, Playerlayer);

        sprite_move->init_keyboardlistener();

        sprite_move->schedule([this, sprite_move](float dt) { // 捕获 `this` 和 `sprite_move`
            sprite_move->update(dt);                         // 更新人物移动逻辑
            updateCameraPosition(dt, sprite_move);                 // 更新相机位置
            }, "update_key_person");
 //===========================================================================================================================

        schedule([this, sprite_move](float dt) {
            this->update(dt, sprite_move);  // 传递 sprite_move 作为参数
            }, "update_key_scene");
        CCLOG("diao yong cheng gong la");

    }
//===========================================================================================================================

    // 计算经过缩放后的实际尺寸
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


    //auto animal = animals::create("Animals.plist", "Pig", Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y),Size(100,100));
    //if (animal)
    //{
    //    animal->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    //    this->addChild(animal, 1);
    //    animal->init_mouselistener();
    //    animal->scheduleRandomMove(tileMap);
    //    animal->schedule([animal](float dt) {
    //        animal->update(dt);
    //        }, "update_animal");
    //}


    //----------------------------------------------------
    // 功能：添加任务栏
    // 说明：添加任务栏到当前场景
    // 图层：Taskbarlayer
    //----------------------------------------------------
    auto taskBarScene = TaskBarLayer::create();
    tileMap->addChild(taskBarScene, 3);

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

    Vec2 map_pos = tileMap->getPosition();
    // 作物格子管理（假设最大36格）
    crops.resize(36);
    for (int i = 0; i < 36; ++i) {

        crops[i].name = "";      // 作物名

        // 获取对象层中每个格子的坐标
        auto object = objectGroup->getObject("crop" + std::to_string(i + 1));  // 获取第 i+1 个格子
        float posX = object["x"].asFloat();
        float posY = object["y"].asFloat();
        float width = object["width"].asFloat();
        float height = object["height"].asFloat();

		CCLOG("Crop %d: x=%f, y=%f, width=%f, height=%f", i, posX, posY, width, height);


        // 创建透明纹理的精灵
        auto sprite = crop::create("crop_m.plist", width, height); // 默认无纹理

        sprite->setPosition(Vec2(posX, posY));        // 设置位置
        sprite->setAnchorPoint(Vec2(0, 0));     // 设置锚点
        sprite->setContentSize(Size(width, height));  // 设置大小
        tileMap->addChild(sprite, 2);  // 添加到瓦片地图
        sprite->init_mouselistener();
        crops[i].sprite = sprite;
        //Vec2 worldPos = sprite->convertToWorldSpace(Vec2(0, 0));
        //log("World Position: x=%f, y=%f", worldPos.x, worldPos.y);


        sprite->schedule([sprite](float dt) {
            sprite->update_day(dt);
            }, "update_crop");

    }
//===========================================================================================================================

    //----------------------------------------------------
    // 功能：钓鱼模块
    // 说明：
    // 图层：
    //----------------------------------------------------
    // 
        // 获取对象层
    auto barrierobjectGroup = tileMap->getObjectGroup("barriers");
    if (!barrierobjectGroup) {
        CCLOG("Failed to get object group 'barriers'");
        return false;
    }

    // 障碍物格子管理（假设最大36格）
    fish.resize(1);
    //   for (int i = 0; i < 36; ++i) {

    fish[0].name = "";      // 作物名

    // 获取对象层中每个格子的坐标
    auto object = barrierobjectGroup->getObject("barrier9");

    float posX = object["x"].asFloat();
    float posY = object["y"].asFloat();
    float width = object["width"].asFloat();
    float height = object["height"].asFloat();

    CCLOG("fish %d: x=%f, y=%f, width=%f, height=%f", 0, posX, posY, width, height);


    // 创建透明纹理的精灵
    auto sprite1 = fish::create("crop_m.plist", width, height); // 默认无纹理

    sprite1->setPosition(Vec2(posX, posY));        // 设置位置
    sprite1->setAnchorPoint(Vec2(0, 0));     // 设置锚点
    sprite1->setContentSize(Size(width, height));  // 设置大小
    tileMap->addChild(sprite1, 2);  // 添加到瓦片地图
    sprite1->init_mouselistener();
    fish[0].sprite = sprite1;
    //Vec2 worldPos = sprite->convertToWorldSpace(Vec2(0, 0));
    //log("World Position: x=%f, y=%f", worldPos.x, worldPos.y);


 // sprite1->schedule([sprite1](float dt) {
 //     sprite1->update_day(dt);
 //     }, "update_fish");
 //
    return true;
}

void FarmScene::update(float dt,moveable_sprite_key_walk* sprite_move) {

    if (!sprite_move ) {
        CCLOG("wandanla");
        return;
    }
    // 获取房子的边界
    Vec2 housePos = house->getPosition();  // 房子的中心位置
    Size houseSize = house->getContentSize() * MapSize;  // 房子的尺寸

    // 获取人物的中心位置
    Vec2 playerPos = sprite_move->getPosition();

    // 判断人物是否在房屋的矩形区域内
    bool isPlayerInsideHouse = playerPos.x > housePos.x - houseSize.width / 2 &&
        playerPos.x < housePos.x + houseSize.width / 2 &&
        playerPos.y > housePos.y - houseSize.height / 2 &&
        playerPos.y < housePos.y + houseSize.height / 2;


    // 获取房子的边界
    Vec2 shedPos = shed->getPosition();  // 房子的中心位置
    Size shedSize = shed->getContentSize() * MapSize;  // 房子的尺寸


    // 判断人物是否在棚屋的矩形区域内
    bool isPlayerInsideshed = playerPos.x > shedPos.x - shedSize.width / 2 &&
        playerPos.x < shedPos.x + shedSize.width / 2 &&
        playerPos.y > shedPos.y - shedSize.height / 2 &&
        playerPos.y < shedPos.y + shedSize.height / 2;

//====================================12.20=================================================================================
//===================================12.21==================================================================================

    // 根据人物是否在房屋区域内，调整房子的透明度
    house->setOpacity(isPlayerInsideHouse ? 128 : 255);
    shed->setOpacity(isPlayerInsideshed ? 128 : 255);

}

// 初始化鼠标监听器
void FarmScene::init_mouselistener()
{
    // 创建鼠标监听器
    auto listener = cocos2d::EventListenerMouse::create();

    // 鼠标回调
    listener->onMouseDown = CC_CALLBACK_1(FarmScene::on_mouse_click, this);

    // 获取事件分发器，添加监听器
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

// 鼠标按下时的回调
void FarmScene::on_mouse_click(cocos2d::Event* event)
{
    //获取鼠标在窗口中的位置,转换到地图坐标
    auto mouse_event = dynamic_cast<cocos2d::EventMouse*>(event);
    Vec2 mousePosition = mouse_event->getLocationInView();
    auto camera = Director::getInstance()->getRunningScene()->getDefaultCamera();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 windowOrigin = camera->getPosition() - Vec2(visibleSize.width / 2, visibleSize.height / 2);
    Vec2 mouse_pos = mousePosition + windowOrigin;
    MOUSE_POS = mouse_pos;
    CCLOG("Mouse Position(global): (%f, %f)", MOUSE_POS.x, MOUSE_POS.y);
    checkForwarmhouseClick(mouse_pos);
   // fish->checkForPoolClick(mouse_pos);
   // checkForPoolClick(mouse_pos);
    //CCLOG("Fish barrier properties: Pos(%f, %f), Width: %f, Height: %f", fish->barrierPos.x, fish->barrierPos.y, fish->barrierWidth, fish->barrierHeight);

    // 0.1秒后将 MOUSE_POS 置为 (0, 0)，并且不影响其他程序运行
    this->scheduleOnce([this](float dt) {
        MOUSE_POS = Vec2::ZERO;
        CCLOG("Mouse Position reset to: (%f, %f)", MOUSE_POS.x, MOUSE_POS.y);
        }, 1.5f, "reset_mouse_pos_key");
}


// 功能：检测是否点击了warmhouse并切换场景
bool FarmScene::checkForwarmhouseClick(Vec2 mousePosition)
{
    // 获取 warmhouse 对象层（warmhouse 层的名称为 "warmhouse"）
    auto objectGroup = tileMap->getObjectGroup("warmhouse");

    CCLOG("Successed to get object group 'warmhouse'");


    std::string Objectname = "warmhouse";
    Sprite* new_warmhouse = nullptr;


    auto object = objectGroup->getObject(Objectname);
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

    // 判断点击位置是否在 Door 区域内
    if (mousePosition.x >= pos.x && mousePosition.x <= pos.x + width &&
        mousePosition.y >= pos.y && mousePosition.y <= pos.y + height) {

        replaceHouseImage();


        return true;
    }

    return false;


}

//
//// 功能：检测是否点击了Pool并切换场景
//void FarmScene::checkForPoolClick(Vec2 mousePosition)
//{
//   // Vec2 playerPos = sprite_move->getPosition();
//
//    // 获取 barriers 对象层（barriers 层的名称为 "barriers"）
//    auto objectGroup = tileMap->getObjectGroup("barriers");
//    if (!objectGroup) {
//        CCLOG("Failed to get object group 'barriers'");
//        return;
//    }
//
//    CCLOG("Successed to get object group 'barriers'");
//
//
//    std::string Objectname = "barrier9";
//    // Sprite* new_warmhouse = nullptr;
////    CCLOG("ddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd");
//
//
//    auto object = objectGroup->getObject(Objectname);
//    float posX = object["x"].asFloat();
//    float posY = object["y"].asFloat();
//    float width = object["width"].asFloat() * MapSize;
//    float height = object["height"].asFloat() * MapSize;
//    auto sprite = Sprite::create();
//    sprite->setPosition(Vec2(posX, posY));
//    sprite->setAnchorPoint(Vec2(0, 0));
//    sprite->setContentSize(Size(width, height));
//    tileMap->addChild(sprite);
//    Vec2 pos = sprite->convertToWorldSpace(Vec2(0, 0));
//    CCLOG("POS: %f, %f", pos.x, pos.y);
//
//    // 判断点击位置是否在区域内
//    if (mousePosition.x >= pos.x && mousePosition.x <= pos.x + width &&
//        mousePosition.y >= pos.y && mousePosition.y <= pos.y + height) {
//        // 获取选中的物品
//        std::string selectedItem = backpackLayer->getSelectedItem();
//        if (selectedItem == "Rod1") {
//            // 开始钓鱼
//            CCLOG("yyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy");
//            CCLOG("%d",fish);
//
//            fish->carry_fishing(mousePosition);
//            CCLOG("wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww");
//
//        }
//        else {
//            CCLOG("Please select a fishing rod first.");
//        }
//        return;
//    }
//    
//}
//


// 替换精灵的图片
void FarmScene::replaceHouseImage() {
    // 替换为新的精灵图片
    badWarmHouse->setTexture("newGreenhouse.png");  // 替换为新的房子图片
}

bool FarmScene::checkCollisionWithBorder(cocos2d::Vec2 position) {
    // 获取地图的图层数据
    auto layer = tileMap->getLayer("Border");

    // 检查图层是否有效
    if (!layer) {
        CCLOG("Failed to get Border layer!");
        return false;
    }

    // 获取地图的图层大小和单个瓦片的大小
    cocos2d::Size layerSize = layer->getLayerSize();
    cocos2d::Size tileSize = layer->getMapTileSize();

    // 获取摄像机的偏移位置
    auto camera = Director::getInstance()->getRunningScene()->getDefaultCamera();
    cocos2d::Vec2 cameraPos = cocos2d::Vec2(camera->getPosition3D().x, camera->getPosition3D().y);  // 提取x, y坐标

    // 将玩家位置转换为相对于摄像机的坐标
    cocos2d::Vec2 relativePos = position - cameraPos;

    // 将相对位置转换为 tile 坐标
    cocos2d::Vec2 tileCoord = cocos2d::Vec2(relativePos.x / tileSize.width, relativePos.y / tileSize.height);

    // 检查坐标是否在有效范围内
    if (tileCoord.x < 0 || tileCoord.x >= layerSize.width || tileCoord.y < 0 || tileCoord.y >= layerSize.height) {
     //   CCLOG("Position is out of bounds: (%f, %f)", relativePos.x, relativePos.y);
        return false;  // 如果超出范围，返回 false
    }

    // 获取坐标对应的 tile GID
    int tileGID = layer->getTileGIDAt(tileCoord);

    // 判断该位置是否为障碍物
    return tileGID != 0; // 如果 GID 不为 0，则说明该位置有障碍物
}

//===================================12.21==================================================================================
FarmScene* FarmScene::getInstance() {
    if (instance == nullptr) {
        instance = FarmScene::create();
    }
    return instance;
}

Scene* FarmScene::createScene() {
    return getInstance();
}

void FarmScene::addItem(const std::string& itemName) {
    for (int i = 0; i < fish.size(); ++i) {
        if (fish[i].name == "") {
            // 找到空格子，放入物品
            fish[i].name = itemName;
            updateItemTexture(i);
            return;
        }
    }
    if (fish[0].name == "") {
        // 找到空格子，放入物品
        fish[0].name = itemName;
        updatefishTexture(0);
        return;
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

// 更新物品显示纹理
void FarmScene::updatefishTexture(int slotIndex) {
    // 检查槽位索引范围是否合法
    if (slotIndex < 0 || slotIndex >= fish.size()) {
        CCLOG("Invalid slot index: %d", slotIndex);
        return;
    }

    auto& slot = fish[slotIndex];

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

// 清除fish纹理
void FarmScene::clearfishTexture(int slotIndex) {
    if (slotIndex < 0 || slotIndex >= fish.size()) return;

    auto& slot = fish[slotIndex];
    slot.sprite->setTexture(nullptr);  // 清空纹理
    slot.sprite->removeAllChildren();  // 清空子节点（如数量标签）
}

// 清除物品纹理
void FarmScene::clearItemTexture(int slotIndex) {
    if (slotIndex < 0 || slotIndex >= fish.size()) return;

    auto& slot = fish[slotIndex];
    slot.sprite->setTexture(nullptr);  // 清空纹理
    slot.sprite->removeAllChildren();  // 清空子节点（如数量标签）
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

    // 镜头位置要保持在地图边界内
    float cameraX = clamp(playerPosition.x, visibleSize.width / 2 - SceneWidth, SceneWidth - visibleSize.width / 2);
    float cameraY = clamp(playerPosition.y, visibleSize.height / 2 - SceneHeight, SceneHeight - visibleSize.height / 2);

    // 获取默认摄像头
    auto camera = Director::getInstance()->getRunningScene()->getDefaultCamera();

    // 设置摄像头位置
    if (camera) {
        camera->setPosition3D(Vec3(cameraX, cameraY, camera->getPosition3D().z));
        //CCLOG("Camera position: (%f, %f)", cameraX, cameraY);
        if (backpackLayer) {
            // 获取屏幕的可见大小
            float backpackX = cameraX - visibleSize.width / 2;
            float backpackY = cameraY - visibleSize.height / 2;

            // 设置背包层的位置
            backpackLayer->setPosition(Vec2(backpackX, backpackY));
        }
    }
}

