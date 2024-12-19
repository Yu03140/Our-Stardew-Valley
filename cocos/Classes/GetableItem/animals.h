#ifndef __ANIMALS_H__
#define __ANIMALS_H__

#include "cocos2d.h"
#include "Global/Global.h"

#define FOOD "straw"
#define SPEED 0.5f
#define EXPERIENCE 10
//动物的成长图鉴
const std::unordered_map<std::string, int> ANIMAL_MAP = { {"Pig",5},{"Goat",5},{"Chicken",4} ,{"Cow",7} };
//动物生成物
const std::unordered_map<std::string, std::string> PRODUCE_MAP = { {"Pig","truffle"},{"Goat","goat_wool"},{"Chicken","chicken_egg"} ,{"Cow","cow_milk"} };


class animals : public cocos2d::Sprite
{
private:
    static Sprite produce;
    int now_day = 0;                             //当前日期
    static std::string animals_name;                //动物的名称
    static int produce_day;                      //每次生成附属品所需要的天数
    bool is_produce = 0;                         //是否生成附属品

    int feed_count = 0;                         //喂养总天数
    int feed_today = 1;                         //今天剩余喂养次数

    static cocos2d::Texture2D* transparent_texture;
    static cocos2d::Size produce_size;
    static cocos2d::Vec2 produce_pos;

public:
    // 创建实例
    static animals* create(const std::string& plist_name, std::string name, cocos2d::Vec2 pos, cocos2d::Size size);

    // 初始化鼠标监听器
    void init_mouselistener();

    // 鼠标按下时的回调
    void on_mouse_click(cocos2d::Event* event);

    //游荡
    void updateDirection(const cocos2d::Vec2& movementDirection);
    void randmove(cocos2d::TMXTiledMap* tileMap);
    void scheduleRandomMove(cocos2d::TMXTiledMap* tileMap);

    //喂食
    void feed();

    //生成附属品
    void create_produce();

    //收获功能
    void harvest();

    //新一天的更新
    void update_day(float deltaTime);
};

#endif __ANIMALS_H__

