#ifndef __ANIMALS_H__
#define __ANIMALS_H__

#include "cocos2d.h"
#include "Global/Global.h"

#define FOOD "straw"
#define SPEED 10.0f
#define EXPERIENCE 10
#define EDGE1 120
#define EDGE0 10

const std::unordered_map<std::string, int> ANIMAL_MAP = { {"Pig",5},{"Goat",5},{"Chicken",1} ,{"Cow",7} };                                                  //����ĳɳ�ͼ��
const std::unordered_map<std::string, std::string> PRODUCE_MAP = { {"Pig","truffle"},{"Goat","goat_wool"},{"Chicken","chicken_egg"} ,{"Cow","cow_milk"} };  //����������

class animals : public cocos2d::Sprite
{
private:

    Sprite* produce;
    int now_day = 0;                                                        //��ǰ����
    std::string animals_name;                                               //���������
    int produce_day;                                                        //ÿ�����ɸ���Ʒ����Ҫ������
    bool is_produce = 0;                                                    //�Ƿ����ɸ���Ʒ
    int feed_count = 0;                                                     //ι��������
    int feed_today = 1;                                                     //����ʣ��ι������
	static cocos2d::Texture2D* transparent_texture;
    cocos2d::Size produce_size;
    cocos2d::Vec2 produce_pos;
    static int count;
    int ID;
	float move_vecx[4] = { 0,0,-SPEED * 0.1f,SPEED * 0.1f };                //�ƶ�����
	float move_vecy[4] = { SPEED * 0.1f,-SPEED * 0.1f ,0,0 };               //�ƶ�����
    bool movement[4] = { false, false, false, false };
	bool is_hit_edge[4] = { false,false, false, false };                    //�Ƿ������߽�
    int dic;
public:

    animals();
    void set_info(std::string name, cocos2d::Vec2 pos, cocos2d::Size size); //���������Ϣ 
    static animals* create(const std::string& plist_name);
    void set_imag();
    void init_mouselistener();                                              // ��ʼ����������
    void on_mouse_click(cocos2d::Event* event);                             // ��갴��ʱ�Ļص�
    void randmove(cocos2d::TMXTiledMap* tileMap);                           // �ε�
    void move_act(cocos2d::TMXTiledMap* tileMap);
    void scheduleRandomMove(cocos2d::TMXTiledMap* tileMap);
    void feed();                                                            // ιʳ
    void create_produce();                                                  // ���ɸ���Ʒ
    void harvest();                                                         // �ջ���
    void update_day(float deltaTime);                                       // ��һ��ĸ���
};

class AnimalsManager :public Node
{
private:
    std::vector<animals*> animals_list;
public:
    static AnimalsManager* create();
    void add_animals(animals* sprite);                                      // ��Ӿ��鵽����
    void schedule_animals();                                                // �������������ʾ���
};



#endif __ANIMALS_H__