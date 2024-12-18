#ifndef GLOBAL_H
#define GLOBAL_H

#include <string>
#include <vector>
#include "cocos2d.h"
#include "Charactor/BackpackLayer.h"
#include "TimeSystem/TimeSystem.h"
#include "Attribute/attribute.h"
#include "TaskBar/TaskBarScene.h"

//ȫ�ֶ���
#define CONTROL_RANGE 300

extern BackpackLayer* backpackLayer;
extern TimeSystem* timeSystem;
extern TaskBarLayer* taskBarScene;
extern cocos2d::Vec2 character_pos;
extern bool is_in_control;
#endif // GLOBAL_H



