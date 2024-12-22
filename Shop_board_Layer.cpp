#include "Shop_board_Layer.h"
#include "Global/Global.h"

cocos2d::Scene* Shop_Board_Layer::createScene() {
    auto scene = cocos2d::Scene::create(); // ����һ���³���
    auto layer = Shop_Board_Layer::create();  // ������������
    scene->addChild(layer); // ������������ӵ�������
    return scene; // ���س���
}

bool Shop_Board_Layer::init() {
    if (!Layer::init()) { // ���ø����ʼ������
        return false; // ���ʧ�ܣ��򷵻� false
    }

    // ����������
    auto shop_board = Shop_Board::create([]() {
        });
    // ��������������Ļ����
    auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    shop_board->setAnchorPoint(Vec2(0.5, 0.5));
    shop_board->setPosition(cocos2d::Vec2(visibleSize.width / 2 - visibleSize.width * (0.1), visibleSize.height / 2 - visibleSize.height * (0.05)));
    // ���taskBar�ĸ߶ȺͿ��
    auto shop_boardSize = shop_board->getContentSize();
    CCLOG("shop_boardSize.width = %f, shop_boardSize.height = %f", shop_boardSize.width, shop_boardSize.height);
    shop_board->setVisible(false); // ��ʼ���ɼ�
    shop_board->setScale(4.0);
    this->addChild(shop_board, 2); // ����������ӵ���ǰ����

    // ������ť��������ʾ������
    auto show_shop_board_Button = cocos2d::MenuItemImage::create(
        "shop_button1.png", // ��ť������״̬ͼ��
        "shop_button1.png", // ��ť��ѡ��״̬ͼ��
        [shop_board](Ref* sender) { // ��ť�ص��������������ʾ������
            shop_board->show();
        });
    //?????????????????????????????????????????????????????
    show_shop_board_Button->setScale(1.5);
    show_shop_board_Button->setPosition(cocos2d::Vec2(visibleSize.width * 0.72, visibleSize.height * 0.6)); // ���ð�ťλ��
    CCLOG("show_shop_board_Button->getPosition().x = %f", show_shop_board_Button->getPosition().x);

    // �����˵�������ť��ӵ��˵���
    auto menu = cocos2d::Menu::create(show_shop_board_Button, nullptr);
    menu->setPosition(cocos2d::Vec2::ZERO + Vec2(visibleSize.width * (-0.01), visibleSize.width * (-0.05))); // ���ò˵�λ��Ϊԭ��
    //CCLOG("menu->getPosition().x = %f", menu->getPosition().x);
    menu->setScale(1.5);
    this->addChild(menu, 2); // ���˵���ӵ���ǰ����


    return true; // ��ʼ���ɹ�
}