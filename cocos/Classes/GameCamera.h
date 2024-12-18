#ifndef __GAME_CAMERA_H__
#define __GAME_CAMERA_H__

#include "cocos2d.h"

class GameCamera {
private:
    cocos2d::Node* mapNode;  // 地图节点
    cocos2d::Node* roleNode; // 角色节点
    float xRange;            // x轴最大移动距离
    float yRange;            // y轴最大移动距离
    float lastRoleX;         // 上一次人物x位置
    float lastRoleY;         // 上一次人物y位置

public:
    GameCamera(cocos2d::Node* viewPortNode, cocos2d::Node* mapNode, cocos2d::Node* roleNode);
    void updatePosition();
};

#endif // __GAME_CAMERA_H__


