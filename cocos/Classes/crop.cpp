#include "crop.h"

//全局变量的时间中获取


// 定义静态成员变量并初始化
std::string crop::crop_name = "";
int crop::develop_day = 0;
cocos2d::Texture2D* crop::transparent_texture = nullptr;
cocos2d::Size crop::crop_size = cocos2d::Size(0, 0);

// 创建实例
crop* crop::create(const std::string& plist_name, float width, float height)
{
    //加载plist文件
    cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plist_name);
    crop_size.width = width;
    crop_size.height = height;

    //创建实例
    crop* crop_sprite = new crop();

    // 创建透明的内存块，设置为全透明 (RGBA8888 格式)
    int dataSize = width * height * 4;  // 每个像素 4 字节（RGBA 格式）
    unsigned char* transparentData = new unsigned char[dataSize];

    // 填充透明数据 (每个像素的 4 个通道值都为 0)
    memset(transparentData, 0, dataSize);

    // 创建透明纹理
    cocos2d::Texture2D* transparentTexture = new cocos2d::Texture2D();
    transparentTexture->initWithData(transparentData, dataSize, cocos2d::backend::PixelFormat::RGBA8888, width, height, cocos2d::Size(width, height));
    transparent_texture = transparentTexture;

    // 释放内存
    delete[] transparentData;
    //判断是否能成功创建
    if (transparentTexture)
    {
        crop_sprite->initWithTexture(transparentTexture);
        crop_sprite->autorelease();
        crop_sprite->init_mouselistener();
        CCLOG("Creation cope successfully!");
        return crop_sprite;
    }
    CCLOG("Creation cope unsuccessfully!");
    CC_SAFE_DELETE(crop_sprite);
    return nullptr;
}

// 初始化鼠标监听器
void crop::init_mouselistener()
{
    // 创建鼠标监听器
    auto listener = cocos2d::EventListenerMouse::create();

    // 鼠标按下时的回调
    listener->onMouseDown = CC_CALLBACK_1(crop::on_mouse_click, this);

    // 获取事件分发器，添加监听器
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

// 鼠标按下时的回调
void crop::on_mouse_click(cocos2d::Event* event)
{
    auto mouse_event = dynamic_cast<cocos2d::EventMouse*>(event);
    auto mouse_pos = this->getParent()->convertToNodeSpace(mouse_event->getLocationInView());
    auto crop_pos = this->getPosition();
    // 计算点击的有效范围
    float min_x = crop_pos.x - crop_size.width / 2;
    float max_x = crop_pos.x + crop_size.width / 2;
    float min_y = crop_pos.y - crop_size.height / 2;
    float max_y = crop_pos.y + crop_size.height / 2;

    // 输出鼠标点击位置和有效范围
    CCLOG("Mouse clicked at: (%.2f, %.2f)", mouse_pos.x, mouse_pos.y);
    CCLOG("Crop valid range: X[%.2f, %.2f], Y[%.2f, %.2f]", min_x, max_x, min_y, max_y);

    if (mouse_pos.x > crop_pos.x - crop_size.width / 2 &&
        mouse_pos.x < crop_pos.x + crop_size.width / 2 &&
        mouse_pos.y > crop_pos.y - crop_size.height / 2 &&
        mouse_pos.y < crop_pos.y + crop_size.height / 2)
    {
        CCLOG("click crop");
        if (develop_level == -1) //作物枯萎，点击铲除
        {
            this->clear();
            CCLOG("clear the dead crop");
        }
        else if (develop_level == 5) {
            this->harvest();
            CCLOG("harvest the crop");
        }
        else if (goods_inhand.goods_name == "Can" && develop_level > 0) //需要手上的工具为水壶，执行浇水
        {
            this->water();
            CCLOG("water this crop successfully");
        }
        else if (CROP_MAP.count(goods_inhand.goods_name) && develop_level == 0) //如果手上拿的物品是种植植物
        {
            this->planting(goods_inhand.goods_name);
            CCLOG("plant a crop");
        }
        else{
            CCLOG("water crop should take can in hand");
        }
    }
}

//浇水
void crop::water()
{
    if(watered_today)//如果今天还有浇水次数
    {
        watered_today -= 1;
    }
}

//种植
void crop::planting(std::string name) {
    if (CROP_MAP.at(name).at("season") == SEASON) {
        crop_name = name;
        develop_level = 1;
        develop_day = 1; /************************************************/
        std::string framename = this->crop_name + "-" + std::to_string(this->develop_level) + ".png";
        this->setSpriteFrame(framename);
        this->setScale(6.0f);  // 将精灵放大 4 倍

        //背包里种子-1
        CCLOG("plant successfully");
    }
    else
        CCLOG("the crop couldn't plant in this season");
}

//施肥
void crop::fertilize()
{
    develop_level += 1;
    std::string framename = this->crop_name + "-" + std::to_string(this->develop_level) + ".png";
    this->setSpriteFrame(framename);
    //背包里肥料-1
}

//丰收
void crop::harvest()
{
    //把生成物加入背包 
    this->clear();

}

//清除
void crop::clear()
{
    water_count = 0;
    unwater_count = 0;
    develop_day = 0;
    develop_level = 0;
    crop_name = "";
    watered_today = 1 + IS_DRY_DAY;
    this->initWithTexture(transparent_texture);
}

//更新
void crop::update_day()
{
    if (TODAY != now_day)//今天结束了
    {
        if (develop_level > 0) {
            if (watered_today)//说明今天浇水次数没有达到要求
            {
                unwater_count++;
                if (unwater_count == DIE_DRY) {
                    develop_level = -1;
                    this->setSpriteFrame("-1.png");
                    
                }
            }
            else//今天浇水达到要求
            {
                water_count++;
                //查看是否需要更新成长状态
                if (water_count > develop_level * develop_day && water_count <= MAX_LEVEL * develop_day) {
                    this->develop_level++;
                    //更新显示的成长状态
                    std::string framename = this->crop_name + "-" + std::to_string(this->develop_level) + ".png";
                    this->setSpriteFrame(framename);
                }
            }
        }
        now_day = TODAY;
        watered_today = 1 + IS_DRY_DAY;

    }
}
