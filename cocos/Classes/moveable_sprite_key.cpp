/****************************************************************************
精灵特点：按下键盘方向键，按照方向移动并执行移动动画，当到达边界时不移动
使用方式：
    auto sprite_move = moveable_sprite_key::create("name.plist","name");
    if (sprite_move)
    {
        // 设置初始位置
        sprite_move->setPosition());
        // 将精灵添加到场景中
        this->addChild(sprite_move);
        // 初始化键盘监听器
        sprite_move->init_keyboardlistener();
        // 定时调用 update 更新精灵的位置
        sprite_move->schedule([sprite_move](float dt) {
            sprite_move->update(dt);
            }, "update_key");
    }
使用要求：plist文件中上下左右移动的后缀分别为{"-back","-front","-left","-right"}，并且每个方向有四个走路的动画，后缀为{"1","2","3","4"}
 ****************************************************************************/
#include "moveable_sprite_key.h"

// 静态成员变量定义
std::string moveable_sprite_key::name = "";  // 静态成员变量的初始化

//创建一个moveable_sprite_key的实例
moveable_sprite_key* moveable_sprite_key::create(const std::string& plist_name, const std::string& sprite_framename)
{
    //加载plist文件
    cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plist_name);

    //同步精灵的图集名称
    name = sprite_framename;

    //创建实例
    std::string default_framename =name + "-front1.png";
    moveable_sprite_key* sprite = new moveable_sprite_key();

    // 获取指定精灵帧
    cocos2d::SpriteFrame* frame = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(default_framename);
    
    //判断是否能成功创建
    if (frame)
    {
        sprite->initWithSpriteFrame(frame);
        sprite->autorelease();
        sprite->setScale(4.0f);  // 将精灵放大 4 倍
        sprite->init_keyboardlistener();
        CCLOG("Creation moveable_sprite_key successfully!");
        return sprite;
    }
    CCLOG("Creation moveable_sprite_key unsuccessfully!");
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

//键盘监听器
void moveable_sprite_key::init_keyboardlistener()
{
    // 创建键盘监听器
    auto listener = cocos2d::EventListenerKeyboard::create();

    // 按键按下时的回调
    listener->onKeyPressed = CC_CALLBACK_2(moveable_sprite_key::onKeyPressed, this);

    // 按键释放时的回调
    listener->onKeyReleased = CC_CALLBACK_2(moveable_sprite_key::onKeyReleased, this);

    // 获取事件分发器，添加监听器
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

}

//按下键盘时，将对应方向参数修改为true
void moveable_sprite_key::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW)
    {
        movement[0] = true; // 上
    }
    else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW)
    {
        movement[1] = true; // 下
    }
    else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW)
    {
        movement[2] = true; // 左
    }
    else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
    {
        movement[3] = true; // 右
    }
}

//松开键盘后，将对应方向参数修改会false
void moveable_sprite_key::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    std::string default_framename = name + "-front1.png";
    if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW)
    {
        movement[0] = false;
    }
    else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW)
    {
        movement[1] = false;
    }
    else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW)
    {
        movement[2] = false;
    }
    else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
    {
        movement[3] = false;
    }

    // 松开键盘时，恢复初始动作，停止所有动作
    this->setSpriteFrame(default_framename);
    this->stopAllActions();
    isAnimating = false;  // 标记动画停止

}

//更新位置
void moveable_sprite_key::update(float deltaTime)
{
    //保存是否到达边界的判断结果,分别为上下左右
    bool is_hit_edge[4] = { false,false, false, false };

    //获取精灵的位置
    cocos2d::Vec2 sprite_pos = this->getPosition();

    //获取窗口的大小信息
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

    // 判断精灵是否超出边界
   if (sprite_pos.y + this->getContentSize().height / 2 >= origin.y + visibleSize.height) {
       is_hit_edge[0] = true;
       CCLOG("Sprite hit the top edge");
    }
    else  if (sprite_pos.y - this->getContentSize().height / 2 <= origin.y) {
       is_hit_edge[1] = true;
       CCLOG("Sprite hit the bottom edge");
    }
    if (sprite_pos.x - this->getContentSize().width / 2 <= origin.x) {
        is_hit_edge[2] = true;
        CCLOG("Sprite hit the left edge");
    }
    else if (sprite_pos.x + this->getContentSize().width / 2 >= origin.x + visibleSize.width) {
        is_hit_edge[3] = true;
        CCLOG("Sprite hit the right edge");
    }


    for (int i = 0; i < 4; i++) {
        if (movement[i] && !is_hit_edge[i])
            move_act(i);
    }
}

//生成移动指令
void moveable_sprite_key::move_act(int direction)
{
    //各方向对应图片后缀
    std::string dic[4] = { "-back","-front","-left","-right" };

    //创建移动动作
    auto move_action = cocos2d::MoveBy::create(0.1f, cocos2d::Vec2( move_vecx[direction], move_vecy[direction]));
    //创建动画
    cocos2d::Vector<cocos2d::SpriteFrame*> frames;
    frames.pushBack(cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(name + dic[direction] + "1.png"));
    frames.pushBack(cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(name + dic[direction] + "2.png"));
    frames.pushBack(cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(name + dic[direction] + "3.png"));
    frames.pushBack(cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(name + dic[direction] + "4.png"));
    // 创建动画对象
    auto animation = cocos2d::Animation::createWithSpriteFrames(frames, 0.1f); // 每帧间隔 0.1s
    auto animate = cocos2d::Animate::create(animation);
    auto repeat = cocos2d::RepeatForever::create(animate);

    this->runAction(move_action);
    // 如果还没有在播放动画，才开始播放
    if (!isAnimating) {
        // 执行移动和动画
        this->runAction(repeat);
        isAnimating = true;  // 标记动画正在播放
    }
}
