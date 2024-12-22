#include "Fish.h"
#define MAG_TIME_CROP 1.5f
// 定义静态成员变量并初始化
//cocos2d::Texture2D* crop::transparent_texture = nullptr;
//cocos2d::Size crop::crop_size = cocos2d::Size(0, 0);

Fish* Fish::create(const std::string& spriteName) {
    Fish* fish = new Fish();
    if (fish && fish->initWithFile(spriteName)) {
        fish->autorelease();
        CCLOG("Fishhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh created successfully.");

        return fish;
    }
    CCLOG("DELETEDELETEDELETEDELETEDELETEDELETEDELETEDELETEDELETEDELETEDELETEDELETEDELETEDELETEDELETEDELETE.");

    CC_SAFE_DELETE(fish);
    return nullptr;
}

//// 设置 barrier 的位置和尺寸
//void Fish::setBarrierProperties(cocos2d::Vec2 pos, float width, float height) {
//    barrierPos = pos;
//    barrierWidth = width;
//    barrierHeight = height;
//}
//moveable_sprite_key_walk* sprite_move = nullptr;

//void Fish::finishFishing(cocos2d::Layer* parentLayer) {
//    // 检查主角是否存在
//    if (!sprite_move) {
//        CCLOG("Player is null. Cannot create fish sprite.");
//        return;
//    }
//
//    // 获取主角位置
//    cocos2d::Vec2 playerPosition = sprite_move->getPosition();
//
//    // 创建鱼精灵
//    auto fishSprite = cocos2d::Sprite::create("fish.png");
//    if (fishSprite) {
//        // 设置精灵位置为主角位置
//        fishSprite->setPosition(playerPosition);
//
//        // 添加精灵到层中
//        parentLayer->addChild(fishSprite);
//
//        // 播放动画效果
//        auto scaleUp = cocos2d::ScaleTo::create(0.3f, 1.5f);
//        auto scaleDown = cocos2d::ScaleTo::create(0.3f, 1.0f);
//        auto sequence = cocos2d::Sequence::create(scaleUp, scaleDown, nullptr);
//        fishSprite->runAction(sequence);
//
//        CCLOG("Fish sprite created at position: (%f, %f)", playerPosition.x, playerPosition.y);
//    }
//    else {
//        CCLOG("Failed to create fish sprite.");
//    }





//
//// 初始化鼠标监听器
//void Fish::init_mouselistener()
//{
//    // 创建鼠标监听器
//    auto listener = cocos2d::EventListenerMouse::create();
//
//    // 鼠标按下时的回调
//    listener->onMouseDown = CC_CALLBACK_1(Fish::on_mouse_click, this);
//    // 获取事件分发器，添加监听器
//    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
//}
// 鼠标按下时的回调
//void Fish::on_mouse_click(cocos2d::Event* event)
//{
//
//    //获取鼠标在窗口中的位置,转换到地图坐标
//    auto mouse_event = dynamic_cast<cocos2d::EventMouse*>(event);
//    Vec2 mousePosition = mouse_event->getLocationInView();
//    auto camera = Director::getInstance()->getRunningScene()->getDefaultCamera();
//    auto visibleSize = Director::getInstance()->getVisibleSize();
//    Vec2 windowOrigin = camera->getPosition() - Vec2(visibleSize.width / 2, visibleSize.height / 2);
//    Vec2 mouse_pos = mousePosition + windowOrigin;
//    MOUSE_POS = mouse_pos;
//    CCLOG("Mouse Position(global): (%f, %f)", MOUSE_POS.x, MOUSE_POS.y);
//
//    checkForPoolClick(mouse_pos);
//
//
//    // 0.1秒后将 MOUSE_POS 置为 (0, 0)，并且不影响其他程序运行
//    this->scheduleOnce([this](float dt) {
//        MOUSE_POS = Vec2::ZERO;
//        CCLOG("Mouse Position reset to: (%f, %f)", MOUSE_POS.x, MOUSE_POS.y);
//        }, 1.5f, "reset_mouse_pos_key");
//
//    
//}
//
void Fish::carry_fishing(Vec2 mousePosition)
{
    if (!this) {
        CCLOG("Fish object is nullptr. Cannot proceed.");
        return;
    }
    CCLOG("Mouse Positioncarry_fishingcarry_fishingcarry_fishingcarry_fishingcarry_fishingcarry_fishingcarry_fishingcarry_fishing: (%f, %f)", mousePosition.x, mousePosition.y);

    // 执行工具检查和操作
    if (backpackLayer->getSelectedItem().find("Can1") != std::string::npos) {
        CCLOG("Waterrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr");
        this->takewater(backpackLayer->getSelectedItem());
    }
    else if (backpackLayer->getSelectedItem().find("Rod1") != std::string::npos) {
        CCLOG("Fishingggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg");
        Sprite* fish_sprite = Sprite::create("bluefish.png");
        fish_sprite->setPosition(mousePosition);  // 设置鱼的位置为点击位置
        this->addChild(fish_sprite);

        this->fishing(backpackLayer->getSelectedItem());
    }
    else {
        CCLOG("Couldn't do anything to the pool");
    }


}

//接水
void Fish::takewater(std::string name)
{
        char last_char = name[name.size() - 1];
        int level = last_char - '0';
     //   watered_today = std::min(watered_today - level, 0);
        this->setSpriteFrame("water.png");

 //  // 在 0.2 秒后恢复原图
 //  this->scheduleOnce([this](float dt) {
 //      this->setSpriteFrame(crop_name + "-" + std::to_string(this->develop_level) + ".png");
 //      }, 0.2f, "reset_texture_crop");

        //背包水+1
        backpackLayer->addItem(name);
        CCLOG("take water successfully");
}

//钓鱼
void Fish::fishing(std::string name) {



    fish_name = name;
//  develop_level = 1;
//  develop_day = CROP_MAP.at(name).at("develop_day");
    std::string framename = "load1.png";//显示鱼图片，表示钓鱼成功
    this->setSpriteFrame(framename);
    this->setScale(MAG_TIME_CROP);

    //背包里鱼+1
    CCLOG("fish successfully");
}


//丰收，每次收获增加EXPERIENCE经验值
void Fish::harvest()
{
// CCLOG("%s", HARVEST_MAP.at(crop_name));
// backpackLayer->addItem(name);
// //人物经验增加10
// Player* player = Player::getInstance("me");
// player->playerproperty.addExperience(EXPERIENCE);

}


