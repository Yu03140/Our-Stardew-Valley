//----------------------------------------------------
// 精灵：可通过工具在地图中获取的物品
// 说明：需要该物品名称、获取所需点击次数、获取所需工具
//----------------------------------------------------
#ifndef __GETABLE_GOOD_H__
#define  __GETABLE_GOOD_H__

#include "cocos2d.h"
#include "Global/Global.h"

class getable_good : public cocos2d::Sprite
{
private:
	//根据name 通过map得到click_times\tool等信息
	std::string sprite_name;
	//通过点击次数判断是否能被获取
	int click_count = 0;
public:


	// 创建实例
	static getable_good* create(const std::string& plist_name);

	// 初始化鼠标监听器
	void init_mouselistener();

	// 鼠标按下时的回调
	void on_mouse_click(cocos2d::Event* event);




};



#endif __GETABLE_GOOD_H__