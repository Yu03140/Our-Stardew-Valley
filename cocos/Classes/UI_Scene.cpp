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

    // ��� NPC ����
    //npcLayer = NPC_Layer::create();
    //this->addChild(npcLayer, 1);

    // ���������
    taskBarLayer = TaskBarScene::create();
    this->addChild(taskBarLayer, 2);

    // ��ӱ�������
    backPackLayer = BackpackLayer::create();
    this->addChild(backPackLayer, 3);

    return true;
}
