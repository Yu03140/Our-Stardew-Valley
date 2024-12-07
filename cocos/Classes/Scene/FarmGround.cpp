#include "FarmGround.h"

USING_NS_CC;

FarmScene* FarmScene::createScene() {
    // ���������� FarmScene ��������
    return FarmScene::create();
}



bool FarmScene::init() {
    // ���ø���ĳ�ʼ������
    if (!Scene::init()) {
        return false;
    }


    // ������Ƭ��ͼ����Ҫ�� example.tmx ���� Resources/ Ŀ¼�У�
    auto tileMap = TMXTiledMap::create("Farm.tmx");

    if (tileMap) {
        // �ɹ����ص�ͼ��������Ϊ�������ӽڵ�
        this->addChild(tileMap);
    }
    else {
        CCLOG("Failed to load the tile map");
    }


    // ʾ������ȡһ�������鲢��ȡ����
    auto objectGroup = tileMap->getObjectGroup("Objects"); // �����������Ϊ "Objects"
    if (objectGroup) {
        // ��ȡһ���������磺PlayerStart����λ��
        auto playerStart = objectGroup->getObject("PlayerStart");
        float x = playerStart["x"].asFloat();
        float y = playerStart["y"].asFloat();
        CCLOG("Player spawn point: (%f, %f)", x, y);
    }

    return true;
}
