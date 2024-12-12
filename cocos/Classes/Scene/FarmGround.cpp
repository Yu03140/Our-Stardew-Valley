#include "FarmGround.h"
#include "Charactor/BackpackLayer.h"
#include "TimeSystem/TimeSystem.h"

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
    auto tileMap = Sprite::create("homepage.jpg");
    //auto tileMap = TMXTiledMap::create("Farm.tmx");

    if (tileMap) {
        // �ɹ����ص�ͼ��������Ϊ�������ӽڵ�
        this->addChild(tileMap);
    }
    else {
        CCLOG("Failed to load the tile map");
    }

    // ��������ͼ�㣬��������ӵ�������
    auto backpackLayer = BackpackLayer::create(); 
    if (backpackLayer) {
        // ���ñ���ͼ�ĳߴ�Ϊ 2560x1600
        tileMap->setContentSize(Size(2560, 1600)); // ���ñ���ͼ�Ĵ�С

        // ������ͼ��λ������Ϊ����������
        tileMap->setPosition(Director::getInstance()->getVisibleSize() / 2);
        
        // ������ͼ����ӵ��������ӽڵ㣬ȷ�����ڱ���ͼ���Ϸ�
        this->addChild(backpackLayer, 1);  
    }

	// ����ʱ��ϵͳʵ��
    // ���� TimeSystem �̳��� Node
    TimeSystem* timeSystem = TimeSystem::getInstance();  // ��ȡ TimeSystem ��ʵ��

    // ȷ����ǰ�ڵ��� Node ���ͣ�ͨ���� Layer �� Scene��
    Node* parentNode = this;  

    // ��� TimeSystem �� parentNode ��
    parentNode->addChild(timeSystem);



    return true;
}
