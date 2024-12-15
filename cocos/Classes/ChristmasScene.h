#ifndef __NPC_SCENE_H__
#define __NPC_SCENE_H__

#include "cocos2d.h"
#include "NPC.h"

class ChristmasScene : public cocos2d::Scene {
public:
    ChristmasScene();
    ~ChristmasScene();

    // ��ʼ������������NPC�����
    bool init();

    // ����NPC��������
    //static cocos2d::Scene* createScene();

    static ChristmasScene* create();

    // ������Ϸ���������������NPC�Ľ���
    void update(float delta);



    void setupBackground();

private:
    cocos2d::Sprite* playerSprite; // ��Ҿ���
    NPC* npc3;                      // NPC����

    // �������Ƿ���NPC�ӽ�����������
    void checkNPCInteraction();
};

#endif // __NPC_SCENE_H__
