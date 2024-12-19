#ifndef _HOVER_BUTTON_H_
#define _HOVER_BUTTON_H_

#include "cocos2d.h"

class hover_button : public cocos2d::Sprite
{
public:
    virtual ~hover_button() { ; }

    // 创建实例
    static hover_button* create(const std::string& plist_name, const std::string& sprite_framename);

    // 初始化鼠标监听器
    void init_mouselistener();

    // 鼠标悬停时的回调
    void on_mouse_move(cocos2d::Event* event);

    // 鼠标按下时的回调
    void on_mouse_click(cocos2d::Event* event);

    //按钮的作用
    virtual void button_func();

private:
    // 三种状态下的精灵帧
    cocos2d::SpriteFrame* default_sprite;
    cocos2d::SpriteFrame* hover_sprite;
    cocos2d::SpriteFrame* click_sprite;
};

#endif _HOVER_BUTTON_H_
