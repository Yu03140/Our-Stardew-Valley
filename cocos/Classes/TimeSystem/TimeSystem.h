#ifndef __TIMESYSTEM_H__
#define __TIMESYSTEM_H__

#include "cocos2d.h"
#include <string>
#include <cstdlib>
#include <ctime>


USING_NS_CC;

// �궨�岿��
#define SEASON_COUNT 4          // һ���ļ�
#define MAX_DAYS_IN_MONTH 30    // ÿ���������30�죨�򻯴���
#define TIME_SCALE 1.0/10.0     // ʱ�����ٱ��ʣ���ʵ��30s=��Ϸ��1Сʱ
#define DROUGHT_DAY_PROBABILITY 0.1 // �ɺ��յĸ��ʣ�10%�ĸ��ʻ����ɸɺ���
#define SPRING 1
#define SUMMER 2
#define AUTUMN 3
#define WINTER 4


// TimeSystem�࣬������Ϸʱ������ź���ʾ
class TimeSystem : public cocos2d::Node {
public:
    TimeSystem();  
    ~TimeSystem(); 

    static TimeSystem* getInstance();  // ��ȡȫ�ֵ���ʵ��

    // ������Ϸʱ�䣬deltaTime ��ÿ֡��ʱ��
    void update(float deltaTime);

    // ������Ļ�ϵı�ǩ��ʾ
    void updateDisplay();

    // ��ȡ��ǰ��Ϸʱ�������Ϣ
    int getYear() const { return year; }
    int getSeason() const { return season; }
    int getDay() const { return day; }
    int getHour() const { return hour; }
    bool isDroughtDay() const { return droughtDay; }

private:
    int year;               // ��ǰ���
    int day;                // ��ǰ����
    int hour;               // ��ǰСʱ
    int season;             // ��ǰ���ڣ���1����2����3����4��
    bool droughtDay;        // �Ƿ��Ǹɺ���

    cocos2d::Label* timeLabel;  // ������ʾʱ����Ϣ�ı�ǩ
    cocos2d::Label* droughtLabel; // ������ʾ�ɺ���״̬�ı�ǩ

    static TimeSystem* instance;  // ��̬��Ա�������������Ψһʵ��

    // �ı�һ�죬ʱ���һ
    void changeDay();

    // �ı�һ���£��·ݼ�һ
    void changeSeason();

    // �ı�һ�꣬��ݼ�һ
    void changeYear();

    // ��������Ƿ�Ϊ�ɺ���
    void randomDroughtDay();
};

#endif // __TIMESYSTEM_H__
