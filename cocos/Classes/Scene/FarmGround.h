#ifndef __FARM_GROUND_H__
#define __FARM_GROUND_H__

#include "cocos2d.h"
#include "Charactor/BackpackLayer.h"
#include "Moveable/moveable_sprite_key.h"
#include "Global/Global.h"
#include "NPC/NPC.h"//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@2����������ǵ��޸��ļ���·��
#include "TimeSystem/TimeSystem.h"


struct Crops {
    std::string name;        // ��Ʒ����
    //  int quantity;            // ��Ʒ����
    cocos2d::Sprite* sprite; // ��ʾ��Ʒ�ľ���
};

class FarmScene : public cocos2d::Scene {
    cocos2d::TMXTiledMap* tileMap;

public:
    // ���� FarmScene
    static FarmScene* createScene();

    // ��ʼ������
    virtual bool init();
    // ��ӻ��Ƴ���Ʒ
    void addItem(const std::string& itemName);
    //  void removeItem(const std::string& itemName);

      // �궨�壬���ڴ�������
    CREATE_FUNC(FarmScene);

private:
    // ���º������Ʒ����
    void updateItemTexture(int slotIndex);
    void clearItemTexture(int slotIndex);

    // ũ��������
    std::vector<Crops> crops;

    // ��Ƭ��ͼ
    cocos2d::TMXTiledMap* tilemap;
    //-------renew(dxn)-------------------------------------------------------
    NPC* npc1;                      // NPC����
    NPC* npc2;
    // �������Ƿ���NPC�ӽ�����������
    void update(float delta);
    void checkNPCInteraction();
    //--------------end----------------------------------------------------------

};

#endif // __FARM_GROUND_H__