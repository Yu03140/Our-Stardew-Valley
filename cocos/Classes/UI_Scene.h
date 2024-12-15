#pragma once
#ifndef __UI_SCENE_H__
#define __UI_SCENE_H__
#include "attribute.h"
#include "NPC.h"
#include "TaskBar.h"
#include "TaskBarScene.h"
#include "cocos2d.h"
#include "BackpackLayer.h"

extern std::string selectedItem;


class UI_Scene : public cocos2d::Layer
{
public:
    static UI_Scene* createScene(); // ��������
    virtual bool init();            // ��ʼ��

    CREATE_FUNC(UI_Scene);

private:
    //NPC_Layer* npcLayer;           // NPC ����
    TaskBarScene* taskBarLayer;   // ������
    BackpackLayer* backPackLayer; // ��������
};

#endif // __UI_SCENE_H__
