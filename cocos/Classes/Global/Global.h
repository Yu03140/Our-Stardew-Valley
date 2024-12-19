#ifndef GLOBAL_H
#define GLOBAL_H

#include <string>
#include <vector>
#include "cocos2d.h"
#include "Charactor/BackpackLayer.h"
#include "TimeSystem/TimeSystem.h"
#include "Attribute/attribute.h"
#include "TaskBar/TaskBarScene.h"

//全局定义
#define CONTROL_RANGE 300

extern BackpackLayer* backpackLayer;
extern TimeSystem* timeSystem;
extern TaskBarLayer* taskBarScene;
extern cocos2d::Vec2 character_pos;
extern bool is_in_control;
extern float SceneWidth;
extern float SceneHeight;

#define Playerlayer 1
#define Backpacklayer 2
#define Timesystemlayer 3
#define Taskbarlayer 4
#endif // GLOBAL_H



