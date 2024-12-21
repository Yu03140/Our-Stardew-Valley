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

//������ֲ�����Ϣ
const std::unordered_map<std::string, std::unordered_map<std::string,int>> CROP_MAP =
{
    {"strawberry",{{"develop_day",5},{"season",SPRING}}},
    {"sunflour",{{"develop_day",4},{"season",SUMMER}}},
    {"pumpkin",{{"develop_day",5},{"season",AUTUMN}}}
};
//��������õ�������Ʒ
const std::unordered_map<std::string, std::string> HARVEST_MAP =
{
    {"strawberry","strawberry_fruit"},
    {"sunflour","sunflour_fruit"},
    {"pumpkin","sunflour_fruit"}
};

class crop : public cocos2d::Sprite
{
private:
    int now_day = 0;                             //��ǰ����
    std::string crop_name;                       //���������
    int develop_day;                              //ÿ�ɳ�һ�׶�����Ҫ������

	int water_count = 0;                         //��ˮ������
    int unwater_count = 0;                       //û�н�ˮ����������
	int develop_level = 0;                       //Ŀǰ�����׶�
	int watered_today = WATER_PRED;                       //����ʣ�ཽˮ����

    static cocos2d::Texture2D* transparent_texture;
    static cocos2d::Size crop_size;
public:
    // ����ʵ��
    static crop* create(const std::string& plist_name, float width, float height);

    // ��ʼ����������
    void init_mouselistener();

    // ��갴��ʱ�Ļص�
    void on_mouse_click(cocos2d::Event* event);

    //��ֲ����
    void planting(std::string name);

    //��ˮ���ܵ�ʵ��
    void water(std::string name);

    //ʩ�ʹ���
    void fertilize(std::string name);

    //���
    void clear();
    
    //�ջ���
    void harvest();
    
    //��һ��ĸ���
    void update_day(float deltaTime);

    //����
    void deinsectization();

};
#endif __CROP_H__

