#include "Global/Global.h"

USING_NS_CC;

// 创建 Board 对象
Board* Board::createBoard(const std::string& weather, int money, int experience) {
    Board* ret = new (std::nothrow) Board();
    if (ret && ret->init(weather, money,experience)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

// 初始化函数
bool Board::init(const std::string& weather, int money, int experience) {
    if (!Layer::init()) {
        return false;
    }





    //人物初始化
    Player* player = Player::getInstance("me");


    // 1. 添加背景图片
    background = Sprite::create("Board.png");

    // 获取屏幕可见尺寸
    //cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

    // 将背景放置在屏幕的左上角
    //background->setAnchorPoint(cocos2d::Vec2(0, 1));  // 锚点设置为左上角 (0, 1)
    //background->setPosition(cocos2d::Vec2(500, 2000));  // 左上角坐标
    //background->setPosition(Vec2(10, Director::getInstance()->getVisibleSize().height - 10));
    //background->setAnchorPoint(Vec2(0, 1));  // 设置锚点为左上角
    //background->setPosition(Vec2(10, Director::getInstance()->getVisibleSize().height));
    background->setPosition(Director::getInstance()->getVisibleSize() / 2);
    this->addChild(background);

    // 2. 添加天气图片
    weatherSprite = Sprite::create();
    this->addChild(weatherSprite);
    setWeatherSprite(weather);  // 设置初始天气图片
    weatherSprite->setPosition(background->getPosition() + Vec2(0, 10));

    // 3. 添加玩家钱财标签（背景下方）
    moneyLabel = Label::createWithTTF("Money: " + std::to_string(player->playerproperty.getMoney()), "fonts/arial.ttf", 24);
    moneyLabel->setPosition(background->getPosition() - Vec2(0, background->getContentSize().height / 2-10));
    moneyLabel->setColor(Color3B::BLACK);
    moneyLabel->setScale(0.5);
    this->addChild(moneyLabel);



    // 4. 添加时间标签（背景上方）
    timeLabel = Label::createWithTTF("", "fonts/arial.ttf", 24);
    // timeLabel = Label::createWithTTF(std::to_string(timeSystem->getYear())+"-"+ std::to_string(timeSystem->getSeason()) + "-" + std::to_string(timeSystem->getDay()) + "-" + std::to_string(timeSystem->getHour()), "fonts/arial.ttf", 24);
    timeLabel->setPosition(background->getPosition() + Vec2(8, -3));
    timeLabel->setColor(Color3B::BLACK);
    timeLabel->setScale(0.4);
    this->addChild(timeLabel);

    // 设置更新时间的调度，每秒调用一次
    schedule([this](float dt) {
        this->updateTimeLabel(dt);
        }, 1.0f, "time_update_key");

    //4.5 添加经验值标签
    experienceLabel = Label::createWithTTF("Experience: " + std::to_string(player->playerproperty.getExperience()), "fonts/arial.ttf", 24);
    experienceLabel->setPosition(background->getPosition() + Vec2(10, background->getContentSize().height / 2-10));
    experienceLabel->setColor(Color3B::BLACK);
    experienceLabel->setScale(0.4);
    this->addChild(experienceLabel);



    return true;
}

void Board::updateTimeLabel(float dt) {
   // _timeSystem->updateTime();  // 更新游戏内的时间
    std::string timeStr = std::to_string(timeSystem->getYear()) + "-" +
        std::to_string(timeSystem->getSeason()) + "-" +
        std::to_string(timeSystem->getDay()) + "-" +
        std::to_string(timeSystem->getHour());
    timeLabel->setString(timeStr);  // 更新标签显示
}



// 更新天气
void Board::updateWeather(const std::string& weather) {
    setWeatherSprite(weather);
}

// 设置天气图片
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

// 更新玩家钱财
void Board::updateMoney(int money) {
    moneyLabel->setString("Money: " + std::to_string(money));
}


