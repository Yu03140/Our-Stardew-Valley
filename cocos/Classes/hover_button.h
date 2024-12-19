#ifndef _HOVER_BUTTON_H_
#define _HOVER_BUTTON_H_

#include "cocos2d.h"

class hover_button : public cocos2d::Sprite
{
public:
    virtual ~hover_button() { ; }

    // ����ʵ��
    static hover_button* create(const std::string& plist_name, const std::string& sprite_framename);

    // ��ʼ����������
    void init_mouselistener();

    // �����ͣʱ�Ļص�
    void on_mouse_move(cocos2d::Event* event);

    // ��갴��ʱ�Ļص�
    void on_mouse_click(cocos2d::Event* event);

    //��ť������
    virtual void button_func();

private:
    // ����״̬�µľ���֡
    cocos2d::SpriteFrame* default_sprite;
    cocos2d::SpriteFrame* hover_sprite;
    cocos2d::SpriteFrame* click_sprite;
};

#endif _HOVER_BUTTON_H_
