#include "TaskBar.h"
//#include "UI_Scene.h"

// 创建任务栏对象，任务描述、NPC名字和完成任务的回调函数作为参数
TaskBar* TaskBar::create(const std::string& taskDescription, const std::string& npcName,
    std::function<void()> completeTaskCallback) {
    TaskBar* taskBar = new (std::nothrow) TaskBar();
    if (taskBar && taskBar->init(taskDescription, npcName, completeTaskCallback)) {
        taskBar->autorelease(); // 自动释放内存
        return taskBar;
    }
    delete taskBar; // 如果初始化失败，释放内存
    return nullptr;
}

// 初始化任务栏对象
// 参数：任务描述、NPC名字、完成任务的回调函数
bool TaskBar::init(const std::string& taskDescription, const std::string& npcName,
    std::function<void()> completeTaskCallback) {
    if (!Node::init()) { // 调用父类初始化方法
        return false;
    }

    this->taskDescription = taskDescription; // 设置任务描述
    this->npcName = npcName; // 设置NPC名字
    this->taskCompleted = false; // 初始化任务未完成状态
    this->completeTaskCallback = completeTaskCallback; // 设置完成任务回调函数

    // 创建任务栏背景图片
    auto background = cocos2d::Sprite::create("HelpWanted.png");
    //background->setScale(2.0f);
    this->addChild(background); // 添加到节点树

    // 创建任务描述标签
   // descriptionLabel = cocos2d::Label::createWithSystemFont(taskDescription, "Arial", 24);

    descriptionLabel = cocos2d::Label::createWithTTF(taskDescription, "fonts/Marker Felt.ttf", 24);
    // 设置字体颜色为黑色
    descriptionLabel->setTextColor(cocos2d::Color4B::BLACK);

    descriptionLabel->setPosition(cocos2d::Vec2(background->getContentSize().width / 2,
        background->getContentSize().height / 1.5)); // 设置标签位置
    descriptionLabel->setLocalZOrder(10); // 设置标签的 Z-order 高于背景
    background->addChild(descriptionLabel); // 将标签添加到背景

    // 创建“完成任务”按钮
    completeTaskButton = cocos2d::MenuItemImage::create(
        "done_button.png", "done_button.png",
        CC_CALLBACK_0(TaskBar::onCompleteTask, this)); // 设置按钮回调函数
    completeTaskButton->setPosition(cocos2d::Vec2(background->getContentSize().width / 2,
        background->getContentSize().height / 3)); // 设置按钮位置




    // 创建“关闭”按钮
    closeButton = cocos2d::MenuItemImage::create(
        "XforTaskBar.png", "XforTaskBar.png",
        CC_CALLBACK_0(TaskBar::onClose, this)); // 设置按钮回调函数
    closeButton->setPosition(cocos2d::Vec2(background->getContentSize().width - 30,
        background->getContentSize().height - 30)); // 设置按钮位置

    // 创建菜单并添加按钮
    auto menu = cocos2d::Menu::create(completeTaskButton, closeButton, nullptr);
    menu->setPosition(cocos2d::Vec2::ZERO); // 设置菜单位置
    background->addChild(menu); // 将菜单添加到背景

    return true;
}

// “完成任务”按钮的回调函数
void TaskBar::onCompleteTask() {
    if (!taskCompleted) { // 如果任务未完成
        taskCompleted = true; // 标记任务为完成
        if (completeTaskCallback) {
            completeTaskCallback(); // 执行完成任务的回调函数
        }
        descriptionLabel->setString("任务完成！"); // 更新任务描述为“任务完成！”
    }
}

// “关闭”按钮的回调函数
void TaskBar::onClose() {
    this->hide(); // 隐藏任务栏
}

// 显示任务栏
void TaskBar::show() {
    this->setVisible(true);
}

// 隐藏任务栏
void TaskBar::hide() {
    this->setVisible(false);
}