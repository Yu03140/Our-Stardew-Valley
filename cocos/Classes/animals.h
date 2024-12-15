#ifndef __ANIMALS_H__
#define __ANIMALS_H__

///////////////////////////////////////////////////////////////////Ҫ��Ӷ���͸���Ʒ
#include "cocos2d.h"
#define TOOL "Pick"
#define FOOD "straw"
#define SPEED 10.0f
#define TODAY 0 //ȫ�ֱ�����ʱ���л�ȡ

class animals : public cocos2d::Sprite
{
private:
    static Sprite produce;
    int now_day = 0;                             //��ǰ����
    static std::string animals_name;                //���������
    static int produce_day;                      //ÿ�����ɸ���Ʒ����Ҫ������
    bool is_produce = 0;                        //�Ƿ����ɸ���Ʒ

    int feed_count = 0;                         //ι��������
    int feed_today = 1;                       //����ʣ��ι������
    int produce_count = 0;

    static cocos2d::Texture2D* transparent_texture;
    static cocos2d::Size produce_size;
    static cocos2d::Vec2 produce_pos;

public:
    // ����ʵ��
    static  animals* create(const std::string& plist_name, std::string name, cocos2d::Vec2 loc, cocos2d::Size size);

    // ��ʼ����������
    void init_mouselistener();

    // ��갴��ʱ�Ļص�
    void on_mouse_click(cocos2d::Event* event);

    //�ε�
    void updateDirection(const cocos2d::Vec2& movementDirection);
    void scheduleRandomMove(cocos2d::TMXTiledMap* tileMap);
    void randmove(cocos2d::TMXTiledMap* tileMap);

    //ιʳ
    void feed();

    //���ɸ���Ʒ
    void create_produce();

    //�ջ���
    void harvest();

    //��һ��ĸ���
    void update_day();
};

#endif __ANIMALS_H__

