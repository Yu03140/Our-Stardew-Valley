#include "Shop_board.h"
#include "Charactor/BackpackLayer.h"
#include "Global/Global.h"
//#include "UI_Scene.h"

// ������������������������NPC���ֺ��������Ļص�������Ϊ����
Shop_Board* Shop_Board::create(std::function<void()> Shop_BoardCallback) {
    Shop_Board* shop_Board = new (std::nothrow) Shop_Board();
    if (shop_Board && shop_Board->init(Shop_BoardCallback)) {
        shop_Board->autorelease(); // �Զ��ͷ��ڴ�
        return shop_Board;
    }
    delete shop_Board; // �����ʼ��ʧ�ܣ��ͷ��ڴ�
    return nullptr;
}

// ��ʼ������������
// ����������������NPC���֡��������Ļص�����
bool Shop_Board::init(std::function<void()>Shop_BoardCallback) {
    if (!Node::init()) { // ���ø����ʼ������
        return false;
    }

    //this->taskDescription = taskDescription; // ������������
    //this->npcName = npcName; // ����NPC����
    this->isOpen = false; // ��ʼ������δ���״̬
    this->Shop_BoardCallback = Shop_BoardCallback; // �����������ص�����

    // ��������������ͼƬ
    auto background = cocos2d::Sprite::create("shop_board.png");
    background->setScale(0.3);
    this->addChild(background); // ��ӵ��ڵ���

    // ��������������ǩ
   //descriptionLabel = cocos2d::Label::createWithSystemFont("Ten dollar each\nout-of-season items are marked up by 20%", "Arial", 24);

    descriptionLabel = cocos2d::Label::createWithTTF("Ten dollar each\nout-of-season items are marked up by 20%", "fonts/Marker Felt.ttf", 20);
    // ����������ɫΪ��ɫ
    descriptionLabel->setTextColor(cocos2d::Color4B::BLACK);

    descriptionLabel->setPosition(cocos2d::Vec2(background->getContentSize().width / 3*2,background->getContentSize().height / 3 ));
    descriptionLabel->setLocalZOrder(10); // ���ñ�ǩ�� Z-order ���ڱ���
    background->addChild(descriptionLabel); // ����ǩ��ӵ�����

    //������Ʒ1 ��ݮ����
    item_strawberry = cocos2d::MenuItemImage::create(
        "strawberry.png", "strawberry.png",
        CC_CALLBACK_0(Shop_Board::buyitem_strawberry, this)); // ���ð�ť�ص�����
    item_strawberry->setScale(5);
    item_strawberry->setPosition(cocos2d::Vec2(background->getContentSize().width / 10,
        background->getContentSize().height / 6*5));




    // �������رա���ť
    closeButton = cocos2d::MenuItemImage::create(
        "XforTaskBar.png", "XforTaskBar.png",
        CC_CALLBACK_0(Shop_Board::onClose, this)); // ���ð�ť�ص�����
    closeButton->setPosition(cocos2d::Vec2(background->getContentSize().width - 30,
        background->getContentSize().height - 30)); // ���ð�ťλ��

    // �����˵�����Ӱ�ť
    auto menu = cocos2d::Menu::create(item_strawberry,closeButton, nullptr);
    menu->setPosition(cocos2d::Vec2::ZERO); // ���ò˵�λ��
    background->addChild(menu); // ���˵���ӵ�����

    return true;
}

// ����Ʒ1������ݮ���ӵĻص�����
 void Shop_Board::buyitem_strawberry() {
     Player* player = Player::getInstance("me");
    if (isOpen==1 && player->playerproperty.getMoney()>10) { // �������δ���
        player->playerproperty.addExperience(50);
        //player->playerproperty.addReputation(50);
        player->playerproperty.addMoney(-10);
        backpackLayer->removeItem("strawberry", -1);
        cocos2d::log("��ҲƲ��Ѹ��£�");
        if (Shop_BoardCallback) {
            Shop_BoardCallback(); // ִ���������Ļص�����

        }
        //descriptionLabel->setString("Done!"); // ������������Ϊ��������ɣ���
    } 
 }




// ���رա���ť�Ļص�����
void Shop_Board::onClose() {
    isOpen = 1;
    this->hide(); // ����������
}

// ��ʾ������
void Shop_Board::show() {
    isOpen = 1;
    this->setVisible(true);
}

// ����������
void Shop_Board::hide() {
    isOpen = 0;
    this->setVisible(false);
}