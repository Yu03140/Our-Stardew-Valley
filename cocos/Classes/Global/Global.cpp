#include "Global.h"
//全局变量
BackpackLayer* backpackLayer = nullptr;
TimeSystem* timeSystem = nullptr;
TaskBarLayer* taskBarScene = nullptr;
cocos2d::Vec2 character_pos = cocos2d::Vec2::ZERO;
extern cocos2d::Vec2 Mouse_Pos = cocos2d::Vec2::ZERO;
bool is_in_control = 0;