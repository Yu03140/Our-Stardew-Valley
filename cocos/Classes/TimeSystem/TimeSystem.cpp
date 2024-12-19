#include "TimeSystem.h"

USING_NS_CC;

// ��̬��Ա������ʼ��
TimeSystem* TimeSystem::instance = nullptr;

// ���캯������ʼ������ʱ�������Ϣ
TimeSystem::TimeSystem() {
    year = 2024;               // ��ʼ���Ϊ2024��
    day = 1;                   // ��ʼ����Ϊ1��
    hour = 0;                  // ��ʼСʱΪ0��
    season = 1;                // ��ʼ����Ϊ������1��ʾ������
    droughtDay = false;        // ��ʼʱ�����Ǹɺ���

    
    // ��ʼ��ʱ����ʾ��ǩ
    timeLabel = Label::createWithSystemFont("", "Arial", 30);
    droughtLabel = Label::createWithSystemFont("", "Arial", 30);

    timeLabel->setPosition(Vec2(2400, 1450));  // ��ǩ��ʾλ��
    droughtLabel->setPosition(Vec2(2400, 1380));  // �ɺ���״̬��ǩλ��

    timeLabel->setMaxLineWidth(500);  // ���������
    droughtLabel->setMaxLineWidth(500);  // ���������

    timeLabel->setTextColor(Color4B::BLACK);
    droughtLabel->setTextColor(Color4B::BLACK);
    

    this->addChild(timeLabel,2);  // ��ӵ�����
    this->addChild(droughtLabel,2); // ��ӵ�����

    Node::onEnter();
    schedule([this](float deltaTime) {
        update(deltaTime);
        }, 10.0f, "update_key");  // ����ÿ 5 �����һ�� update
    this->scheduleUpdate();



}

// ��������
TimeSystem::~TimeSystem() {
    // �˴�����������Դ��ʵ�������ﲢ����Ҫ����������
}

// ��ȡȫ��ʵ�������������򴴽�
TimeSystem* TimeSystem::getInstance() {
    if (instance == nullptr) {
        instance = new TimeSystem();
    }

    // ȷ�� TimeSystem ʵ������ӵ���ǰ���еĳ���
    auto currentScene = Director::getInstance()->getRunningScene();
    if (instance->getParent() != currentScene) {
        currentScene->addChild(instance);
    }

    return instance;
}


// ������Ϸʱ��
void TimeSystem::update(float deltaTime) {

    // ����deltaTime��TIME_SCALE������Сʱ
    hour += (deltaTime * TIME_SCALE);

    // ���Сʱ������24������һ���������������
    if (hour >= 24) {
        hour -= 24;  // ����Сʱ��
        changeDay();  // �ı�һ��
    }
   
    // ������Ļ�ϵ�ʱ����ʾ
    updateDisplay(); 
   
}

// ��������
void TimeSystem::changeDay() {
    day++;  // ��������
    randomDroughtDay();  // ��������Ƿ��Ǹɺ���

    // ������ڳ�����һ���µ��������������Ϊ1�����ı��·�
    if (day > MAX_DAYS_IN_MONTH) {
        day = 1;
        changeSeason();
    }
}

// ���ڸ���
void TimeSystem::changeSeason() {
    season++;  // �·�����
    if (season > SEASON_COUNT) {  // ������ڴ���4������Ϊ1���ı����
        season = 1;
        changeYear();
    }
}

// ��ݸ���
void TimeSystem::changeYear() {
    year++;  // �������
}

// ��������Ƿ��Ǹɺ��գ�ʹ��DROUGHT_DAY_PROBABILITY�ĸ���
void TimeSystem::randomDroughtDay() {
    if ((rand() % 100) < (DROUGHT_DAY_PROBABILITY * 100)) {
        droughtDay = true;  // ������ʷ��ϣ�����Ϊ�ɺ���
    }
    else {
        droughtDay = false;  // ��������Ϊ�Ǹɺ���
    }
}

// ������ʾ��ʱ����Ϣ
void TimeSystem::updateDisplay() {
    //log("TimeSystemDisplay"); // ������־

    // ������ʾ��ʱ���ַ���
    std::string timeText = "Year: " + std::to_string(year) + "\n";
    timeText += "Season: " + std::to_string(season) + "\n";
    timeText += "Day: " + std::to_string(day) + "\n";
    timeText += "Hour: " + std::to_string(hour) + "\n";

    // �������е� timeLabel ����
    timeLabel->setString(timeText);

    // ������ʾ�ɺ���״̬���ַ���
    std::string droughtText = "Drought Day: " + std::string(droughtDay ? "Yes" : "No");
    //log("TimeLabel Updated: %s", timeText.c_str()); // ������־

    // ���¸ɺ��ձ�ǩ������
    droughtLabel->setString(droughtText);

    //log("TimeLabel Position: x = %f, y = %f", timeLabel->getPositionX(), timeLabel->getPositionY());
}

