#pragma once
#ifndef SHOP_BOARD_LAYER_H
#define SHOP_BOARD_LAYER_H

#include "cocos2d.h"
#include "Shop_board.h"
#include "Attribute/attribute.h" 

class Shop_Board_Layer : public cocos2d::Layer {
public:

    static cocos2d::Scene* createScene();

    /**
     * @brief ��ʼ��������������
     * @return ��ʼ���Ƿ�ɹ���
     */
    virtual bool init();

    /**
     * @brief ���� CREATE_FUNC �꣬���ڼ򻯴�������Ĵ��롣
     * CREATE_FUNC ���Զ����ɾ�̬ create() ������
     */
    CREATE_FUNC(Shop_Board_Layer);

private:
    // �ڴ˴�����κ���Ҫ��˽�г�Ա��������������
};

#endif // TASKBARSCENE_H
