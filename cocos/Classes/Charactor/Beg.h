#ifndef __BACKPACK_LAYER_H__
#define __BACKPACK_LAYER_H__

#include "cocos2d.h"

class BackpackLayer : public cocos2d::Layer
{
public:
    // ���캯������������
    BackpackLayer();
    ~BackpackLayer();

    // ������������
    static BackpackLayer* create();

    // ��ʼ������
    virtual bool init();

    // ��ӱ�����Ʒ
    void addItem(const std::string& itemName, const std::string& itemImage);

    // �л������Ŀɼ���
    void toggleVisibility();

private:
    // ������������
    cocos2d::Sprite* backpackBackground;

    // ��Ʒ����
    std::vector<cocos2d::Sprite*> items;
};

#endif // __BACKPACK_LAYER_H__
