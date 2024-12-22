#ifndef TASKBARLAYER_H
#define TASKBARLAYER_H

#include "cocos2d.h"
#include "TaskBar.h"

class TaskBarLayer : public cocos2d::Layer {
public:
    virtual bool init();
    CREATE_FUNC(TaskBarLayer);
    static cocos2d::Scene* createScene();

private:
    TaskBar* taskBar; // TaskBar 对象

    //void initTaskBar(); // 初始化 TaskBar 的方法
};

#endif // TASKBARLAYER_H
