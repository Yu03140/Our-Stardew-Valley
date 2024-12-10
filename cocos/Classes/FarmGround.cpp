#include "FarmGround.h"
using namespace cocos2d;
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
    tileMap = TMXTiledMap::create("Myfarm.tmx");
   // tileMap = TMXTiledMap::create("shed.tmx");

    if (tileMap) {
        // ��ȡ��Ļ�Ĵ�С
        Size winSize = Director::getInstance()->getWinSize();

        // ����ê��Ϊ���ģ��Ե�ͼ������Ϊ���յ㣩
        tileMap->setAnchorPoint(Vec2(0.5, 0.5));

        tileMap->setScale(0.8f);

        // ��ȡ��ͼ��ԭʼ�ߴ磨���������ţ�
        Size mapSize = tileMap->getContentSize();

        // �����ͼ��λ�ã�����ͼ��������Ļ����
        float posX = winSize.width / 2;
        float posY = winSize.height / 2;
        tileMap->setPosition(Vec2(posX, posY));

        // ����ͼ��ӵ�������
        this->addChild(tileMap, 0);
    }

    return true;
}
