#include "GameCamera.h"

GameCamera::GameCamera(cocos2d::Node* viewPortNode, cocos2d::Node* mapNode, cocos2d::Node* roleNode)
    : mapNode(mapNode), roleNode(roleNode), lastRoleX(0), lastRoleY(0) {

    // �����ͼ������ƶ���Χ
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

    // ��ʼ����λ��
    lastRoleX = roleNode->getPositionX();
    lastRoleY = roleNode->getPositionY();

    CCLOG("����ͷ����ƶ�����: %.2f, %.2f", xRange, yRange);
}

void GameCamera::updatePosition() {
    if (lastRoleX == roleNode->getPositionX() && lastRoleY == roleNode->getPositionY()) {
        return;
    }

    lastRoleX = roleNode->getPositionX();
    lastRoleY = roleNode->getPositionY();

    // ���µ�ͼλ��ʹ���ﱣ������Ļ����
    float distX = roleNode->getPositionX();
    float distY = roleNode->getPositionY();
    mapNode->setPosition(-distX, -distY);

    // ��������ͷλ�ã����õ�ͼ�����߽�
    if (mapNode->getPositionX() > xRange) {
        mapNode->setPosition(xRange, mapNode->getPositionY());
        CCLOG("����ͷ�����ұ߽�");
    }
    else if (mapNode->getPositionX() < -xRange) {
        mapNode->setPosition(-xRange, mapNode->getPositionY());
        CCLOG("����ͷ������߽�");
    }

    if (mapNode->getPositionY() > yRange) {
        mapNode->setPosition(mapNode->getPositionX(), yRange);
        CCLOG("����ͷ�����ϱ߽�");
    }
    else if (mapNode->getPositionY() < -yRange) {
        mapNode->setPosition(mapNode->getPositionX(), -yRange);
        CCLOG("����ͷ�����±߽�");
    }
}
