#ifndef __ANIMALS_H__
#define __ANIMALS_H__

///////////////////////////////////////////////////////////////////要添加动物和附属品
#include "cocos2d.h"
#define TOOL "Pick"
#define FOOD "straw"
#define SPEED 10.0f
#define TODAY 0 //全局变量的时间中获取

class animals : public cocos2d::Sprite
{
private:
    static Sprite produce;
    int now_day = 0;                             //当前日期
    static std::string animals_name;                //动物的名称
    static int produce_day;                      //每次生成附属品所需要的天数
    bool is_produce = 0;                        //是否生成附属品

    int feed_count = 0;                         //喂养总天数
    int feed_today = 1;                       //今天剩余喂养次数
    int produce_count = 0;

    static cocos2d::Texture2D* transparent_texture;
    static cocos2d::Size produce_size;
    static cocos2d::Vec2 produce_pos;

public:
    // 创建实例
    static  animals* create(const std::string& plist_name, std::string name, cocos2d::Vec2 loc, cocos2d::Size size);

    // 初始化鼠标监听器
    void init_mouselistener();

    // 鼠标按下时的回调
    void on_mouse_click(cocos2d::Event* event);

    //游荡
    void updateDirection(const cocos2d::Vec2& movementDirection);
    void scheduleRandomMove(cocos2d::TMXTiledMap* tileMap);
    void randmove(cocos2d::TMXTiledMap* tileMap);

    //喂食
    void feed();

    //生成附属品
    void create_produce();

    //收获功能
    void harvest();

    //新一天的更新
    void update_day();
};

#endif __ANIMALS_H__

