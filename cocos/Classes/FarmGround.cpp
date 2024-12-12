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
    // ��ȡ��Ļ�ɼ�����Ĵ�С��ԭ��
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // ���������TMX��ͼ
    tileMap = TMXTiledMap::create("Content/Maps/Farm.tmx");
    if (tileMap) {
        CCLOG("TileMap loaded successfully. Map size: %f x %f",
            tileMap->getContentSize().width,
            tileMap->getContentSize().height);
        Size visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        tileMap->setPosition(Vec2(origin.x + visibleSize.width / 2 - tileMap->getContentSize().width / 2,
            origin.y + visibleSize.height / 2 - tileMap->getContentSize().height / 2));

        addChild(tileMap, 0, 100);
    }
    else {
        CCLOG("Failed to load TMX file: csva.tmx");
        return false;
    }

    //addChild(sprite); // ���ͼƬ���سɹ���������ʾ�ڳ�����


    // ����Ҿ�����ӵ�������
    //addChild(player, 2, 200);


    return true;
}
