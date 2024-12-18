#ifndef GLOBAL_H
#define GLOBAL_H

#include <string>
#include <vector>
#include "cocos2d.h"
#include "BackpackLayer.h"
#include "TimeSystem.h"
#include "attribute.h"
#include "TaskBarScene.h"

extern BackpackLayer* backpackLayer;
extern TimeSystem* timeSystem;
extern float SceneWidth;
extern float SceneHeight;
extern TMXTiledMap* tileMap;
extern TMXLayer* borderLayer;
#define Playerlayer 1
#define Backpacklayer 2
#define Timesystemlayer 3
#define Taskbarlayer 4

#endif // GLOBAL_H



