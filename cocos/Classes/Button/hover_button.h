#ifndef __HOVER_BUTTON_H__
#define __HOVER_BUTTON_H__

#include "cocos2d.h"

USING_NS_CC;

class hover_button : public Sprite
{
public:
    virtual ~hover_button() { ; }

    // 创建按钮实例
    static hover_button* create(const std::string& plist_name, const std::string& sprite_framename);

    // 初始化鼠标监听器
    void init_mouselistener();

    // 鼠标悬停时的回调
    void on_mouse_move(cocos2d::Event* event);

    // 鼠标点击时的回调
    void on_mouse_click(cocos2d::Event* event);

    // 按钮点击后的处理函数
    //void button_func();

    // 设置按钮的点击回调(new)
    void setButtonFunc(const std::function<void()>& func);


private:
    // 三种状态下的精灵帧
    SpriteFrame* default_sprite;  // 普通状态下的精灵帧
    SpriteFrame* hover_sprite;    // 悬停状态下的精灵帧
    SpriteFrame* click_sprite;    // 点击状态下的精灵帧

    // 物品精灵（与按钮关联）(new)
    Sprite* associatedItem;

    // 用于存储点击回调函数
    std::function<void()> button_func;  

 

};

#endif // __HOVER_BUTTON_H__
