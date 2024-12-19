#include "TaskBarScene.h"
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
        "One pumpkin for 50$\n From Bouncer", // ��������
        "Bouncer", // NPC ����
        []() {

            // ��������Ļص������������޸���ҲƲ��� NPC �øж�
            Player* player = Player::getInstance();
            player->playerproperty.addExperience(50);
            player->playerproperty.addReputation(50);
            player->playerproperty.addMoney(50);
            //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@�޸ı���
            //bool��������Ƿ�����������

            cocos2d::log("��ҲƲ��ͺøж��Ѹ��£�");
        });
    // ��������������Ļ����
    auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    taskBar->setAnchorPoint(Vec2(1, 1));
    taskBar->setPosition(cocos2d::Vec2(visibleSize.width / 4, visibleSize.height / 4));
	CCLOG("visibleSize.width / 4=%f,visibleSize.height / 4=%f", visibleSize.width / 4, visibleSize.height / 4);
    taskBar->setVisible(false); // ��ʼ���ɼ�
    this->addChild(taskBar); // ����������ӵ���ǰ����

    // ������ť��������ʾ������
    auto showTaskBarButton = cocos2d::MenuItemImage::create(
        "TaskBarOrigin.png", // ��ť������״̬ͼ��
        "TaskBarOrigin.png", // ��ť��ѡ��״̬ͼ��
        [taskBar](Ref* sender) { // ��ť�ص��������������ʾ������
            taskBar->show();
        });
    //?????????????????????????????????????????????????????
    showTaskBarButton->setPosition(cocos2d::Vec2(200, 1000)); // ���ð�ťλ��

    // �����˵�������ť��ӵ��˵���
    auto menu = cocos2d::Menu::create(showTaskBarButton, nullptr);
    menu->setPosition(cocos2d::Vec2::ZERO); // ���ò˵�λ��Ϊԭ��
    this->addChild(menu); // ���˵���ӵ���ǰ����


    return true; // ��ʼ���ɹ�
}
