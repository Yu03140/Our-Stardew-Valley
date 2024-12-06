#ifndef __MOVEABLE_SPRITE_KEY_H__
#define __MOVEABLE_SPRITE_KEY_H__

#include "cocos2d.h"

class moveable_sprite_key : public cocos2d::Sprite
{
private:
    const float speed = 30.0f;//移动速度
    //数组各位置分别表示上、下、左、右方位
    float move_vecx[4] = { 0,0,-speed * 0.1f,speed * 0.1f };
    float move_vecy[4] = { speed * 0.1f,-speed * 0.1f ,0,0 };
    bool movement[4] = { false, false, false, false };
    bool isAnimating = false;
    static std::string name;

public:
    //创建一个moveable_sprite_key的实例
    static moveable_sprite_key* create(const std::string& plist_name, const std::string& sprite_framename);

    //键盘监听器
    void init_keyboardlistener();

    //按下键盘时，将对应方向参数修改为true
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    //松开键盘后，将对应方向参数修改会false
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    //更新位置
    void update(float deltaTime);

    //生成移动指令
    void move_act(int direction);

};

#endif __MOVEABLE_SPRITE_KEY_H__
