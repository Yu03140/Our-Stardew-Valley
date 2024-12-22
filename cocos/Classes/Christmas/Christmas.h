#pragma once
#ifndef __CHRISTMAS_SCENE_H__
#define __CHRISTMAS_SCENE_H__

#include "cocos2d.h"

class ChristmasScene : public cocos2d::Scene {
public:
    // ���캯������������
    ChristmasScene();
    ~ChristmasScene();

    // ���������ľ�̬����
    static ChristmasScene* createScene();

    // ��ʼ������
    virtual bool init();


    // ��ȡ������ť����¼�
    void onGetRewardClicked(cocos2d::Ref* sender);

    // ����������
    void goBackToMainScene();


    void createFixedText();
    void updateTextPerCharacter(float dt);

private:
    cocos2d::Sprite* _background;       // ʥ������
    cocos2d::Sprite* _talkBoard;        // �Ի���
    cocos2d::Label* _scrollingText;     // �����ı�
    cocos2d::MenuItemImage* _getButton; // ��ȡ��ť
    bool _isTextScrolling;              // �ı��Ƿ����ڹ���
    float _scrollingSpeed;              // �����ٶ�
    std::string _message;               // ��������Ϣ
};

#endif // __CHRISTMAS_SCENE_H__

