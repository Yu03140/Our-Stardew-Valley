#ifndef __MOVEABLE_SPRITE_KEY_H__
#define __MOVEABLE_SPRITE_KEY_H__

#include "cocos2d.h"

class moveable_sprite_key : public cocos2d::Sprite
{
private:
    const float speed = 30.0f;//�ƶ��ٶ�
    //�����λ�÷ֱ��ʾ�ϡ��¡����ҷ�λ
    float move_vecx[4] = { 0,0,-speed * 0.1f,speed * 0.1f };
    float move_vecy[4] = { speed * 0.1f,-speed * 0.1f ,0,0 };
    bool movement[4] = { false, false, false, false };
    bool isAnimating = false;
    static std::string name;

public:
    //����һ��moveable_sprite_key��ʵ��
    static moveable_sprite_key* create(const std::string& plist_name, const std::string& sprite_framename);

    //���̼�����
    void init_keyboardlistener();

    //���¼���ʱ������Ӧ��������޸�Ϊtrue
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    //�ɿ����̺󣬽���Ӧ��������޸Ļ�false
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    //����λ��
    void update(float deltaTime);

    //�����ƶ�ָ��
    void move_act(int direction);

};

#endif __MOVEABLE_SPRITE_KEY_H__
