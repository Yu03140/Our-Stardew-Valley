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
     * @brief 初始化任务栏场景。
     * @return 初始化是否成功。
     */
    virtual bool init();

    /**
     * @brief 启用 CREATE_FUNC 宏，用于简化创建对象的代码。
     * CREATE_FUNC 会自动生成静态 create() 方法。
     */
    CREATE_FUNC(Shop_Board_Layer);

private:
    // 在此处添加任何需要的私有成员变量或辅助函数。
};

#endif // TASKBARSCENE_H
