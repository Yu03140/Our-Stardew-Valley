#include "FarmGround.h"

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
    init_mouselistener();
    // 加载地图，放在中间
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
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

    }    
    main_char = sprite_move;

    tileMap = TMXTiledMap::create("Myfarm.tmx");
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
    backpackLayer = BackpackLayer::getInstance();
    if (backpackLayer) {
        this->addChild(backpackLayer, Backpacklayer);
        backpackLayer->setName("backpackLayer");
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

    // 计算经过缩放后的实际尺寸
    Size originalSize = sprite_move->getContentSize();
    float scale = sprite_move->getScale();
    Size scaledSize = Size(originalSize.width * scale, originalSize.height * scale);
    auto sprite_tool = moveable_sprite_key_tool::create("Tools.plist");
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

    //----------------------------------------------------
    // 功能：添加任务栏
    // 说明：添加任务栏到当前场景
    // 图层：Taskbarlayer
    //----------------------------------------------------
    taskBarScene = TaskBarLayer::create(); 
    this->addChild(taskBarScene,3);     

    Vec2 map_pos = tileMap->getPosition();  // 获取瓦片地图的偏移位置
    Size tileSize = tileMap->getTileSize(); // 获取瓦片尺寸
    float mapscale = tileMap->getScale();      // 获取瓦片地图的缩放因子（如果有的话）
    /*--------------------------------------------renew2----------------------------------------*/
    
    //----------------------------------------------------
    // 功能：树模块
    // 说明：在地图上添加树格子，用于生成树
    // 图层：Playerlayer
    //----------------------------------------------------
    // 获取对象层（每个作物格子的位置）
    auto objectGroup_tree = tileMap->getObjectGroup("forest");
    if (!objectGroup_tree) {
        CCLOG("Failed to get object group 'tree'");
        return false;
    }

    // 树格子管理
    GoodsManager* tree_manager = GoodsManager::create();
    auto objects_tree = objectGroup_tree->getObjects();

    for (const auto& object : objects_tree) {
        // 通过 object 中的数据判断是否是名称为 'tree' 的对象
        auto dict = object.asValueMap();
        std::string objectName = dict["name"].asString();
        //处理所有名称为树的对象
        if (objectName == "trees") {
            auto sprite = getable_goods::create("goods.plist");
            sprite->add_in(dict, sprite, "tree", tileMap);
            //加入树格子管理器
            tree_manager->add_goods(sprite);
        }
    }
    this->addChild(tree_manager);
    tree_manager->schedule([tree_manager](float delta) {
        tree_manager->random_access();
        }, 6.0f, "RandomAccessSchedulerKey");
   
    //----------------------------------------------------
    // 功能：草模块
    // 说明：在地图上添加草格子，用于生成草
    // 图层：Playerlayer
    //----------------------------------------------------
    // 获取对象层（每个作物格子的位置）
    auto objectGroup_grass = tileMap->getObjectGroup("grass");
    if (!objectGroup_grass) {
        CCLOG("Failed to get object group 'grass'");
        return false;
    }

    // 草格子管理
    GoodsManager* grass_manager = GoodsManager::create();
    auto objects_grass = objectGroup_grass->getObjects();

    for (const auto& object : objects_grass) {
        // 通过 object 中的数据判断是否是名称为 'grass' 的对象
        auto dict = object.asValueMap();
        std::string objectName = dict["name"].asString();
        //处理所有名称为草的对象
        if (objectName == "grass") {
            auto sprite = getable_goods::create("goods.plist");
            sprite->add_in(dict, sprite,"grass",tileMap);
            //加入草格子管理器
            grass_manager->add_goods(sprite);
        }
    }
    this->addChild(grass_manager);
    grass_manager->schedule([grass_manager](float delta) {
         grass_manager->random_access();
        }, 6.0f, "RandomAccessSchedulerKey");

    /*--------------------------------------------renew2----------------------------------------*/
    
    //----------------------------------------------------
    // 功能：作物模块
    // 说明：在地图上添加作物格子，用于种植作物
    // 图层：Playerlayer
    //----------------------------------------------------
    // 获取对象层（每个作物格子的位置）
    auto objectGroup_crop = tileMap->getObjectGroup("crops_layer");
    if (!objectGroup_crop) {
        CCLOG("Failed to get object group 'crops_layer'");
        return false;
    }


    // 作物格子管理（假设最大36格）
    crops.resize(36);
    for (int i = 0; i < 36; ++i) {

        crops[i].name = "";      // 作物名

        // 获取对象层中每个格子的坐标
        auto object = objectGroup_crop->getObject("crop" + std::to_string(i + 1));  // 获取第 i+1 个格子
        float posX = object["x"].asFloat();
        float posY = object["y"].asFloat();
        float width = object["width"].asFloat();
        float height = object["height"].asFloat();

        // 创建透明纹理的精灵
        auto sprite = crop::create("crop.plist", width, height); // 默认无纹理

        sprite->setPosition(Vec2(posX, posY));        // 设置位置
        sprite->setAnchorPoint(Vec2(0, 0));     // 设置锚点
        sprite->setContentSize(Size(width, height));  // 设置大小
        tileMap->addChild(sprite, 2);  // 添加到瓦片地图
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
    float cameraX = clamp(playerPosition.x, visibleSize.width - SceneWidth / 2, SceneWidth / 2);
    float cameraY = clamp(playerPosition.y, visibleSize.height - SceneHeight / 2, SceneHeight / 2);

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

/*------------------------------------------------------renew-------------------------------------------------------------*/

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

    checkForButtonClick(MOUSE_POS);
    CCLOG("Mouse Position(global): (%f, %f)", MOUSE_POS.x, MOUSE_POS.y);
    // 1.5秒后将 MOUSE_POS 置为 (0, 0)，并且不影响其他程序运行
    this->scheduleOnce([this](float dt) {
        MOUSE_POS = Vec2::ZERO;
        CCLOG("Mouse Position reset to: (%f, %f)", MOUSE_POS.x, MOUSE_POS.y);
        }, 1.5f, "reset_mouse_pos_key");
}

// 功能：检测是否点击了Button并切换场景
void FarmScene::checkForButtonClick(Vec2 mousePosition)
{
    // 获取 Button 对象层（Button 层的名称为 "Button"）
    auto objectGroup = tileMap->getObjectGroup("Button");
    if (!objectGroup) {
        CCLOG("Failed to get object group 'Button'");
        return;
    }

    CCLOG("Successed to get object grouo 'Button'");

    // 获取 Door 对象的坐标和尺寸

    std::string Objectname[3] = { "Mines_Door","Home_Door","Shed_Door" };
    Scene* nextScene = nullptr;

    for (int i = 0; i < 3; i++) {
        auto object = objectGroup->getObject(Objectname[i]);
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

            if (backpackLayer) 
                this->removeChild(backpackLayer);  // 移除背包层
            CCLOG("remove backpacklayer successfully!");
            CCLOG("Door clicked! Switching to MinesScene...");

            switch (i) {
            case 0:
                // 切换到 MinesScene
                nextScene = MinesScene::createScene();
                break;
            case 1:
                // 切换到 HomeScene
                nextScene = HomeScene::createScene();
                break;
            case 2:
                // 切换到 ShedScene
                nextScene = ShedScene::createScene();
                break;
            }

            // 如果我们成功获取到下一个场景，就推入栈中
            if (nextScene) {
                nextScene->retain();  // 保留场景，避免被销毁
                Director::getInstance()->pushScene(nextScene);
            }
            return;
        }
    }
}

// 进入场景时重新加入背包层
void FarmScene::onEnter()
{
    Scene::onEnter();
    is_infarm = 1;
    CCLOG("IN FARM");
    // 如果背包层不存在于当前场景，重新添加
    if (backpackLayer && !this->getChildByName("backpackLayer")) {
        this->addChild(backpackLayer, Backpacklayer);
        backpackLayer->setName("backpackLayer");
        CCLOG("readd backpacklayer");
    }
}
void FarmScene::onExit()
{
    Scene::onExit();
    is_infarm = 0;
    CCLOG("LEAVE FARM");

}


/*------------------------------------------------------renew-------------------------------------------------------------*/
