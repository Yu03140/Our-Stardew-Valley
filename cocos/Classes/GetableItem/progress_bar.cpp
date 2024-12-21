#include "progress_bar.h"

bool progress_bar::init()
{
    // ��������������
    progressBarBackground = cocos2d::Sprite::create("progress_bar_bg.png");
    this->addChild(progressBarBackground);

    // ����������ǰ��
    progressBar = cocos2d::ProgressTimer::create(cocos2d::Sprite::create("progress_bar.png"));
    progressBar->setType(cocos2d::ProgressTimer::Type::BAR);
    progressBar->setBarChangeRate(cocos2d::Vec2(1, 0)); // ˮƽ�仯
    progressBar->setMidpoint(cocos2d::Vec2(0, 0)); // ���ý�������ʼλ��
    progressBar->setPercentage(0); // ��ʼ��Ϊ 0%
    this->addChild(progressBar);

    return true;
}
progress_bar* progress_bar::create()
{
    progress_bar* ret = new progress_bar();
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    else {
        delete ret;
        return nullptr;
    }
}
//��ʾ������
void progress_bar::show_progress_bar(const cocos2d::Vec2& position)
{
    this->setPosition(position);
    this->setVisible(true); // ��ʾ������
}
//���½���
void progress_bar::update_progress_bar(float progress)
{
    if (progress < 0) {
        progress = 0;
    }
    if (progress > 100) {
        progress = 100; // ��֤������������100%
    }
    progressBar->setPercentage(progress);
}
//���ؽ�����
void progress_bar::hide_progress_bar()
{
    this->setVisible(false);
}
