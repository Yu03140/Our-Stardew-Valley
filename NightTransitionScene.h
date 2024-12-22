#pragma once
#include "cocos2d.h"

class NightTransitionScene : public cocos2d::Scene {
public:
    // ���캯��
    NightTransitionScene() {}

    // ��������
    static NightTransitionScene* createScene() {
        NightTransitionScene* ret = new NightTransitionScene();
        if (ret && ret->init()) {
            ret->autorelease();
            return ret;
        }
        else {
            delete ret;
            return nullptr;
        }
    }

    // ��ʼ������
    bool init() {
        if (!Scene::init()) {
            return false;
        }

        // ��ȡ��Ļ�ߴ�
        auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

        // ����ȫ���� night.png ͼƬ
        auto nightOverlay = cocos2d::Sprite::create("night.png");
        if (!nightOverlay) {
            CCLOG("Failed to load night.png");
            return false;
        }

        // ����ͼƬ��С����Ӧ������Ļ
        nightOverlay->setContentSize(visibleSize);
        nightOverlay->setPosition(visibleSize.width, visibleSize.height / 2);  // ��ʼλ������Ļ�Ҳ�����

        // ��ͼƬ��ӵ�������
        this->addChild(nightOverlay, 100);

        // ������������Ķ���
        auto moveLeft = cocos2d::MoveBy::create(2.0f, cocos2d::Vec2(-visibleSize.width/2, 0));  // �����ƶ�������Ļ���
        auto delay = cocos2d::DelayTime::create(3.0f);  // ͣ��3��
        auto removeOverlay = cocos2d::CallFunc::create([nightOverlay]() {
            nightOverlay->removeFromParent();  // �Ƴ�ҹ������
            });

        // �������У�ҹ��ͼƬ������� -> ͣ��3�� -> �Ƴ�ͼƬ
        nightOverlay->runAction(cocos2d::Sequence::create(moveLeft, delay, removeOverlay, nullptr));

        // ��3���ӳٺ󷵻ص�ԭ����
        this->scheduleOnce([this](float dt) {
            // ��ת�������󷵻�ԭ����
            cocos2d::Director::getInstance()->popScene();
            }, 5.0f, "return_scene_key");

        return true;
    }
};

