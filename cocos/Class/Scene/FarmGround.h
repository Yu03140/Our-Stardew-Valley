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
#include "GetableItem/Fish.h"
#include "Shop/Shop_board_Layer.h"

#define MapSize 4
#define TOOL_WIDTH 40
#define TOOL_HEIGHT 60

struct Crops {
    std::string name;                                             // ��Ʒ����
    crop* sprite;                                                 // ��ʾ��Ʒ�ľ���
};  

struct Fish {
    std::string name;                                             // �ϰ�������
    fish* sprite;                                                 // ��ʾ��Ʒ�ľ���
};

class FarmScene : public cocos2d::Scene {

public:
	static FarmScene* getInstance();						      // ��ȡ FarmScene ʵ��
    static Scene* createScene();                                  // ���� FarmScene
	virtual bool init();									      // ��ʼ�� FarmScene
	void addItem(const std::string& itemName);				      // �����Ʒ 
    CREATE_FUNC(FarmScene);                                       // ʹ�� CREATE_FUNC ��
	cocos2d::TMXTiledMap* tileMap;						          // ��Ƭ��ͼ 
    void update(float dt, moveable_sprite_key_walk* sprite_move); // ���·�����ÿ֡����
	void replaceHouseImage();   						          // �滻����ͼƬ  
	cocos2d::Sprite* badWarmHouse;							      // ���ݾ���
	bool checkForwarmhouseClick(Vec2 mousePosition);              // ���ݵ�����

private:
    void updateItemTexture(int slotIndex);                        // ������Ʒ����
    void clearItemTexture(int slotIndex);                         // ������Ʒ����
	void updateCameraPosition(float dt, Node* player);		      // ���������λ��      
	std::vector<Crops> crops;									  // ��������
	std::vector<Fish> fish;									      // ������
	static FarmScene* instance;								      // FarmScene ʵ��
	void init_mouselistener();							 		  // ��ʼ����������
    void on_mouse_click(cocos2d::Event* event);                   // ���ص�
	void checkForButtonClick(Vec2 mousePosition);                 // ��鰴ť���   
	void onEnter(); 										      // ���볡��
	void onExit();											      // �˳�����
    NPC* npc1;                                                    // NPC����
	NPC* npc2;      							                  // NPC����        
	void update(float delta);									  // �������Ƿ���NPC�ӽ�����������
	void checkNPCInteraction();								      // ���NPC����
	Board* board;										  		  // �������
	TaskBarLayer* taskBarLayer;								      // ������
	Shop_Board_Layer* shop_board_layer;							  // �̵����
    cocos2d::Sprite* house;										  // ���Ӿ���
    cocos2d::Sprite* shed;								          // ���ݾ���
    moveable_sprite_key_walk* sprite_move;						  // ��������������

};

#endif  __FARM_GROUND_H__