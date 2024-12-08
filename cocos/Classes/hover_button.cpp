#include "hover_button.h"


// ����ʵ��
hover_button* hover_button::create(const std::string& plist_name, const std::string& sprite_framename)
{
    // ���ؾ���֡
    cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plist_name);

    // ����ʵ��
    hover_button* button = new hover_button();

    // ��ȡ��ͨ����ͣ״̬�µľ���֡
    button->default_sprite = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(sprite_framename + "-default.png");
    button->hover_sprite = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(sprite_framename + "-hover.png");
    button->click_sprite = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(sprite_framename + "-clicked.png");

    // �ж��Ƿ�ɹ���ȡ����֡
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

// ��ʼ����������
void hover_button::init_mouselistener()
{
    // ������������
    auto listener = cocos2d::EventListenerMouse::create();

    // �����ͣʱ�Ļص�
    listener->onMouseMove = CC_CALLBACK_1(hover_button::on_mouse_move, this);

    // ��갴��ʱ�Ļص�
    listener->onMouseDown = CC_CALLBACK_1(hover_button::on_mouse_click, this);

    // ��ȡ�¼��ַ�������Ӽ�����
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

// �����ͣʱ�Ļص�
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
        // �����ͣ�ڰ�ť�ϣ��л�����ͣ״̬
        this->setSpriteFrame(hover_sprite);
        CCLOG("Mouse hover in button!");
    }
    else
    {
        // ����ƿ���ť���ָ���ͨ״̬
        this->setSpriteFrame(default_sprite);
    }
}

// ��갴��ʱ�Ļص�
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
        // ������ڰ�ť�����ڣ�ִ�ж�Ӧ����
        CCLOG("Button clicked button!");
        button_func();
    }
}

//��ť������
void hover_button::button_func()
{
    this->setSpriteFrame(click_sprite);
}

