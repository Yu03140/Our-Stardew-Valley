#ifndef __CROP_H__
#define __CROP_H__

#include "cocos2d.h"
#include "Global/Global.h"

#define MAX_LEVEL 5
#define DIE_DRY 4
#define WATER_PRED 3
#define EXPERIENCE 10
struct GOODS_INHAND {
    std::string goods_name;
};

//作物种植相关信息
const std::unordered_map<std::string, std::unordered_map<std::string, int>> CROP_MAP =
{
    {"strawberry",{{"develop_day",5},{"season",SPRING}}},
    {"sunflour",{{"develop_day",4},{"season",SUMMER}}},
    {"pumpkin",{{"develop_day",5},{"season",AUTUMN}}}
};
//作物成熟后得到的生成品
const std::unordered_map<std::string, std::string> HARVEST_MAP =
{
    {"strawberry","strawberry_fruit"},
    {"sunflour","sunflour_fruit"},
    {"pumpkin","sunflour_fruit"}
};

class crop : public cocos2d::Sprite
{
private:
    int ID;
    int now_day = 0;                             //当前日期
    std::string crop_name;                //作物的名称
    int develop_day;                      //每成长一阶段所需要的天数

    int water_count = 0;                         //浇水总天数
    int unwater_count = 0;                       //没有浇水的连续天数
    int develop_level = 0;                       //目前生长阶段
    int watered_today = WATER_PRED;                       //今天剩余浇水次数

    static cocos2d::Texture2D* transparent_texture;
    static cocos2d::Size crop_size;
public:
    // 创建实例
    static crop* create(const std::string& plist_name, float width, float height);

    // 初始化鼠标监听器
    void init_mouselistener();

    // 鼠标按下时的回调
    void on_mouse_click(cocos2d::Event* event);

    //种植功能
    void planting(std::string name);

    //浇水功能的实现
    void water(std::string name);

    //施肥功能
    void fertilize(std::string name);

    //清除
    void clear();

    //收获功能
    void harvest();

    //新一天的更新
    void update_day(float deltaTime);

    //除虫
    void deinsectization();

    void set_ID(int i) { ID = i; }
};
#endif __CROP_H__
