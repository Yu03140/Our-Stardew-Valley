#ifndef __ANIMALS_H__
#define __ANIMALS_H__

#include "cocos2d.h"
#include "Global/Global.h"

#define FOOD "straw"
#define SPEED 0.5f
#define EXPERIENCE 10
//����ĳɳ�ͼ��
const std::unordered_map<std::string, int> ANIMAL_MAP = { {"Pig",5},{"Goat",5},{"Chicken",4} ,{"Cow",7} };
//����������
const std::unordered_map<std::string, std::string> PRODUCE_MAP = { {"Pig","truffle"},{"Goat","goat_wool"},{"Chicken","chicken_egg"} ,{"Cow","cow_milk"} };


class animals : public cocos2d::Sprite
{
private:
    static Sprite produce;
    int now_day = 0;                             //��ǰ����
    static std::string animals_name;                //���������
    static int produce_day;                      //ÿ�����ɸ���Ʒ����Ҫ������
    bool is_produce = 0;                         //�Ƿ����ɸ���Ʒ

    int feed_count = 0;                         //ι��������
    int feed_today = 1;                         //����ʣ��ι������

    static cocos2d::Texture2D* transparent_texture;
    static cocos2d::Size produce_size;
    static cocos2d::Vec2 produce_pos;

public:
    // ����ʵ��
    static animals* create(const std::string& plist_name, std::string name, cocos2d::Vec2 pos, cocos2d::Size size);

    // ��ʼ����������
    void init_mouselistener();

    // ��갴��ʱ�Ļص�
    void on_mouse_click(cocos2d::Event* event);

    //�ε�
    void updateDirection(const cocos2d::Vec2& movementDirection);
    void randmove(cocos2d::TMXTiledMap* tileMap);
    void scheduleRandomMove(cocos2d::TMXTiledMap* tileMap);

    //ιʳ
    void feed();

    //���ɸ���Ʒ
    void create_produce();

    //�ջ���
    void harvest();

    //��һ��ĸ���
    void update_day(float deltaTime);
};

#endif __ANIMALS_H__

