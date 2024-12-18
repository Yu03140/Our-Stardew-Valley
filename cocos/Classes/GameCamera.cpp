#include "GameCamera.h"

GameCamera::GameCamera(cocos2d::Node* viewPortNode, cocos2d::Node* mapNode, cocos2d::Node* roleNode)
    : mapNode(mapNode), roleNode(roleNode), lastRoleX(0), lastRoleY(0) {

    // 计算地图的最大移动范围
    if (mapNode->getContentSize().width > viewPortNode->getContentSize().width) {
        xRange = (mapNode->getContentSize().width - viewPortNode->getContentSize().width) / 2;
    }
    else {
        xRange = 0;
    }
    if (mapNode->getContentSize().height > viewPortNode->getContentSize().height) {
        yRange = (mapNode->getContentSize().height - viewPortNode->getContentSize().height) / 2;
    }
    else {
        yRange = 0;
    }

    // 初始人物位置
    lastRoleX = roleNode->getPositionX();
    lastRoleY = roleNode->getPositionY();

    CCLOG("摄像头最大移动距离: %.2f, %.2f", xRange, yRange);
}

void GameCamera::updatePosition() {
    if (lastRoleX == roleNode->getPositionX() && lastRoleY == roleNode->getPositionY()) {
        return;
    }

    lastRoleX = roleNode->getPositionX();
    lastRoleY = roleNode->getPositionY();

    // 更新地图位置使人物保持在屏幕中央
    float distX = roleNode->getPositionX();
    float distY = roleNode->getPositionY();
    mapNode->setPosition(-distX, -distY);

    // 限制摄像头位置，不让地图超过边界
    if (mapNode->getPositionX() > xRange) {
        mapNode->setPosition(xRange, mapNode->getPositionY());
        CCLOG("摄像头超过右边界");
    }
    else if (mapNode->getPositionX() < -xRange) {
        mapNode->setPosition(-xRange, mapNode->getPositionY());
        CCLOG("摄像头超过左边界");
    }

    if (mapNode->getPositionY() > yRange) {
        mapNode->setPosition(mapNode->getPositionX(), yRange);
        CCLOG("摄像头超过上边界");
    }
    else if (mapNode->getPositionY() < -yRange) {
        mapNode->setPosition(mapNode->getPositionX(), -yRange);
        CCLOG("摄像头超过下边界");
    }
}
