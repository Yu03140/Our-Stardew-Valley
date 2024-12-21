#include "TaskBarLayer.h"
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
        "One Axe1 for 50$\n From Bouncer", // 任务描述
        "Bouncer", // NPC 名字
        []() {

            
        });
    // 设置任务栏到屏幕中心
    auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    taskBar->setAnchorPoint(Vec2(0.5, 0.5));
    taskBar->setPosition(cocos2d::Vec2(visibleSize.width / 2- visibleSize.width * (0.1), visibleSize.height / 2- visibleSize.height * (0.05)));
    // 获得taskBar的高度和宽度
	auto taskBarSize = taskBar->getContentSize();
	CCLOG("taskBarSize.width = %f, taskBarSize.height = %f", taskBarSize.width, taskBarSize.height);
    taskBar->setVisible(false); // 初始不可见
    this->addChild(taskBar,2); // 将任务栏添加到当前层中

    // 创建按钮，用于显示任务栏
    auto showTaskBarButton = cocos2d::MenuItemImage::create(
        "TaskBarOrigin.png", // 按钮的正常状态图像
        "TaskBarOrigin.png", // 按钮的选中状态图像
        [taskBar](Ref* sender) { // 按钮回调函数，点击后显示任务栏
            taskBar->show();
        });
    //?????????????????????????????????????????????????????
    showTaskBarButton->setPosition(cocos2d::Vec2(visibleSize.width * 0.5, visibleSize.height * 0.5 - taskBarSize.height)); // 设置按钮位置
    CCLOG("showTaskBarButton->getPosition().x = %f", showTaskBarButton->getPosition().x);

    // 创建菜单并将按钮添加到菜单中
    auto menu = cocos2d::Menu::create(showTaskBarButton, nullptr);
    menu->setPosition(cocos2d::Vec2::ZERO+Vec2(visibleSize.width*(-0.01), visibleSize.width * (-0.05))); // 设置菜单位置为原点
	//CCLOG("menu->getPosition().x = %f", menu->getPosition().x);
    this->addChild(menu,2); // 将菜单添加到当前层中


    return true; // 初始化成功
}