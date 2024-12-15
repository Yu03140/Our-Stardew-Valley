#include "TaskBarScene.h"

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//! 注意！这里是图层，添加到场景中的语句有所不同，如下
/**    // 运行场景。设置 Director 运行该场景。
auto scene = cocos2d::Scene::create(); // 创建一个空场景
auto layer = TaskBarScene::create(); // 创建你的层
scene->addChild(layer);               // 将层添加到场景
cocos2d::Director::getInstance()->runWithScene(scene); // 运行场景*/









/**
 * @brief 创建任务栏场景。
 * @return 返回包含任务栏的场景对象。
 */
cocos2d::Scene* TaskBarScene::createScene() {
    auto scene = cocos2d::Scene::create(); // 创建一个新场景
    auto layer = TaskBarScene::create();  // 创建任务栏层
    scene->addChild(layer); // 将任务栏层添加到场景中
    return scene; // 返回场景
}

/**
 * @brief 初始化任务栏场景。
 * @return 初始化是否成功。
 */
bool TaskBarScene::init() {
    if (!Layer::init()) { // 调用父类初始化方法
        return false; // 如果失败，则返回 false
    }

    // 创建任务栏
    auto taskBar = TaskBar::create(
        "One pumpkin for 50$\n From Bouncer", // 任务描述
        "Bouncer", // NPC 名字
        []() {
            // 完成任务后的回调函数，用于修改玩家财产和 NPC 好感度
            cocos2d::log("玩家财产和好感度已更新！");
        });
    // 设置任务栏到屏幕中心
    auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    auto origin = cocos2d::Director::getInstance()->getVisibleOrigin();
    taskBar->setPosition(cocos2d::Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height / 2));

    this->addChild(taskBar); // 将任务栏添加到当前层中

    // 创建按钮，用于显示任务栏
    auto showTaskBarButton = cocos2d::MenuItemImage::create(
        "ShowTaskBarNormal.png", // 按钮的正常状态图像
        "ShowTaskBarSelected.png", // 按钮的选中状态图像
        [taskBar](Ref* sender) { // 按钮回调函数，点击后显示任务栏
            taskBar->show();
        });
    showTaskBarButton->setPosition(cocos2d::Vec2(240, 320)); // 设置按钮位置

    // 创建菜单并将按钮添加到菜单中
    auto menu = cocos2d::Menu::create(showTaskBarButton, nullptr);
    menu->setPosition(cocos2d::Vec2::ZERO); // 设置菜单位置为原点
    this->addChild(menu); // 将菜单添加到当前层中

    return true; // 初始化成功
}
