#include "TaskBarLayer.h"
#include "Global/Global.h"

cocos2d::Scene* TaskBarLayer::createScene() {
    auto scene = cocos2d::Scene::create(); // ����һ���³���
    auto layer = TaskBarLayer::create();  // ������������
    scene->addChild(layer); // ������������ӵ�������
    return scene; // ���س���
}

bool TaskBarLayer::init() {
    if (!Layer::init()) { // ���ø����ʼ������
        return false; // ���ʧ�ܣ��򷵻� false
    }

    // ����������
    auto taskBar = TaskBar::create(
        "One Axe1 for 50$\n From Bouncer", // ��������
        "Bouncer", // NPC ����
        []() {

            
        });
    // ��������������Ļ����
    auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    taskBar->setAnchorPoint(Vec2(0.5, 0.5));
    taskBar->setPosition(cocos2d::Vec2(visibleSize.width / 2- visibleSize.width * (0.1), visibleSize.height / 2- visibleSize.height * (0.05)));
    // ���taskBar�ĸ߶ȺͿ��
	auto taskBarSize = taskBar->getContentSize();
	CCLOG("taskBarSize.width = %f, taskBarSize.height = %f", taskBarSize.width, taskBarSize.height);
    taskBar->setVisible(false); // ��ʼ���ɼ�
    this->addChild(taskBar,2); // ����������ӵ���ǰ����

    // ������ť��������ʾ������
    auto showTaskBarButton = cocos2d::MenuItemImage::create(
        "TaskBarOrigin.png", // ��ť������״̬ͼ��
        "TaskBarOrigin.png", // ��ť��ѡ��״̬ͼ��
        [taskBar](Ref* sender) { // ��ť�ص��������������ʾ������
            taskBar->show();
        });
    //?????????????????????????????????????????????????????
    showTaskBarButton->setPosition(cocos2d::Vec2(visibleSize.width * 0.5, visibleSize.height * 0.5 - taskBarSize.height)); // ���ð�ťλ��
    CCLOG("showTaskBarButton->getPosition().x = %f", showTaskBarButton->getPosition().x);

    // �����˵�������ť��ӵ��˵���
    auto menu = cocos2d::Menu::create(showTaskBarButton, nullptr);
    menu->setPosition(cocos2d::Vec2::ZERO+Vec2(visibleSize.width*(-0.01), visibleSize.width * (-0.05))); // ���ò˵�λ��Ϊԭ��
	//CCLOG("menu->getPosition().x = %f", menu->getPosition().x);
    this->addChild(menu,2); // ���˵���ӵ���ǰ����


    return true; // ��ʼ���ɹ�
}