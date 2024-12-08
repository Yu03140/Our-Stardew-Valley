#include "hover_button.h"


// 创建实例
hover_button* hover_button::create(const std::string& plist_name, const std::string& sprite_framename)
{
    // 加载精灵帧
    cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plist_name);

    // 创建实例
    hover_button* button = new hover_button();

    // 获取普通、悬停状态下的精灵帧
    button->default_sprite = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(sprite_framename + "-default.png");
    button->hover_sprite = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(sprite_framename + "-hover.png");
    button->click_sprite = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(sprite_framename + "-clicked.png");

    // 判断是否成功获取精灵帧
    if (button->default_sprite && button->hover_sprite)
    {
        button->initWithSpriteFrame(button->default_sprite);
        button->autorelease();
        button->init_mouselistener();
        CCLOG("Creation hover_button successfully!");
        return button;
    }

    CCLOG("Creation hover_button unsuccessfully!");
    CC_SAFE_DELETE(button);
    return nullptr;
}

// 初始化鼠标监听器
void hover_button::init_mouselistener()
{
    // 创建鼠标监听器
    auto listener = cocos2d::EventListenerMouse::create();

    // 鼠标悬停时的回调
    listener->onMouseMove = CC_CALLBACK_1(hover_button::on_mouse_move, this);

    // 鼠标按下时的回调
    listener->onMouseDown = CC_CALLBACK_1(hover_button::on_mouse_click, this);

    // 获取事件分发器，添加监听器
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

// 鼠标悬停时的回调
void hover_button::on_mouse_move(cocos2d::Event* event)
{
    auto mouse_event = dynamic_cast<cocos2d::EventMouse*>(event);
    auto mouse_pos = this->getParent()->convertToNodeSpace(mouse_event->getLocationInView());
    auto button_pos = this->getPosition();
    auto button_size = this->getContentSize();

    if (mouse_pos.x > button_pos.x - button_size.width / 2 &&
        mouse_pos.x < button_pos.x + button_size.width / 2 &&
        mouse_pos.y > button_pos.y - button_size.height / 2 &&
        mouse_pos.y < button_pos.y + button_size.height / 2)
    {
        // 鼠标悬停在按钮上，切换到悬停状态
        this->setSpriteFrame(hover_sprite);
        CCLOG("Mouse hover in button!");
    }
    else
    {
        // 鼠标移开按钮，恢复普通状态
        this->setSpriteFrame(default_sprite);
    }
}

// 鼠标按下时的回调
void hover_button::on_mouse_click(cocos2d::Event* event)
{
    auto mouse_event = dynamic_cast<cocos2d::EventMouse*>(event);
    auto mouse_pos = this->getParent()->convertToNodeSpace(mouse_event->getLocationInView());
    auto button_pos = this->getPosition();
    auto button_size = this->getContentSize();
    
    if (mouse_pos.x > button_pos.x - button_size.width / 2 &&
        mouse_pos.x < button_pos.x + button_size.width / 2 &&
        mouse_pos.y > button_pos.y - button_size.height / 2 &&
        mouse_pos.y < button_pos.y + button_size.height / 2)
    {
        // 鼠标点击在按钮区域内，执行对应功能
        CCLOG("Button clicked button!");
        button_func();
    }
}

//按钮的作用
void hover_button::button_func()
{
    this->setSpriteFrame(click_sprite);
}

