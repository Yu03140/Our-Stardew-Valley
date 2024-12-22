#ifndef FISH_H
#define FISH_H

#include "Charactor/BackpackLayer.h"
#include "Moveable/moveable_sprite_key.h"
#include "Global/Global.h"
#include "cocos2d.h"

class Fish : public cocos2d::Sprite
{

public:
    static Fish* create(const std::string& spriteName);
    cocos2d::Vec2 barrierPos;  // barrier 的位置
    float barrierWidth;         // barrier 的宽度
    float barrierHeight;        // barrier 的高度

  //  void checkForPoolClick(cocos2d::Vec2 mousePosition);

    // 设置 barrier 的位置和尺寸
    void setBarrierProperties(cocos2d::Vec2 pos, float width, float height);
    // 初始化方法
  //  bool initWithSpriteName(const std::string& spriteName);
    // 初始化鼠标监听器
   // void init_mouselistener();
    //判断点击池塘
    void carry_fishing(Vec2 mousePosition);

    cocos2d::TMXTiledMap* tileMap;

    // 鼠标按下时的回调
 //   void on_mouse_click(cocos2d::Event* event);
    // 构造函数，接收主角结点
//    Fish(cocos2d::Node* player);

    // 钓鱼完成时的处理函数
  //  void finishFishing(cocos2d::Layer* parentLayer);
    //钓鱼功能
    void fishing(std::string name);

    //接水功能的实现
    void takewater(std::string name);

    //收获功能
    void harvest();

  //  void startFishingAtPosition(const cocos2d::Vec2& fishingPoint); // 开始钓鱼
  //  void stopFishing();                                             // 停止钓鱼
  //  void updateFishing(float dt);                                   // 更新钓鱼状态

    bool isFishing() const { return fishingState; } // 检查当前是否正在钓鱼

private:
  //  bool initWithBackpack(BackpackLayer* backpackLayer); // 私有初始化函数
    bool fishingState = false;                  // 钓鱼状态

    cocos2d::Vec2 fishingTarget;                // 钓鱼目标位置
    // 背包层，用于获取钓竿
    BackpackLayer* backpackLayer;
    cocos2d::Sprite* fishingLine = nullptr;     // 鱼线
    // 主角指针
    moveable_sprite_key_walk* sprite_move;  
    std::string fish_name;                //鱼的名称
  //
  //static cocos2d::Texture2D* transparent_texture;
  //static cocos2d::Size crop_size;

};

#endif // FISH_H



//struct GOODS_INHAND {
//    std::string goods_name;
//};
//
////作物种植相关信息
//const std::unordered_map<std::string, std::unordered_map<std::string, int>> CROP_MAP =
//{
//    {"strawberry",{{"develop_day",5},{"season",SPRING}}},
//    {"sunflour",{{"develop_day",4},{"season",SUMMER}}},
//    {"pumpkin",{{"develop_day",5},{"season",AUTUMN}}}
//};
////作物成熟后得到的生成品
//const std::unordered_map<std::string, std::string> HARVEST_MAP =
//{
//    {"strawberry","strawberry_fruit"},
//    {"sunflour","sunflour_fruit"},
//    {"pumpkin","sunflour_fruit"}
//};
//
