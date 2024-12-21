#include "Global/Global.h"

USING_NS_CC;

// ���� Board ����
Board* Board::createBoard(const std::string& weather, int money, int experience) {
    Board* ret = new (std::nothrow) Board();
    if (ret && ret->init(weather, money, experience)) {
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
    background = Sprite::create("Board.png");
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto mapSize = background->getContentSize();
    float X = visibleSize.width / 1.7 - mapSize.width / 4 * 3;
    float Y = visibleSize.height / 1.7 - mapSize.height / 4 * 3;
	CCLOG("X: %f, Y: %f", X, Y);
    background->setPosition(X, Y);
    this->addChild(background);

    // 2. �������ͼƬ
    weatherSprite = Sprite::create();
    this->addChild(weatherSprite);
    setWeatherSprite(weather);  // ���ó�ʼ����ͼƬ
    weatherSprite->setPosition(background->getPosition()+ Vec2(background->getContentSize().height /16, background->getContentSize().height / 8));

    // 3. ������Ǯ�Ʊ�ǩ�������·���
    moneyLabel = Label::createWithTTF(std::to_string(player->playerproperty.getMoney()), "fonts/arial.ttf", 12);
    moneyLabel->setPosition(background->getPosition() - Vec2(0, background->getContentSize().height /8*3));
    moneyLabel->setColor(Color3B::BLACK);
    moneyLabel->setScale(0.5);
    this->addChild(moneyLabel);
    // ÿ�����һ��Ǯ�Ʊ�ǩ
    schedule([this](float dt) {
        // ÿ�����һ��Ǯ�Ʊ�ǩ
        this->updateMoneyLabel();
        }, 1.0f, "money_update_key");


    // 4. ���ʱ���ǩ�������Ϸ���
    timeLabel = Label::createWithTTF("", "fonts/arial.ttf", 12);
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
    experienceLabel = Label::createWithTTF("Exp: " + std::to_string(player->playerproperty.getExperience()), "fonts/arial.ttf", 11);
    experienceLabel->setPosition(background->getPosition() + Vec2(10- background->getContentSize().height / 8, background->getContentSize().height / 8*3-2.5));
    experienceLabel->setColor(Color3B::BLACK);
    experienceLabel->setScale(0.4);
    this->addChild(experienceLabel);
    // ÿ�����һ�ξ����ǩ
    schedule([this](float dt) {
        this->updateExperienceLabel();
        }, 1.0f, "experience_update_key");



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


// �������Ǯ�Ʊ�ǩ
void Board::updateMoneyLabel() {
    //�����ʼ��
    Player* player = Player::getInstance("me");
    // ���� moneyLabel ���ı�
    moneyLabel->setString( std::to_string(player->playerproperty.getMoney()));
}


// ������Ҿ����ǩ
void Board::updateExperienceLabel() {
    //�����ʼ��
    Player* player = Player::getInstance("me");
    // ���� moneyLabel ���ı�
    experienceLabel->setString("Exp: " + std::to_string(player->playerproperty.getExperience()));
}