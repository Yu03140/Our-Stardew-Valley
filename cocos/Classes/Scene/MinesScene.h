#ifndef __MINES_SCENE_H__
#define __MINES_SCENE_H__

#include "cocos2d.h"

class MinesScene : public cocos2d::Scene
{
public:

    static MinesScene* getInstance();
    static Scene* createScene();

    // ��ʼ������
    virtual bool init();

    // ���һ����ʼ����ͼ�ĺ���
    void initTileMap();

    // ��дupdate������������չ��̬�߼�
    virtual void update(float delta) override;

    // ������¼�����
    void onMouseDown(cocos2d::Event* event);

    // ʹ��CREATE_FUNC�궨��create����
    CREATE_FUNC(MinesScene);

private:
    // ��Ƭ��ͼ��ָ��
    cocos2d::TMXTiledMap* _tileMap;

    // ��ײ����ض�����Ƭͼ�㣨�����Ҫ�����ϰ���������߼���
    cocos2d::TMXLayer* _collisionLayer;

    static MinesScene* instance;
};

#endif // __MINES_SCENE_H__
