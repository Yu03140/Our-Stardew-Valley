#include "Global/Global.h"

USING_NS_CC;

// ���� Board ����
Board* Board::createBoard(const std::string& weather, int money, int experience) {
    Board* ret = new (std::nothrow) Board();
    if (ret && ret->init(weather, money,experience)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

// ��ʼ������
bool Board::init(const std::string& weather, int money, int experience) {
    if (!Layer::init()) {
        return false;
    }





    //�����ʼ��
    Player* player = Player::getInstance("me");


    // 1. ��ӱ���ͼƬ
    background = Sprite::create("Board.png");

    // ��ȡ��Ļ�ɼ��ߴ�
    //cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

    // ��������������Ļ�����Ͻ�
    //background->setAnchorPoint(cocos2d::Vec2(0, 1));  // ê������Ϊ���Ͻ� (0, 1)
    //background->setPosition(cocos2d::Vec2(500, 2000));  // ���Ͻ�����
    //background->setPosition(Vec2(10, Director::getInstance()->getVisibleSize().height - 10));
    //background->setAnchorPoint(Vec2(0, 1));  // ����ê��Ϊ���Ͻ�
    //background->setPosition(Vec2(10, Director::getInstance()->getVisibleSize().height));
    background->setPosition(Director::getInstance()->getVisibleSize() / 2);
    this->addChild(background);

    // 2. �������ͼƬ
    weatherSprite = Sprite::create();
    this->addChild(weatherSprite);
    setWeatherSprite(weather);  // ���ó�ʼ����ͼƬ
    weatherSprite->setPosition(background->getPosition() + Vec2(0, 10));

    // 3. ������Ǯ�Ʊ�ǩ�������·���
    moneyLabel = Label::createWithTTF("Money: " + std::to_string(player->playerproperty.getMoney()), "fonts/arial.ttf", 24);
    moneyLabel->setPosition(background->getPosition() - Vec2(0, background->getContentSize().height / 2-10));
    moneyLabel->setColor(Color3B::BLACK);
    moneyLabel->setScale(0.5);
    this->addChild(moneyLabel);



    // 4. ���ʱ���ǩ�������Ϸ���
    timeLabel = Label::createWithTTF("", "fonts/arial.ttf", 24);
    // timeLabel = Label::createWithTTF(std::to_string(timeSystem->getYear())+"-"+ std::to_string(timeSystem->getSeason()) + "-" + std::to_string(timeSystem->getDay()) + "-" + std::to_string(timeSystem->getHour()), "fonts/arial.ttf", 24);
    timeLabel->setPosition(background->getPosition() + Vec2(8, -3));
    timeLabel->setColor(Color3B::BLACK);
    timeLabel->setScale(0.4);
    this->addChild(timeLabel);

    // ���ø���ʱ��ĵ��ȣ�ÿ�����һ��
    schedule([this](float dt) {
        this->updateTimeLabel(dt);
        }, 1.0f, "time_update_key");

    //4.5 ��Ӿ���ֵ��ǩ
    experienceLabel = Label::createWithTTF("Experience: " + std::to_string(player->playerproperty.getExperience()), "fonts/arial.ttf", 24);
    experienceLabel->setPosition(background->getPosition() + Vec2(10, background->getContentSize().height / 2-10));
    experienceLabel->setColor(Color3B::BLACK);
    experienceLabel->setScale(0.4);
    this->addChild(experienceLabel);



    return true;
}

void Board::updateTimeLabel(float dt) {
   // _timeSystem->updateTime();  // ������Ϸ�ڵ�ʱ��
    std::string timeStr = std::to_string(timeSystem->getYear()) + "-" +
        std::to_string(timeSystem->getSeason()) + "-" +
        std::to_string(timeSystem->getDay()) + "-" +
        std::to_string(timeSystem->getHour());
    timeLabel->setString(timeStr);  // ���±�ǩ��ʾ
}



// ��������
void Board::updateWeather(const std::string& weather) {
    setWeatherSprite(weather);
}

// ��������ͼƬ
void Board::setWeatherSprite(const std::string& weather) {
    std::string imagePath;
    if (weather == "normal") {
        imagePath = "normal.png";
    }
    else if (weather == "dry") {
        imagePath = "dry.png";
    }
    else if (weather == "rain") {
        imagePath = "rain.png";
    }
    else {
        return;
    }

    weatherSprite->setTexture(imagePath);
}

// �������Ǯ��
void Board::updateMoney(int money) {
    moneyLabel->setString("Money: " + std::to_string(money));
}


