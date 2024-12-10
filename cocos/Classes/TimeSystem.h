#ifndef __TIMESYSTEM_H__
#define __TIMESYSTEM_H__

#include "cocos2d.h"
#include <string>
#include <cstdlib>
#include <ctime>

USING_NS_CC;

// 宏定义部分
#define SEASON_COUNT 4           // 一年四季
#define MAX_MONTH 12             // 一年有12个月
#define MAX_DAYS_IN_MONTH 30    // 每个月最多30天（简化处理）
#define TIME_SCALE 10            // 时间流速倍率，现实中10分钟=游戏中1天
#define DROUGHT_DAY_PROBABILITY 0.1 // 干旱日的概率，10%的概率会生成干旱日

// TimeSystem类，管理游戏时间的流逝和显示
class TimeSystem : public cocos2d::Node {
public:
    TimeSystem();  // 构造函数
    ~TimeSystem(); // 析构函数

    static TimeSystem* getInstance();  // 获取全局单例实例

    // 更新游戏时间，deltaTime 是每帧的时间
    void update(float deltaTime);

    // 更新屏幕上的标签显示
    void updateDisplay();

    // 获取当前游戏时间相关信息
    int getYear() const { return year; }
    int getMonth() const { return month; }
    int getDay() const { return day; }
    int getHour() const { return hour; }
    bool isDroughtDay() const { return droughtDay; }

private:
    int year;               // 当前年份
    int month;              // 当前月份
    int day;                // 当前日期
    int hour;               // 当前小时
    int currentSeason;      // 当前季节（0：春，1：夏，2：秋，3：冬）
    bool droughtDay;        // 是否是干旱日

    cocos2d::Label* timeLabel;  // 用于显示时间信息的标签
    cocos2d::Label* droughtLabel; // 用于显示干旱日状态的标签

    static TimeSystem* instance;  // 静态成员变量，保存类的唯一实例

    // 改变一天，时间加一
    void changeDay();

    // 改变一个月，月份加一
    void changeMonth();

    // 改变一年，年份加一
    void changeYear();

    // 随机决定是否为干旱日
    void randomDroughtDay();
};

#endif // __TIMESYSTEM_H__
