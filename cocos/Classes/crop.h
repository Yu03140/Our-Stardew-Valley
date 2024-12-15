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
    int now_day = 0;                             //��ǰ����
    static std::string crop_name;                //���������
    static int develop_day;                      //ÿ�ɳ�һ�׶�����Ҫ������

	int water_count = 0;                         //��ˮ������
    int unwater_count = 0;                       //û�н�ˮ����������
	int develop_level = 0;                       //Ŀǰ�����׶�
	int watered_today = 1;                       //����ʣ�ཽˮ����

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
    void water();

    //ʩ�ʹ���
    void fertilize();

    //���
    void clear();
    
    //�ջ���
    void harvest();
    
    //��һ��ĸ���
    void update_day();

};
#endif __CROP_H__

