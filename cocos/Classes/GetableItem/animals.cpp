#include "animals.h"

std::string animals::animals_name = "";
int animals::produce_day = 0;
cocos2d::Sprite animals::produce;
cocos2d::Texture2D* animals::transparent_texture = nullptr;
cocos2d::Size animals::produce_size = cocos2d::Size(0, 0);
cocos2d::Vec2 animals::produce_pos = cocos2d::Vec2(0, 0);


// 创建实例
animals* animals::create(const std::string& plist_name, std::string name, cocos2d::Vec2 pos, cocos2d::Size size)
{
    //加载plist文件
    cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plist_name);
    
    //设置基本信息
    animals_name = name;
    produce_size = size;
    produce_pos = pos;
    produce_day = ANIMAL_MAP.at(name);

    //创建实例
    animals* animals_sprite = new animals();
    Sprite* produce_sprite = new Sprite();

    // 创建透明的内存块，设置为全透明 (RGBA8888 格式)
    int dataSize = size.width * size.height * 4;  // 每个像素 4 字节（RGBA 格式）
    unsigned char* transparentData = new unsigned char[dataSize];

    // 填充透明数据 (每个像素的 4 个通道值都为 0)
    memset(transparentData, 0, dataSize);

    // 创建透明纹理
    cocos2d::Texture2D* transparentTexture = new cocos2d::Texture2D();
    transparentTexture->initWithData(transparentData, dataSize, cocos2d::backend::PixelFormat::RGBA8888, size.width, size.height, size);
    transparent_texture = transparentTexture;

    // 释放内存
    delete[] transparentData;
    //判断是否能成功创建
    if (transparentTexture && animals_sprite && produce_sprite)
    {
        animals_sprite->setSpriteFrame(animals_name + "-front.png");
        animals_sprite->autorelease();
        animals_sprite->init_mouselistener();
        animals_sprite->setScale(2.0f);  // 将精灵放大 2 倍
        produce_sprite->initWithTexture(transparentTexture);
        produce_sprite->autorelease();
        produce_sprite->setScale(2.0f);  // 将精灵放大 2 倍
        produce.setPosition(pos);
        CCLOG("Creation animal successfully!");
        return animals_sprite;
    }
    CCLOG("Creation animal unsuccessfully!");
    CC_SAFE_DELETE(animals_sprite);
    return nullptr;
}

// 初始化鼠标监听器
void animals::init_mouselistener()
{
    // 创建鼠标监听器
    auto listener = cocos2d::EventListenerMouse::create();

    // 鼠标按下时的回调
    listener->onMouseDown = CC_CALLBACK_1(animals::on_mouse_click, this);

    // 获取事件分发器，添加监听器
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

// 鼠标按下时的回调
void animals::on_mouse_click(cocos2d::Event* event)
{
    auto mouse_event = dynamic_cast<cocos2d::EventMouse*>(event);
    auto mouse_pos = this->getParent()->convertToNodeSpace(mouse_event->getLocationInView());
    auto animals_pos = this->getPosition();
    auto animals_size = this->getContentSize();
    CCLOG("animals clicked");
    if(is_in_control){
        if (mouse_pos.x > animals_pos.x - animals_size.width / 2 &&
            mouse_pos.x < animals_pos.x + animals_size.width / 2 &&
            mouse_pos.y > animals_pos.y - animals_size.height / 2 &&
            mouse_pos.y < animals_pos.y + animals_size.height / 2)//点击动物
        {
            if (backpackLayer->getSelectedItem() == FOOD) {
                this->feed();
            }
        }
        else if (mouse_pos.x > produce_pos.x - produce_size.width / 2 &&
            mouse_pos.x < produce_pos.x + produce_size.width / 2 &&
            mouse_pos.y > produce_pos.y - produce_size.height / 2 &&
            mouse_pos.y < produce_pos.y + produce_size.height / 2)//点击生成物放置区
        {
            if (is_produce) {
                this->harvest();
            }
        }
    }
}

//喂养
void animals::feed()
{
    if (feed_today) {
        feed_today--;
        //背包食物-1
        backpackLayer->removeItem(FOOD);
        CCLOG("feed successfully");
    }
    else 
        CCLOG("couldn't feed today");
}

//生成附属品
void animals::create_produce()
{
    if (feed_count % produce_day == 0 && feed_count) 
    {
        produce.setSpriteFrame(animals_name + "-produce.png");//显示生成物
        is_produce = 1;
        CCLOG("create produce");
    }
}

//收获功能
void animals::harvest()
{    
    //把生成物加入背包
    backpackLayer->addItem(PRODUCE_MAP.at(animals_name));
    //任务经验增加EXPERIENCE
    Player* player = Player::getInstance("me");
    player->playerproperty.addExperience(EXPERIENCE);
    produce.setTexture(transparent_texture);
    is_produce = 0;
}

// 根据移动方向设置精灵的图片
void animals::updateDirection(const cocos2d::Vec2& movementDirection) {
    float angle = movementDirection.getAngle();  // 计算角度

    // 根据角度选择图片（例如，四个方向）
    if (angle > -M_PI_4 && angle <= M_PI_4) {
        // 向右
        this->setSpriteFrame(animals_name + "-right.png");
    }
    else if (angle > M_PI_4 && angle <= 3 * M_PI_4) {
        // 向上
        this->setSpriteFrame(animals_name + "-back.png");
    }
    else if (angle > -3 * M_PI_4 && angle <= -M_PI_4) {
        // 向下
        this->setSpriteFrame(animals_name + "-front.png");
    }
    else {
        // 向左
        this->setSpriteFrame(animals_name + "-left.png");
    }
}
//游荡
void animals::randmove(cocos2d::TMXTiledMap* tileMap)
{
    // 获取瓦片地图的大小
    auto mapSize = tileMap->getMapSize();
    auto currentPos = this->getPosition();

    // 随机选择一个瓦片的坐标
    int randomX = rand() % int(mapSize.width - 20);
    int randomY = rand() % int(mapSize.height - 20);

    auto tileSize = tileMap->getTileSize();  // 获取瓦片的大小

    // 计算瓦片的世界坐标
    float worldX = randomX * tileSize.width + tileMap->getPosition().x;
    float worldY = randomY * tileSize.height + tileMap->getPosition().y;

    // 使用 MoveTo 动作移动精灵
    auto targetPosition = cocos2d::Vec2(worldX, worldY);
    auto movementDirection = targetPosition - currentPos;  // 计算移动方向
    this->updateDirection(movementDirection);
    float distance = movementDirection.length();
    auto moveAction = cocos2d::MoveTo::create(distance/SPEED, targetPosition);  // 移动到目标位置
    this->runAction(moveAction);
}
//不定时游荡
void animals::scheduleRandomMove(cocos2d::TMXTiledMap* tileMap) {
    // 每3秒随机移动一次
    this->schedule([this, tileMap](float dt) {
        randmove(tileMap);
        }, 3.0f, "random_move_key");
}

//新一天的更新
void animals::update_day(float deltaTime)
{
    if (timeSystem->getDay() != now_day)//今天结束了
    {
        if (animals_name != "") {
            if (feed_today == 0)//说明今天喂养次数达到要求
            {
                feed_count++;
                //查看是否需要更新成长状态
                this->create_produce();
            }
        }
        now_day = timeSystem->getDay();
        feed_today = 1;
    }
}