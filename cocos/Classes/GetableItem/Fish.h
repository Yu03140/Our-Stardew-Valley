#ifndef __FISH_H__
#define __FISH_H__

#include "cocos2d.h"
#include "Global/Global.h"

#define MAX_LEVEL 5
#define DIE_DRY 4
#define WATER_PRED 3
#define EXPERIENCE 10


const std::unordered_map<std::string, std::unordered_map<std::string, int>> FISH_MAP =
{
    {"bluefish",{{"develop_day",5},{"season",SPRING}}},
    {"bluefish",{{"develop_day",4},{"season",SUMMER}}},
    {"bluefish",{{"develop_day",5},{"season",AUTUMN}}}
};

const std::unordered_map<std::string, std::string> HARVEST_FISH_MAP =
{
    {"bluefish","bluefish"},
    {"bluefish","bluefish"},
    {"bluefish","bluefish"}
};

class fish : public cocos2d::Sprite
{
private:
    std::string fish_name= "bluefish";             

    static cocos2d::Texture2D* transparent_texture;
    static cocos2d::Size fish_size;
public:
    // ����ʵ��
    static fish* create(const std::string& plist_name, float width, float height);

    // ��ʼ����������
    void init_mouselistener();

    // ��갴��ʱ�Ļص�
    void on_mouse_click(cocos2d::Event* event);

    // ȡˮ���ܵ�ʵ��
    void water(std::string name);

    // ����
    void fishing(std::string name);

    // ���
    void clear();


};
#endif __FISH_H__
