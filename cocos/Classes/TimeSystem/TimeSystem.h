#ifndef __TIMESYSTEM_H__
#define __TIMESYSTEM_H__

#include "cocos2d.h"
#include <string>
#include <cstdlib>
#include <ctime>


USING_NS_CC;

// 宏定义部分
#define SEASON_COUNT 4          // 一年四季
#define MAX_DAYS_IN_MONTH 30    // 每个季节最多30天（简化处理）
#define TIME_SCALE 1.0/10.0     // 时间流速倍率，现实中30s=游戏中1小时
#define DROUGHT_DAY_PROBABILITY 0.1 // 干旱日的概率，10%的概率会生成干旱日
#define SPRING 1
#define SUMMER 2
#define AUTUMN 3
#define WINTER 4


// TimeSystem类，管理游戏时间的流逝和显示
class TimeSystem : public cocos2d::Node {
public:
    TimeSystem();  
    ~TimeSystem(); 

    static TimeSystem* getInstance();  // 获取全局单例实例

    // 更新游戏时间，deltaTime 是每帧的时间
    void update(float deltaTime);

    // 更新屏幕上的标签显示
    void updateDisplay();

    // 获取当前游戏时间相关信息
    int getYear() const { return year; }
    int getSeason() const { return season; }
    int getDay() const { return day; }
    int getHour() const { return hour; }
    bool isDroughtDay() const { return droughtDay; }

private:
    int year;               // 当前年份
    int day;                // 当前日期
    int hour;               // 当前小时
    int season;             // 当前季节（春1，夏2，秋3，冬4）
    bool droughtDay;        // 是否是干旱日

    cocos2d::Label* timeLabel;  // 用于显示时间信息的标签
    cocos2d::Label* droughtLabel; // 用于显示干旱日状态的标签

    static TimeSystem* instance;  // 静态成员变量，保存类的唯一实例

    // 改变一天，时间加一
    void changeDay();

    // 改变一个月，月份加一
    void changeSeason();

    // 改变一年，年份加一
    void changeYear();

    // 随机决定是否为干旱日
    void randomDroughtDay();
};

#endif // __TIMESYSTEM_H__
