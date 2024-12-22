#include "Christmas.h"
#include "Global/Global.h"  
#include "cocos2d.h"
#include "Scene/FarmGround.h"

USING_NS_CC;


ChristmasScene::ChristmasScene()
    : _background(nullptr), _talkBoard(nullptr), _scrollingText(nullptr), _getButton(nullptr),
    _isTextScrolling(false), _scrollingSpeed(0.2f) {}

ChristmasScene::~ChristmasScene() {}

// ����������̬����������ʵ����ʥ����������
ChristmasScene* ChristmasScene::createScene() {
    // ���� ChristmasScene ����
    ChristmasScene* scene = new ChristmasScene();
    if (scene && scene->init()) { // ��ʼ������
        scene->autorelease();     
        return scene;
    }
    CC_SAFE_DELETE(scene);        // �����ʼ��ʧ�ܣ���ȫ�ͷ��ڴ�
    return nullptr;
}

// ��ʼ��
bool ChristmasScene::init() {
 
    if (!Scene::init()) {
        return false;
    }

    // ����ʥ������ͼ
    _background = Sprite::create("ChristmasScene.png"); // ���ر���ͼ��Դ
    if (_background) {
        _background->setPosition(Director::getInstance()->getVisibleSize() / 2);
        _background->setScale(0.8);

        this->addChild(_background); // ��������ӵ���ǰ����
    }

    // ���ضԻ��򱳾�
    _talkBoard = Sprite::create("TalkBoard.png");
    if (_talkBoard) {
        _talkBoard->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2, _talkBoard->getContentSize().height ));
        _talkBoard->setScale(2.0f);
        this->addChild(_talkBoard); 

        // �������ֱ�ǩ����ӵ��Ի���
        _message = "Merry Christmas, Traveller!!!\n1000$ has been gathered for you!"; 
        createFixedText();
    }

    // ������ȡ������ť
    _getButton = MenuItemImage::create(
        "GetButton_Normal.png",   // ��ť����״̬��ͼƬ
        "GetButton_Normal.png",   // ��ť����״̬��ͼƬ
        CC_CALLBACK_1(ChristmasScene::onGetRewardClicked, this) // ��ť����¼��ص�
    );
    if (_getButton) {
        _getButton->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2, _getButton->getContentSize().height/2));
        // �����˵����󣬽���ť����˵�
        auto menu = Menu::create(_getButton, nullptr);
        menu->setPosition(Vec2::ZERO); // ���˵�λ����Ϊ���
        this->addChild(menu); 
    }

    return true; // ��ʼ���ɹ�
}

// ���������ı�
void ChristmasScene::createFixedText() {
    // ʹ��ϵͳ���崴���յ��ı���ǩ
    _scrollingText = Label::createWithSystemFont("", "Arial", 15);
    if (_scrollingText) {
        float offsetX = -200.0f;  
        float offsetY = 0.0f;

        // �������ֱ�ǩλ�ã�������ƫ����
        _scrollingText->setPosition(Vec2(
            _talkBoard->getContentSize().width /32*10,   
            _talkBoard->getContentSize().height / 2 + offsetY  
        ));

        _scrollingText->setColor(Color3B::BLACK); 
        _scrollingText->setOpacity(255);         

        // �����ֱ�ǩ��Ϊ�ӽڵ���ӵ��Ի��򱳾�
        _talkBoard->addChild(_scrollingText);

        // ����������ʾ�߼�
        schedule([this](float dt) {
            this->updateTextPerCharacter(dt); // ÿ֡������ʾһ���ַ�
            }, 0.1f, "character_display_key"); // ÿ 0.1 �����һ��
    }
}



void ChristmasScene::updateTextPerCharacter(float dt) {
    static size_t index = 0; 
    if (index < _message.length()) {
        // ��ȡ��ǰ�ַ���׷�ӵ����ֱ�ǩ������
        std::string currentText = _scrollingText->getString();
        currentText += _message[index];
        _scrollingText->setString(currentText);

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
    player->playerproperty.addMoney(1000);      // Ϊ������� 1000$
    goBackToMainScene();                       
}

// ����������
void ChristmasScene::goBackToMainScene() {
    cocos2d::Director::getInstance()->popScene();
}


