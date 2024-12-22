#pragma once
#ifndef SHOP_BOARD_H
#define SHOP_BOARD_H

#include "cocos2d.h"
#include <string>
#include "Global/Global.h"


class Shop_Board : public cocos2d::Node {
public:

    static Shop_Board* create(std::function<void()> Shop_BoardCallback);


    virtual bool init(std::function<void()> Shop_BoardCallback);

    void show();


    void hide();

    int judgePrice() {
        if (timeSystem->getSeason() == 1) {
            return 12;
        }
        else {
            return 10;
        }
    }

private:

    bool isOpen=0; ///< �����Ƿ���ɵı�־��
    cocos2d::Label* descriptionLabel; ///< ��ʾ��Ʒ�۸������ı�ǩ��

    cocos2d::MenuItemImage* item_strawberry; ///<��Ʒ1��
    cocos2d::MenuItemImage* item_pumpkin; ///<��Ʒ2��




    cocos2d::MenuItemImage* closeButton; ///< ���رա���ť��
    std::function<void()> Shop_BoardCallback; ///< �������Ļص�������

    /**
     * @brief ��������񡱰�ť�Ļص�������
     */
    void buyitem_strawberry();
    void buyitem_pumpkin();

    /**
     * @brief ���رա���ť�Ļص�������
     */
    void onClose();
};

#endif // TASKBAR_H
