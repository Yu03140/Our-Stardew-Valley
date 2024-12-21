#pragma once
#ifndef __HOME_SCENE_H__
#define __HOME_SCENE_H__

#include "SubScene.h"
#include "cocos2d.h"

class HomeScene : public SubScene {
public:

    // ���һ����ʼ����ͼ�ĺ���
    void initTileMap() override;

    // ʵ�ֵ���ģʽ
    static HomeScene* getInstance();
    static cocos2d::Scene* createScene();

    // ��дupdate������������չ��̬�߼�
    virtual void update(float delta) override;

    // ������¼�����
    void changeScene(cocos2d::Event* event);

    // ʹ��CREATE_FUNC�궨��create����
    CREATE_FUNC(HomeScene);

protected:
    static HomeScene* instance;
};

#endif // __HOME_SCENE_H__