#ifndef __PROGRESS_BAR_H__
#define  __PROGRESS_BAR_H__

#include "cocos2d.h"

class progress_bar : public cocos2d::Sprite
{
private:
	cocos2d::ProgressTimer* progressBar = nullptr;  // ������ǰ��
	cocos2d::Sprite* progressBarBackground = nullptr; // ����������
	float progress = 0;  // ���ƽ������Ľ���

public:
	bool init();
	static progress_bar* create();
	void show_progress_bar(const cocos2d::Vec2& position);
	void update_progress_bar(float delta);
	void hide_progress_bar();
};
#endif __PROGRESS_BAR_H__
