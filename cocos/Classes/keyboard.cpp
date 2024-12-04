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

//当节点进入场景时调用
void HelloWorld::onEnter() {
    // 调用父类的 onEnter() 方法，保持场景的生命周期逻辑
    Layer::onEnter();

    // 打印日志，表示节点进入场景
    log("HelloWorld onEnter");

    // 创建一个键盘事件监听器
    auto listener = EventListenerKeyboard::create();

    // 为按键按下事件设置回调函数
    listener->onKeyPressed = [](EventKeyboard::KeyCode keyCode, Event* event) {
        // 打印按下的按键的 keyCode
        log("Key with keycode %d pressed", keyCode);
        };

    // 为按键释放事件设置回调函数
    listener->onKeyReleased = [](EventKeyboard::KeyCode keyCode, Event* event) {
        // 打印释放的按键的 keyCode
        log("Key with keycode %d released", keyCode);
        };

    // 获取事件分发器
    auto eventDispatcher = Director::getInstance()->getEventDispatcher();

    // 将事件监听器添加到事件分发器中，确保它在场景图中接收到事件
    eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}


