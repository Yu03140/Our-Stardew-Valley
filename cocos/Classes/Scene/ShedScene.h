#pragma once
#ifndef __SHED_SCENE_H__
#define __SHED_SCENE_H__

#include "cocos2d.h"
#include "SubScene.h"

class ShedScene : public SubScene {
public:

    // ���һ����ʼ����ͼ�ĺ���
    void initTileMap() override;

    // ʵ�ֵ���ģʽ
    static ShedScene* getInstance();
    static cocos2d::Scene* createScene();

    // ��дupdate������������չ��̬�߼�
    virtual void update(float delta) override {}

    // ������¼�����
    void changeScene(cocos2d::Event* event);

    // ʹ��CREATE_FUNC�궨��create����
    CREATE_FUNC(ShedScene);

protected:
    static ShedScene* instance;
};

#endif // __SHED_SCENE_H__