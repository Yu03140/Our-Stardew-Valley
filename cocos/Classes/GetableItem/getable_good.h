//----------------------------------------------------
// ���飺��ͨ�������ڵ�ͼ�л�ȡ����Ʒ
// ˵������Ҫ����Ʒ���ơ���ȡ��������������ȡ���蹤��
//----------------------------------------------------
#ifndef __GETABLE_GOOD_H__
#define  __GETABLE_GOOD_H__

#include "cocos2d.h"
#include "Global/Global.h"

class getable_good : public cocos2d::Sprite
{
private:
	//����name ͨ��map�õ�click_times\tool����Ϣ
	std::string sprite_name;
	//ͨ����������ж��Ƿ��ܱ���ȡ
	int click_count = 0;
public:


	// ����ʵ��
	static getable_good* create(const std::string& plist_name);

	// ��ʼ����������
	void init_mouselistener();

	// ��갴��ʱ�Ļص�
	void on_mouse_click(cocos2d::Event* event);




};



#endif __GETABLE_GOOD_H__