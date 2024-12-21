#ifndef __MINES_SCENE_H__
#define __MINES_SCENE_H__

#include "cocos2d.h"
#include "FarmGround.h"
#include "SubScene.h"

class MinesScene : public SubScene
{
public:

    static MinesScene* getInstance();
    static Scene* createScene();

    // ���һ����ʼ����ͼ�ĺ���
    void initTileMap();

    // ������¼�����
    void changeScene(cocos2d::Event* event);

    // ʹ��CREATE_FUNC�궨��create����
    CREATE_FUNC(MinesScene);

protected:

    static MinesScene* instance;
};

#endif // __MINES_SCENE_H__
