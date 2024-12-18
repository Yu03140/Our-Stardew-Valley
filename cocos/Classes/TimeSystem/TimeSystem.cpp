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
    weather="normal";        // ��ʼʱ�����Ǹɺ���

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

   
}

// ��������
void TimeSystem::changeDay() {
    day++;  // ��������
    randomWeather();  // ��������Ƿ��Ǹɺ���

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
void TimeSystem::randomWeather() {
    // ����һ�� 0 �� 99 ֮��������
    int randomValue = rand() % 100;

    if (randomValue < 60) {
        weather = "normal";  // 60% ��������������
    }
    else if (randomValue < 80) {
        weather = "rain";    // 20% ����������
    }
    else {
        weather = "dry";     // 20% �����Ǹɺ�����
    }
}



