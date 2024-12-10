#include "TimeSystem.h"


USING_NS_CC;

// 静态成员变量初始化
TimeSystem* TimeSystem::instance = nullptr;

// 构造函数，初始化所有时间相关信息
TimeSystem::TimeSystem() {
    year = 2024;               // 初始年份为2024年
    month = 1;                 // 初始月份为1月
    day = 1;                   // 初始日期为1日
    hour = 0;                  // 初始小时为0点
    droughtDay = false;        // 初始时，不是干旱日
    currentSeason = 0;         // 初始季节为春季（0表示春季）

    // 初始化时间显示标签
    timeLabel = Label::createWithSystemFont("", "Arial", 24);
    droughtLabel = Label::createWithSystemFont("", "Arial", 24);

    timeLabel->setPosition(Vec2(100, 350));  // 标签显示位置
    droughtLabel->setPosition(Vec2(100, 320));  // 干旱日状态标签位置

    this->addChild(timeLabel);  // 添加到场景
    this->addChild(droughtLabel); // 添加到场景

    // 每帧调用一次 update() 方法更新游戏时间
    schedule([this](float deltaTime) { update(deltaTime); }, "update_key");
}

// 析构函数
TimeSystem::~TimeSystem() {
    // 此处可以清理资源，实际中这里并不需要做额外清理
}

// 获取全局实例，若不存在则创建
TimeSystem* TimeSystem::getInstance() {
    if (instance == nullptr) {
        instance = new TimeSystem();
        Director::getInstance()->getRunningScene()->addChild(instance); // 将实例添加到当前场景中
    }
    return instance;
}

// 更新游戏时间
void TimeSystem::update(float deltaTime) {
    // 根据deltaTime和TIME_SCALE来增加小时
    hour += (deltaTime * TIME_SCALE);

    // 如果小时数超过24，代表一天结束，更新日期
    if (hour >= 24) {
        hour -= 24;  // 重置小时数
        changeDay();  // 改变一天
    }

    // 更新屏幕上的时间显示
    updateDisplay();
}

// 改变一天
void TimeSystem::changeDay() {
    day++;  // 日期增加
    randomDroughtDay();  // 随机决定是否是干旱日

    // 如果日期超过了一个月的最大天数，重置为1，并改变月份
    if (day > MAX_DAYS_IN_MONTH) {
        day = 1;
        changeMonth();
    }
}

// 改变月份
void TimeSystem::changeMonth() {
    month++;  // 月份增加
    if (month > MAX_MONTH) {  // 如果月份大于12，重置为1，改变年份
        month = 1;
        changeYear();
    }
}

// 改变年份
void TimeSystem::changeYear() {
    year++;  // 年份增加
}

// 随机决定是否是干旱日，使用DROUGHT_DAY_PROBABILITY的概率
void TimeSystem::randomDroughtDay() {
    if ((rand() % 100) < (DROUGHT_DAY_PROBABILITY * 100)) {
        droughtDay = true;  // 如果概率符合，设置为干旱日
    }
    else {
        droughtDay = false;  // 否则，设置为非干旱日
    }
}

// 更新显示的时间信息
void TimeSystem::updateDisplay() {
    // 创建显示的时间字符串
    std::string timeText = "Year: " + std::to_string(year) + "\n";
    timeText += "Month: " + std::to_string(month) + "\n";
    timeText += "Day: " + std::to_string(day) + "\n";
    timeText += "Hour: " + std::to_string(hour) + "\n";

    // 更新时间标签的内容
    timeLabel->setString(timeText);

    // 创建显示干旱日状态的字符串
    std::string droughtText = "Drought Day: " + std::string(droughtDay ? "Yes" : "No");

    // 更新干旱日标签的内容
    droughtLabel->setString(droughtText);
}
