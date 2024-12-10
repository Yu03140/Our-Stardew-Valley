#include "TimeSystem.h"


USING_NS_CC;

// ��̬��Ա������ʼ��
TimeSystem* TimeSystem::instance = nullptr;

// ���캯������ʼ������ʱ�������Ϣ
TimeSystem::TimeSystem() {
    year = 2024;               // ��ʼ���Ϊ2024��
    month = 1;                 // ��ʼ�·�Ϊ1��
    day = 1;                   // ��ʼ����Ϊ1��
    hour = 0;                  // ��ʼСʱΪ0��
    droughtDay = false;        // ��ʼʱ�����Ǹɺ���
    currentSeason = 0;         // ��ʼ����Ϊ������0��ʾ������

    // ��ʼ��ʱ����ʾ��ǩ
    timeLabel = Label::createWithSystemFont("", "Arial", 24);
    droughtLabel = Label::createWithSystemFont("", "Arial", 24);

    timeLabel->setPosition(Vec2(100, 350));  // ��ǩ��ʾλ��
    droughtLabel->setPosition(Vec2(100, 320));  // �ɺ���״̬��ǩλ��

    this->addChild(timeLabel);  // ��ӵ�����
    this->addChild(droughtLabel); // ��ӵ�����

    // ÿ֡����һ�� update() ����������Ϸʱ��
    schedule([this](float deltaTime) { update(deltaTime); }, "update_key");
}

// ��������
TimeSystem::~TimeSystem() {
    // �˴�����������Դ��ʵ�������ﲢ����Ҫ����������
}

// ��ȡȫ��ʵ�������������򴴽�
TimeSystem* TimeSystem::getInstance() {
    if (instance == nullptr) {
        instance = new TimeSystem();
        Director::getInstance()->getRunningScene()->addChild(instance); // ��ʵ����ӵ���ǰ������
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

// �ı�һ��
void TimeSystem::changeDay() {
    day++;  // ��������
    randomDroughtDay();  // ��������Ƿ��Ǹɺ���

    // ������ڳ�����һ���µ��������������Ϊ1�����ı��·�
    if (day > MAX_DAYS_IN_MONTH) {
        day = 1;
        changeMonth();
    }
}

// �ı��·�
void TimeSystem::changeMonth() {
    month++;  // �·�����
    if (month > MAX_MONTH) {  // ����·ݴ���12������Ϊ1���ı����
        month = 1;
        changeYear();
    }
}

// �ı����
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
    // ������ʾ��ʱ���ַ���
    std::string timeText = "Year: " + std::to_string(year) + "\n";
    timeText += "Month: " + std::to_string(month) + "\n";
    timeText += "Day: " + std::to_string(day) + "\n";
    timeText += "Hour: " + std::to_string(hour) + "\n";

    // ����ʱ���ǩ������
    timeLabel->setString(timeText);

    // ������ʾ�ɺ���״̬���ַ���
    std::string droughtText = "Drought Day: " + std::string(droughtDay ? "Yes" : "No");

    // ���¸ɺ��ձ�ǩ������
    droughtLabel->setString(droughtText);
}
