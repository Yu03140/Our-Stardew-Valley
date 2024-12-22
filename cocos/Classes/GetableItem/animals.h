//auto animal = animals::create("Animals.plist""Pig", Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y),Size(100,100));
//if (animal)
//{
//    animal->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
//    this->addChild(animal, 1);
//    animal->init_mouselistener();
//    animal->scheduleRandomMove(tileMap);
//    animal->schedule([animal](float dt) {
//        animal->update(dt);
//        }, "update_animal");
//}



#ifndef __ANIMALS_H__
#define __ANIMALS_H__

#include "cocos2d.h"
#include "Global/Global.h"

#define FOOD "straw"
#define SPEED 20.0f
#define EXPERIENCE 10
#define EDGE1 120
#define EDGE0 10
//����ĳɳ�ͼ��
const std::unordered_map<std::string, int> ANIMAL_MAP = { {"Pig",5},{"Goat",5},{"Chicken",4} ,{"Cow",7} };
//����������
const std::unordered_map<std::string, std::string> PRODUCE_MAP = { {"Pig","truffle"},{"Goat","goat_wool"},{"Chicken","chicken_egg"} ,{"Cow","cow_milk"} };


class animals : public cocos2d::Sprite
{
private:
    Sprite* produce;
    int now_day = 0;                             //��ǰ����
    std::string animals_name;                //���������
    int produce_day;                      //ÿ�����ɸ���Ʒ����Ҫ������
    bool is_produce = 0;                         //�Ƿ����ɸ���Ʒ

    int feed_count = 0;                         //ι��������
    int feed_today = 1;                         //����ʣ��ι������

    static cocos2d::Texture2D* transparent_texture;
    cocos2d::Size produce_size;
    cocos2d::Vec2 produce_pos;
    static int count;
    int ID;
    //�����λ�÷ֱ��ʾ�ϡ��¡����ҷ�λ
    float move_vecx[4] = { 0,0,-SPEED * 0.1f,SPEED * 0.1f };
    float move_vecy[4] = { SPEED * 0.1f,-SPEED * 0.1f ,0,0 };
    bool movement[4] = { false, false, false, false };
    //�����Ƿ񵽴�߽���жϽ��,�ֱ�Ϊ��������
    bool is_hit_edge[4] = { false,false, false, false };
    int dic;
public:
    animals();
    //���������Ϣ
    void set_info(std::string name, cocos2d::Vec2 pos, cocos2d::Size size);
    // ����ʵ��
    static animals* create(const std::string& plist_name);
    void set_imag();

    // ��ʼ����������
    void init_mouselistener();

    // ��갴��ʱ�Ļص�
    void on_mouse_click(cocos2d::Event* event);

    //�ε�
    void randmove(cocos2d::TMXTiledMap* tileMap);
    void move_act(cocos2d::TMXTiledMap* tileMap);
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

/*-------------------------------------------------------------------renew ------------------------------------------------------------------------*/
/*-------------------------------------------------------------------AnimalsManager ------------------------------------------------------------------------*/
class AnimalsManager :public Node
{
private:
    std::vector<animals*> animals_list;
public:
    static AnimalsManager* create();
    // ��Ӿ��鵽����
    void add_animals(animals* sprite);

    // �������������ʾ���
    void schedule_animals();

};



#endif __ANIMALS_H__

