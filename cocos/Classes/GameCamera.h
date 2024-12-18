#ifndef __GAME_CAMERA_H__
#define __GAME_CAMERA_H__

#include "cocos2d.h"

class GameCamera {
private:
    cocos2d::Node* mapNode;  // ��ͼ�ڵ�
    cocos2d::Node* roleNode; // ��ɫ�ڵ�
    float xRange;            // x������ƶ�����
    float yRange;            // y������ƶ�����
    float lastRoleX;         // ��һ������xλ��
    float lastRoleY;         // ��һ������yλ��

public:
    GameCamera(cocos2d::Node* viewPortNode, cocos2d::Node* mapNode, cocos2d::Node* roleNode);
    void updatePosition();
};

#endif // __GAME_CAMERA_H__


