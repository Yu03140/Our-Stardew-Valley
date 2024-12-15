#ifndef __CROP_H__
#define __CROP_H__

#include "cocos2d.h"
#include "global_properties.h"

#define DIE_DRY 3
#define MAX_LEVEL 5
#define SEASON 1
#define SPRING 1
#define SUMMER 2
#define AUTUMN 3
#define WINTER 4
#define IS_DRY_DAY 0

const std::map<std::string, std::map<std::string,int>> CROP_MAP =
{
    {"strawberry",{{"develop_day",3},{"season",SPRING}}},
    {"sunflour",{{"develop_day",4},{"season",SUMMER}}},
    {"pumpkin",{{"develop_day",5},{"season",WINTER}}}
};

class crop : public cocos2d::Sprite
{
private:
    int now_day = 0;                             //当前日期
    static std::string crop_name;                //作物的名称
    static int develop_day;                      //每成长一阶段所需要的天数

	int water_count = 0;                         //浇水总天数
    int unwater_count = 0;                       //没有浇水的连续天数
	int develop_level = 0;                       //目前生长阶段
	int watered_today = 1;                       //今天剩余浇水次数

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
    void water();

    //施肥功能
    void fertilize();

    //清除
    void clear();
    
    //收获功能
    void harvest();
    
    //新一天的更新
    void update_day();

};
#endif __CROP_H__

