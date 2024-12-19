#include "TaskBarScene.h"
#include "Global/Global.h"

cocos2d::Scene* TaskBarLayer::createScene() {
    auto scene = cocos2d::Scene::create(); // 创建一个新场景
    auto layer = TaskBarLayer::create();  // 创建任务栏层
    scene->addChild(layer); // 将任务栏层添加到场景中
    return scene; // 返回场景
}

bool TaskBarLayer::init() {
    if (!Layer::init()) { // 调用父类初始化方法
        return false; // 如果失败，则返回 false
    }

    // 创建任务栏
    auto taskBar = TaskBar::create(
        "One pumpkin for 50$\n From Bouncer", // 任务描述
        "Bouncer", // NPC 名字
        []() {

            // 完成任务后的回调函数，用于修改玩家财产和 NPC 好感度
            Player* player = Player::getInstance();
            player->playerproperty.addExperience(50);
            player->playerproperty.addReputation(50);
            player->playerproperty.addMoney(50);
            //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@修改背包
            //bool函数检测是否可以完成任务

            cocos2d::log("玩家财产和好感度已更新！");
        });
    // 设置任务栏到屏幕中心
    auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    taskBar->setAnchorPoint(Vec2(1, 1));
    taskBar->setPosition(cocos2d::Vec2(visibleSize.width / 4, visibleSize.height / 4));
	CCLOG("visibleSize.width / 4=%f,visibleSize.height / 4=%f", visibleSize.width / 4, visibleSize.height / 4);
    taskBar->setVisible(false); // 初始不可见
    this->addChild(taskBar); // 将任务栏添加到当前层中

    // 创建按钮，用于显示任务栏
    auto showTaskBarButton = cocos2d::MenuItemImage::create(
        "TaskBarOrigin.png", // 按钮的正常状态图像
        "TaskBarOrigin.png", // 按钮的选中状态图像
        [taskBar](Ref* sender) { // 按钮回调函数，点击后显示任务栏
            taskBar->show();
        });
    //?????????????????????????????????????????????????????
    showTaskBarButton->setPosition(cocos2d::Vec2(200, 1000)); // 设置按钮位置

    // 创建菜单并将按钮添加到菜单中
    auto menu = cocos2d::Menu::create(showTaskBarButton, nullptr);
    menu->setPosition(cocos2d::Vec2::ZERO); // 设置菜单位置为原点
    this->addChild(menu); // 将菜单添加到当前层中


    return true; // 初始化成功
}
