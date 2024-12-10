#ifndef __TIMESYSTEM_H__
#define __TIMESYSTEM_H__

#include "cocos2d.h"
#include <string>
#include <cstdlib>
#include <ctime>

USING_NS_CC;

// �궨�岿��
#define SEASON_COUNT 4           // һ���ļ�
#define MAX_MONTH 12             // һ����12����
#define MAX_DAYS_IN_MONTH 30    // ÿ�������30�죨�򻯴���
#define TIME_SCALE 10            // ʱ�����ٱ��ʣ���ʵ��10����=��Ϸ��1��
#define DROUGHT_DAY_PROBABILITY 0.1 // �ɺ��յĸ��ʣ�10%�ĸ��ʻ����ɸɺ���

// TimeSystem�࣬������Ϸʱ������ź���ʾ
class TimeSystem : public cocos2d::Node {
public:
    TimeSystem();  // ���캯��
    ~TimeSystem(); // ��������

    static TimeSystem* getInstance();  // ��ȡȫ�ֵ���ʵ��

    // ������Ϸʱ�䣬deltaTime ��ÿ֡��ʱ��
    void update(float deltaTime);

    // ������Ļ�ϵı�ǩ��ʾ
    void updateDisplay();

    // ��ȡ��ǰ��Ϸʱ�������Ϣ
    int getYear() const { return year; }
    int getMonth() const { return month; }
    int getDay() const { return day; }
    int getHour() const { return hour; }
    bool isDroughtDay() const { return droughtDay; }

private:
    int year;               // ��ǰ���
    int month;              // ��ǰ�·�
    int day;                // ��ǰ����
    int hour;               // ��ǰСʱ
    int currentSeason;      // ��ǰ���ڣ�0������1���ģ�2���3������
    bool droughtDay;        // �Ƿ��Ǹɺ���

    cocos2d::Label* timeLabel;  // ������ʾʱ����Ϣ�ı�ǩ
    cocos2d::Label* droughtLabel; // ������ʾ�ɺ���״̬�ı�ǩ

    static TimeSystem* instance;  // ��̬��Ա�������������Ψһʵ��

    // �ı�һ�죬ʱ���һ
    void changeDay();

    // �ı�һ���£��·ݼ�һ
    void changeMonth();

    // �ı�һ�꣬��ݼ�һ
    void changeYear();

    // ��������Ƿ�Ϊ�ɺ���
    void randomDroughtDay();
};

#endif // __TIMESYSTEM_H__
