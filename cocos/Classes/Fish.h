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
    cocos2d::Vec2 barrierPos;  // barrier ��λ��
    float barrierWidth;         // barrier �Ŀ��
    float barrierHeight;        // barrier �ĸ߶�

  //  void checkForPoolClick(cocos2d::Vec2 mousePosition);

    // ���� barrier ��λ�úͳߴ�
    void setBarrierProperties(cocos2d::Vec2 pos, float width, float height);
    // ��ʼ������
  //  bool initWithSpriteName(const std::string& spriteName);
    // ��ʼ����������
   // void init_mouselistener();
    //�жϵ������
    void carry_fishing(Vec2 mousePosition);

    cocos2d::TMXTiledMap* tileMap;

    // ��갴��ʱ�Ļص�
 //   void on_mouse_click(cocos2d::Event* event);
    // ���캯�����������ǽ��
//    Fish(cocos2d::Node* player);

    // �������ʱ�Ĵ�����
  //  void finishFishing(cocos2d::Layer* parentLayer);
    //���㹦��
    void fishing(std::string name);

    //��ˮ���ܵ�ʵ��
    void takewater(std::string name);

    //�ջ���
    void harvest();

  //  void startFishingAtPosition(const cocos2d::Vec2& fishingPoint); // ��ʼ����
  //  void stopFishing();                                             // ֹͣ����
  //  void updateFishing(float dt);                                   // ���µ���״̬

    bool isFishing() const { return fishingState; } // ��鵱ǰ�Ƿ����ڵ���

private:
  //  bool initWithBackpack(BackpackLayer* backpackLayer); // ˽�г�ʼ������
    bool fishingState = false;                  // ����״̬

    cocos2d::Vec2 fishingTarget;                // ����Ŀ��λ��
    // �����㣬���ڻ�ȡ����
    BackpackLayer* backpackLayer;
    cocos2d::Sprite* fishingLine = nullptr;     // ����
    // ����ָ��
    moveable_sprite_key_walk* sprite_move;  
    std::string fish_name;                //�������
  //
  //static cocos2d::Texture2D* transparent_texture;
  //static cocos2d::Size crop_size;

};

#endif // FISH_H



//struct GOODS_INHAND {
//    std::string goods_name;
//};
//
////������ֲ�����Ϣ
//const std::unordered_map<std::string, std::unordered_map<std::string, int>> CROP_MAP =
//{
//    {"strawberry",{{"develop_day",5},{"season",SPRING}}},
//    {"sunflour",{{"develop_day",4},{"season",SUMMER}}},
//    {"pumpkin",{{"develop_day",5},{"season",AUTUMN}}}
//};
////��������õ�������Ʒ
//const std::unordered_map<std::string, std::string> HARVEST_MAP =
//{
//    {"strawberry","strawberry_fruit"},
//    {"sunflour","sunflour_fruit"},
//    {"pumpkin","sunflour_fruit"}
//};
//
