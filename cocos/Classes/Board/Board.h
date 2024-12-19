#pragma once
#ifndef __BOARD_H__
#define __BOARD_H__

#include "cocos2d.h"

class Board : public cocos2d::Layer {
public:
    static Board* createBoard(const std::string& weather, int money, int experience);
    virtual bool init(const std::string& weather, int money, int experience);

    void updateWeather(const std::string& weather);  // ��������
    void updateTimeLabel(float dt);
    void updateMoneyLabel();
    void updateExperienceLabel();

private:
    // ˽�г�Ա����
    cocos2d::Sprite* background;        // ����ͼƬ
    cocos2d::Sprite* weatherSprite;     // ����ͼƬ
    cocos2d::Label* moneyLabel;         // ��ʾ���Ǯ�Ƶı�ǩ
    cocos2d::Label* timeLabel;          // ��ʾ������ʱ��ı�ǩ
    cocos2d::Label* experienceLabel;    //��ʾ��Ҿ���ֵ�ı�ǩ

    // ���ߺ���
    void setWeatherSprite(const std::string& weather);

};

#endif // __BOARD_H__

