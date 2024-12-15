#include "UI_Scene.h"

USING_NS_CC;

UI_Scene* UI_Scene::createScene()
{
    return UI_Scene::create();
}

bool UI_Scene::init()
{
    //if (!Scene::init())
    //{
        //return false;
   // }

    // 添加 NPC 界面
    //npcLayer = NPC_Layer::create();
    //this->addChild(npcLayer, 1);

    // 添加任务栏
    taskBarLayer = TaskBarScene::create();
    this->addChild(taskBarLayer, 2);

    // 添加背包界面
    backPackLayer = BackpackLayer::create();
    this->addChild(backPackLayer, 3);

    return true;
}
