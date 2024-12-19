
#ifndef __NPC_SCENE_H__
#define __NPC_SCENE_H__

#include "cocos2d.h"
#include "NPC.h"

class NPCScene : public cocos2d::Scene {
public:
    NPCScene();
    ~NPCScene();

    // ��ʼ������������NPC�����
    bool init();

    // ����NPC��������
    //static cocos2d::Scene* createScene();

    static NPCScene* create();

    // ������Ϸ���������������NPC�Ľ���
    void update(float delta);

private:
    cocos2d::Sprite* playerSprite; // ��Ҿ���
    NPC* npc1;                      // NPC����
    NPC* npc2;
    // �������Ƿ���NPC�ӽ�����������
    void checkNPCInteraction();
};

#endif // __NPC_SCENE_H__

