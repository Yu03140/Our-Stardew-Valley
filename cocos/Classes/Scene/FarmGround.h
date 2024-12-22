#ifndef __FARM_GROUND_H__
#define __FARM_GROUND_H__

#include "cocos2d.h"
#include "Charactor/BackpackLayer.h"
#include "Moveable/moveable_sprite_key.h"
#include "Global/Global.h"
#include "GetableItem/crop.h"
#include "GetableItem/animals.h"
#include "GetableItem/getable_goods.h"
/*----------------------------------------------------------------RENEW2-----------------------------------------------------------------------------*/
#include "MinesScene.h"
#include "HomeScene.h"
#include "ShedScene.h"

/*----------------------------------------------------------------RENEW2-----------------------------------------------------------------------------*/

#define MapSize 4
/*----------------------------------------------------------------RENEW2-----------------------------------------------------------------------------*/
/*----------------------------------------------------------------RENEW2-----------------------------------------------------------------------------*/


struct Crops {
    std::string name;        // ��Ʒ����
    crop* sprite; // ��ʾ��Ʒ�ľ���
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

    moveable_sprite_key_tool* main_tool;

      // �궨�壬���ڴ�������
    CREATE_FUNC(FarmScene);

private:
    // ���º������Ʒ����
    void updateItemTexture(int slotIndex);
    void clearItemTexture(int slotIndex);

    // ���������λ��
    void updateCameraPosition(float dt, Node* player);

    // ũ��������
    std::vector<Crops> crops;

    // ��Ƭ��ͼ
    cocos2d::TMXTiledMap* tilemap;
    /*------------------------------------------------------renew-------------------------------------------------------------*/
    moveable_sprite_key_walk* main_char = nullptr;
    // ��ʼ����������
    void init_mouselistener();

    // ���ص�
    void on_mouse_click(cocos2d::Event* event);
    
    void checkForButtonClick(Vec2 mousePosition);

    void onEnter();
    void onExit();
    
 /*------------------------------------------------------renew-------------------------------------------------------------*/
};

#endif // __FARM_GROUND_H__