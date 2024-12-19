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
	std::string sprite_name;

};



#endif __GETABLE_GOOD_H__