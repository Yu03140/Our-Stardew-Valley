#ifndef __FISH_H__
#define __FISH_H__

#include "cocos2d.h"
#include "Global/Global.h"

#define MAX_LEVEL 5
#define DIE_DRY 4
#define WATER_PRED 3
#define EXPERIENCE 10

//������ֲ�����Ϣ
const std::unordered_map<std::string, std::unordered_map<std::string, int>> FISH_MAP =
{
    {"bluefish",{{"develop_day",5},{"season",SPRING}}},
    {"bluefish",{{"develop_day",4},{"season",SUMMER}}},
    {"bluefish",{{"develop_day",5},{"season",AUTUMN}}}
};
//��������õ�������Ʒ
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
    int now_day = 0;                             //��ǰ����
    std::string fish_name= "bluefish";                //���������
    int develop_day;                      //ÿ�ɳ�һ�׶�����Ҫ������

    int water_count = 0;                         //��ˮ������
    int unwater_count = 0;                       //û�н�ˮ����������
    int develop_level = 0;                       //Ŀǰ�����׶�
    int watered_today = WATER_PRED;                       //����ʣ�ཽˮ����

    static cocos2d::Texture2D* transparent_texture;
    static cocos2d::Size fish_size;
public:
    // ����ʵ��
    static fish* create(const std::string& plist_name, float width, float height);

    // ��ʼ����������
    void init_mouselistener();

    // ��갴��ʱ�Ļص�
    void on_mouse_click(cocos2d::Event* event);

    //��ˮ���ܵ�ʵ��
    void water(std::string name);

    //����
    void fishing(std::string name);

    //���
    void clear();


};
#endif __FISH_H__
