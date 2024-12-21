#ifndef __FARM_GROUND_H__
#define __FARM_GROUND_H__

#include "cocos2d.h"
#include "Charactor/BackpackLayer.h"
#include "Moveable/moveable_sprite_key.h"
#include "Global/Global.h"
#include "GetableItem/Crop.h"
#include "GetableItem/Animals.h"
#include "NPC/NPC.h"
#include "MinesScene.h"
#include "HomeScene.h"
#include "ShedScene.h"

#define MapSize 4
#define TOOL_WIDTH 40
#define TOOL_HEIGHT 60

    struct Crops {
        std::string name;        // ��Ʒ����
        crop* sprite; // ��ʾ��Ʒ�ľ���
    };

    class FarmScene : public cocos2d::Scene {

    public:
        // ���� FarmScene
        static FarmScene* getInstance();
        static Scene* createScene();
        // ��ʼ������
        virtual bool init();
        // ��ӻ��Ƴ���Ʒ
        void addItem(const std::string& itemName);
        //  void removeItem(const std::string& itemName);

        CREATE_FUNC(FarmScene); // ʹ�� CREATE_FUNC ��

        // ��Ƭ��ͼ
        cocos2d::TMXTiledMap* tileMap;


    private:
        // ���º������Ʒ����
        void updateItemTexture(int slotIndex);
        void clearItemTexture(int slotIndex);

        // ���������λ��
        void updateCameraPosition(float dt, Node* player);

        // ũ��������
        std::vector<Crops> crops;

        static FarmScene* instance;

        // ��ʼ����������
        void init_mouselistener();

        // ���ص�
        void on_mouse_click(cocos2d::Event* event);

        void checkForButtonClick(Vec2 mousePosition);

        void FarmScene::onEnter();

        NPC* npc1;                      // NPC����
        NPC* npc2;
        // �������Ƿ���NPC�ӽ�����������
        void update(float delta);
        void checkNPCInteraction();

		Board* board;
		TaskBarLayer* taskBarLayer;

    };

#endif // __FARM_GROUND_H__�ڴ�������