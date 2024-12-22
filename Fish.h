#ifndef __FISH_H__
#define __FISH_H__

#include "cocos2d.h"
#include "Global/Global.h"

#define MAX_LEVEL 5
#define DIE_DRY 4
#define WATER_PRED 3
#define EXPERIENCE 10

//作物种植相关信息
const std::unordered_map<std::string, std::unordered_map<std::string, int>> FISH_MAP =
{
    {"bluefish",{{"develop_day",5},{"season",SPRING}}},
    {"bluefish",{{"develop_day",4},{"season",SUMMER}}},
    {"bluefish",{{"develop_day",5},{"season",AUTUMN}}}
};
//作物成熟后得到的生成品
const std::unordered_map<std::string, std::string> HARVEST_FISH_MAP =
{
    {"bluefish","bluefish"},
    {"bluefish","bluefish"},
    {"bluefish","bluefish"}
};

class fish : public cocos2d::Sprite
{
private:
    int ID;
    int now_day = 0;                             //当前日期
    std::string fish_name= "bluefish";                //作物的名称
    int develop_day;                      //每成长一阶段所需要的天数

    int water_count = 0;                         //浇水总天数
    int unwater_count = 0;                       //没有浇水的连续天数
    int develop_level = 0;                       //目前生长阶段
    int watered_today = WATER_PRED;                       //今天剩余浇水次数

    static cocos2d::Texture2D* transparent_texture;
    static cocos2d::Size fish_size;
public:
    // 创建实例
    static fish* create(const std::string& plist_name, float width, float height);

    // 初始化鼠标监听器
    void init_mouselistener();

    // 鼠标按下时的回调
    void on_mouse_click(cocos2d::Event* event);

    //浇水功能的实现
    void water(std::string name);

    //钓鱼
    void fishing(std::string name);

    //清除
    void clear();


};
#endif __FISH_H__
