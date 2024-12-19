#pragma once
#ifndef TASKBARSCENE_H
#define TASKBARSCENE_H

#include "cocos2d.h"
#include "TaskBar.h"
#include "Attribute/attribute.h" 
/**
 * @brief TaskBarScene 类用于管理任务栏的场景。
 * 该类继承自 cocos2d::Layer，提供显示任务栏、处理任务交互的功能。
 */
class TaskBarLayer : public cocos2d::Layer {
public:
    /**
     * @brief 创建并返回任务栏场景。
     * @return 一个包含任务栏的 cocos2d::Scene 对象。
     */
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
    CREATE_FUNC(TaskBarLayer);

private:
    // 在此处添加任何需要的私有成员变量或辅助函数。
};

#endif // TASKBARSCENE_H
