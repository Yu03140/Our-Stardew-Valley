/****************************************************************
 * Project Name: 
 * File Name:     
 * File Function: 
 * Author:        
 * Update Date:   2024/12/4
 * Explanation:   
 ****************************************************************/

#include "cocos2d.h"

using namespace cocos2d;

//���ڵ���볡��ʱ����
void HelloWorld::onEnter() {
    // ���ø���� onEnter() ���������ֳ��������������߼�
    Layer::onEnter();

    // ��ӡ��־����ʾ�ڵ���볡��
    log("HelloWorld onEnter");

    // ����һ�������¼�������
    auto listener = EventListenerKeyboard::create();

    // Ϊ���������¼����ûص�����
    listener->onKeyPressed = [](EventKeyboard::KeyCode keyCode, Event* event) {
        // ��ӡ���µİ����� keyCode
        log("Key with keycode %d pressed", keyCode);
        };

    // Ϊ�����ͷ��¼����ûص�����
    listener->onKeyReleased = [](EventKeyboard::KeyCode keyCode, Event* event) {
        // ��ӡ�ͷŵİ����� keyCode
        log("Key with keycode %d released", keyCode);
        };

    // ��ȡ�¼��ַ���
    auto eventDispatcher = Director::getInstance()->getEventDispatcher();

    // ���¼���������ӵ��¼��ַ����У�ȷ�����ڳ���ͼ�н��յ��¼�
    eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}


