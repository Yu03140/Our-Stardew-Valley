#ifndef __HOVER_BUTTON_H__
#define __HOVER_BUTTON_H__

#include "cocos2d.h"

USING_NS_CC;

class hover_button : public Sprite
{
public:
    virtual ~hover_button() { ; }

    // ������ťʵ��
    static hover_button* create(const std::string& plist_name, const std::string& sprite_framename);

    // ��ʼ����������
    void init_mouselistener();

    // �����ͣʱ�Ļص�
    void on_mouse_move(cocos2d::Event* event);

    // �����ʱ�Ļص�
    void on_mouse_click(cocos2d::Event* event);

    // ��ť�����Ĵ�����
    //void button_func();

    // ���ð�ť�ĵ���ص�(new)
    void setButtonFunc(const std::function<void()>& func);


private:
    // ����״̬�µľ���֡
    SpriteFrame* default_sprite;  // ��ͨ״̬�µľ���֡
    SpriteFrame* hover_sprite;    // ��ͣ״̬�µľ���֡
    SpriteFrame* click_sprite;    // ���״̬�µľ���֡

    // ��Ʒ���飨�밴ť������(new)
    Sprite* associatedItem;

    // ���ڴ洢����ص�����
    std::function<void()> button_func;  

 

};

#endif // __HOVER_BUTTON_H__
