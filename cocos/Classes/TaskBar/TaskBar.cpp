#include "TaskBar.h"
#include "Charactor/BackpackLayer.h"
#include "Global/Global.h"

// ��������������
TaskBar* TaskBar::create() {
    TaskBar* taskBar = new (std::nothrow) TaskBar();
    if (taskBar && taskBar->init()) {
        taskBar->autorelease();
        return taskBar;
    }
    delete taskBar;
    return nullptr;
}

// ��ʼ��������
bool TaskBar::init() {
    if (!Node::init()) {
        return false;
    }

    this->taskCompleted = false;

    // ��������������ͼƬ
    auto background = cocos2d::Sprite::create("HelpWanted.png");
    background->setScale(0.5);
    this->addChild(background);

    // ��������������ǩ
    descriptionLabel = cocos2d::Label::createWithTTF("", "fonts/Marker Felt.ttf", 15);
    descriptionLabel->setTextColor(cocos2d::Color4B::BLACK);
    descriptionLabel->setPosition(cocos2d::Vec2(background->getContentSize().width / 2,
        background->getContentSize().height / 3 * 2));
    descriptionLabel->setLocalZOrder(10);
    background->addChild(descriptionLabel);

    // ������������񡱰�ť
    completeTaskButton = cocos2d::MenuItemImage::create(
        "done_button.png", "done_button.png",
        CC_CALLBACK_0(TaskBar::onCompleteTask, this));
    completeTaskButton->setPosition(cocos2d::Vec2(background->getContentSize().width / 2,
        background->getContentSize().height / 3));

    // �������رա���ť
    closeButton = cocos2d::MenuItemImage::create(
        "XforTaskBar.png", "XforTaskBar.png",
        CC_CALLBACK_0(TaskBar::onClose, this));
    closeButton->setPosition(cocos2d::Vec2(background->getContentSize().width - 30,
        background->getContentSize().height - 30));

    // �����˵�����Ӱ�ť
    auto menu = cocos2d::Menu::create(completeTaskButton, closeButton, nullptr);
    menu->setPosition(cocos2d::Vec2::ZERO);
    background->addChild(menu);

    return true;
}

// ��������������
void TaskBar::addTask(const std::string& taskDescription, std::function<void()> completeTaskCallback) {
    taskQueue.push({ taskDescription, completeTaskCallback });

    // �����ǰû���������ڽ��У���������ʾ��һ������
    //if (taskQueue.size() == 1 && !taskCompleted) {
        //showNextTask();
    //}
}


// ��ʾ��һ������
void TaskBar::showNextTask() {
    if (!taskQueue.empty()) {
        // �Ӷ�����ȡ����һ������
        currentTask = taskQueue.front();
        taskQueue.pop();

        // ������������
        descriptionLabel->setString(currentTask.description);
        taskCompleted = false; // ����������ɱ�־
        completeTaskButton->setVisible(true); // ȷ����ť�ɼ�
    }
    else {
        // ���û�������ˣ���ʾ���״̬
        descriptionLabel->setString("Done!"); // �����������
        completeTaskButton->setVisible(false); // ������ɰ�ť
    }
}


void TaskBar::onCompleteTask() {
    // �����ǰ����δ��ɣ�ִ�е�ǰ����Ļص�
    if (!taskCompleted) {
        if (currentTask.completeCallback) {
            currentTask.completeCallback(); // ִ������Ļص�
        }
        taskCompleted = true; // ��ǵ�ǰ�������
    }

    // �����������ɣ��л�����һ������
    if (taskCompleted) {
        showNextTask(); // ��ʾ��һ������
    }
}


// ���رա���ť�Ļص�����
void TaskBar::onClose() {
    this->hide();
}

// ��ʾ������
void TaskBar::show() {
    this->setVisible(true);
}

// ����������
void TaskBar::hide() {
    this->setVisible(false);
}