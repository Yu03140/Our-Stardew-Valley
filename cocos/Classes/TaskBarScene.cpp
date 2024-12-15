#include "TaskBarScene.h"

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//! ע�⣡������ͼ�㣬��ӵ������е����������ͬ������
/**    // ���г��������� Director ���иó�����
auto scene = cocos2d::Scene::create(); // ����һ���ճ���
auto layer = TaskBarScene::create(); // ������Ĳ�
scene->addChild(layer);               // ������ӵ�����
cocos2d::Director::getInstance()->runWithScene(scene); // ���г���*/









/**
 * @brief ����������������
 * @return ���ذ����������ĳ�������
 */
cocos2d::Scene* TaskBarScene::createScene() {
    auto scene = cocos2d::Scene::create(); // ����һ���³���
    auto layer = TaskBarScene::create();  // ������������
    scene->addChild(layer); // ������������ӵ�������
    return scene; // ���س���
}

/**
 * @brief ��ʼ��������������
 * @return ��ʼ���Ƿ�ɹ���
 */
bool TaskBarScene::init() {
    if (!Layer::init()) { // ���ø����ʼ������
        return false; // ���ʧ�ܣ��򷵻� false
    }

    // ����������
    auto taskBar = TaskBar::create(
        "One pumpkin for 50$\n From Bouncer", // ��������
        "Bouncer", // NPC ����
        []() {
            // ��������Ļص������������޸���ҲƲ��� NPC �øж�
            cocos2d::log("��ҲƲ��ͺøж��Ѹ��£�");
        });
    // ��������������Ļ����
    auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    auto origin = cocos2d::Director::getInstance()->getVisibleOrigin();
    taskBar->setPosition(cocos2d::Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height / 2));

    this->addChild(taskBar); // ����������ӵ���ǰ����

    // ������ť��������ʾ������
    auto showTaskBarButton = cocos2d::MenuItemImage::create(
        "ShowTaskBarNormal.png", // ��ť������״̬ͼ��
        "ShowTaskBarSelected.png", // ��ť��ѡ��״̬ͼ��
        [taskBar](Ref* sender) { // ��ť�ص��������������ʾ������
            taskBar->show();
        });
    showTaskBarButton->setPosition(cocos2d::Vec2(240, 320)); // ���ð�ťλ��

    // �����˵�������ť��ӵ��˵���
    auto menu = cocos2d::Menu::create(showTaskBarButton, nullptr);
    menu->setPosition(cocos2d::Vec2::ZERO); // ���ò˵�λ��Ϊԭ��
    this->addChild(menu); // ���˵���ӵ���ǰ����

    return true; // ��ʼ���ɹ�
}
