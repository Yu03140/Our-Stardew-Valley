#include "Christmas.h"
#include "Global/Global.h"  
#include "cocos2d.h"
#include "Scene/FarmGround.h"

USING_NS_CC;

// ���캯������ʼ����Ա����
ChristmasScene::ChristmasScene()
    : _background(nullptr), _talkBoard(nullptr), _scrollingText(nullptr), _getButton(nullptr),
    _isTextScrolling(false), _scrollingSpeed(0.2f) {}

// ����������������Դ��������ʱ���ֶ������߼���
ChristmasScene::~ChristmasScene() {}

// ����������̬����������ʵ����ʥ����������
ChristmasScene* ChristmasScene::createScene() {
    // ���� ChristmasScene ����
    ChristmasScene* scene = new ChristmasScene();
    if (scene && scene->init()) { // ��ʼ������
        scene->autorelease();     // �����Զ��ͷţ���ֹ�ڴ�й©
        return scene;
    }
    CC_SAFE_DELETE(scene);        // �����ʼ��ʧ�ܣ���ȫ�ͷ��ڴ�
    return nullptr;
}

// ��ʼ����������������������Ԫ�أ��米������ť�ȣ�
bool ChristmasScene::init() {
    // ���ø���ĳ�ʼ��������ȷ������������ʼ���ɹ�
    if (!Scene::init()) {
        return false;
    }

    // ����ʥ������ͼ
    _background = Sprite::create("ChristmasScene.png"); // ���ر���ͼ��Դ
    if (_background) {
        // ���ñ���ͼƬλ��Ϊ��Ļ����
        _background->setPosition(Director::getInstance()->getVisibleSize() / 2);
        _background->setScale(0.8);

        this->addChild(_background); // ��������ӵ���ǰ����
    }

    // ���ضԻ��򱳾�
    _talkBoard = Sprite::create("TalkBoard.png"); // ���ضԻ���ͼƬ��Դ
    if (_talkBoard) {
        // ���öԻ���λ��Ϊ��Ļ�·�
        _talkBoard->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2, _talkBoard->getContentSize().height ));
        _talkBoard->setScale(2.0f);
        this->addChild(_talkBoard); // ���Ի�����ӵ���ǰ����

        // �������ֱ�ǩ����ӵ��Ի���
        _message = "Merry Christmas, Traveller!!!\n1000$ has been gathered for you!"; // ȫ����������
        createFixedText(); // ���÷����������ֱ�ǩ
    }



    // ������ȡ������ť
    _getButton = MenuItemImage::create(
        "GetButton_Normal.png",   // ��ť����״̬��ͼƬ
        "GetButton_Normal.png",   // ��ť����״̬��ͼƬ
        CC_CALLBACK_1(ChristmasScene::onGetRewardClicked, this) // ��ť����¼��ص�
    );
    if (_getButton) {
        // ���ð�ťλ��
        _getButton->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2, _getButton->getContentSize().height/2));
        // �����˵����󣬽���ť����˵�
        auto menu = Menu::create(_getButton, nullptr);
        menu->setPosition(Vec2::ZERO); // ���˵�λ����Ϊ���
        //_talkBoard->setScale(0.5f);
        this->addChild(menu); // ���˵���ӵ�������
    }



    return true; // ��ʼ���ɹ�
}

// ���������ı�
void ChristmasScene::createFixedText() {
    // ʹ��ϵͳ���崴���յ��ı���ǩ
    _scrollingText = Label::createWithSystemFont("", "Arial", 15);
    if (_scrollingText) {
        // ƫ���������Ը������������
        float offsetX = -200.0f;  // X ��ƫ����
        float offsetY = 0.0f; // Y ��ƫ����

        // �������ֱ�ǩλ�ã�������ƫ����
        _scrollingText->setPosition(Vec2(
            _talkBoard->getContentSize().width /32*10,   // X ����
            _talkBoard->getContentSize().height / 2 + offsetY   // Y ����
        ));

        _scrollingText->setColor(Color3B::BLACK); // ����������ɫΪ��ɫ
        _scrollingText->setOpacity(255);         // ������ȫ��͸��

        // �����ֱ�ǩ��Ϊ�ӽڵ���ӵ��Ի��򱳾�
        _talkBoard->addChild(_scrollingText);

        // ����������ʾ�߼�
        schedule([this](float dt) {
            this->updateTextPerCharacter(dt); // ÿ֡������ʾһ���ַ�
            }, 0.1f, "character_display_key"); // ÿ 0.1 �����һ��
    }
}



void ChristmasScene::updateTextPerCharacter(float dt) {
    static size_t index = 0; // ��ǰ��ʾ�����ַ�����
    if (index < _message.length()) {
        // ��ȡ��ǰ�ַ���׷�ӵ����ֱ�ǩ������
        std::string currentText = _scrollingText->getString();
        currentText += _message[index];
        _scrollingText->setString(currentText);

        // ����������׼����ʾ��һ���ַ�
        index++;
    }
    else {
        // ������ʾ��ϣ�ȡ��������
        unschedule("character_display_key");
    }
}


// �����ȡ������ť�Ļص�
void ChristmasScene::onGetRewardClicked(Ref* sender) {
    // ���� Player �������ҵĻ���
    Player* player = Player::getInstance("me"); // ��ȡ��ǰ��ҵ�ʵ��
    player->playerproperty.addMoney(1000);      // Ϊ������� 1000$��������� Player ���Ѿ�ʵ���˻��ҹ���
    goBackToMainScene();                        // ����������
}

// ����������
void ChristmasScene::goBackToMainScene() {
    // ʹ�� Cocos2d-x �� popScene ���������ص�����ջ�е���һ��������������
    cocos2d::Director::getInstance()->popScene();
}


