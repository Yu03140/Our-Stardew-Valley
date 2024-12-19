#include "TaskBar.h"
//#include "UI_Scene.h"

// ������������������������NPC���ֺ��������Ļص�������Ϊ����
TaskBar* TaskBar::create(const std::string& taskDescription, const std::string& npcName,
    std::function<void()> completeTaskCallback) {
    TaskBar* taskBar = new (std::nothrow) TaskBar();
    if (taskBar && taskBar->init(taskDescription, npcName, completeTaskCallback)) {
        taskBar->autorelease(); // �Զ��ͷ��ڴ�
        return taskBar;
    }
    delete taskBar; // �����ʼ��ʧ�ܣ��ͷ��ڴ�
    return nullptr;
}

// ��ʼ������������
// ����������������NPC���֡��������Ļص�����
bool TaskBar::init(const std::string& taskDescription, const std::string& npcName,
    std::function<void()> completeTaskCallback) {
    if (!Node::init()) { // ���ø����ʼ������
        return false;
    }

    this->taskDescription = taskDescription; // ������������
    this->npcName = npcName; // ����NPC����
    this->taskCompleted = false; // ��ʼ������δ���״̬
    this->completeTaskCallback = completeTaskCallback; // �����������ص�����

    // ��������������ͼƬ
    auto background = cocos2d::Sprite::create("HelpWanted.png");
    //background->setScale(2.0f);
    this->addChild(background); // ��ӵ��ڵ���

    // ��������������ǩ
   // descriptionLabel = cocos2d::Label::createWithSystemFont(taskDescription, "Arial", 24);

    descriptionLabel = cocos2d::Label::createWithTTF(taskDescription, "fonts/Marker Felt.ttf", 24);
    // ����������ɫΪ��ɫ
    descriptionLabel->setTextColor(cocos2d::Color4B::BLACK);

    descriptionLabel->setPosition(cocos2d::Vec2(background->getContentSize().width / 2,
        background->getContentSize().height / 1.5)); // ���ñ�ǩλ��
    descriptionLabel->setLocalZOrder(10); // ���ñ�ǩ�� Z-order ���ڱ���
    background->addChild(descriptionLabel); // ����ǩ��ӵ�����

    // ������������񡱰�ť
    completeTaskButton = cocos2d::MenuItemImage::create(
        "done_button.png", "done_button.png",
        CC_CALLBACK_0(TaskBar::onCompleteTask, this)); // ���ð�ť�ص�����
    completeTaskButton->setPosition(cocos2d::Vec2(background->getContentSize().width / 2,
        background->getContentSize().height / 3)); // ���ð�ťλ��




    // �������رա���ť
    closeButton = cocos2d::MenuItemImage::create(
        "XforTaskBar.png", "XforTaskBar.png",
        CC_CALLBACK_0(TaskBar::onClose, this)); // ���ð�ť�ص�����
    closeButton->setPosition(cocos2d::Vec2(background->getContentSize().width - 30,
        background->getContentSize().height - 30)); // ���ð�ťλ��

    // �����˵�����Ӱ�ť
    auto menu = cocos2d::Menu::create(completeTaskButton, closeButton, nullptr);
    menu->setPosition(cocos2d::Vec2::ZERO); // ���ò˵�λ��
    background->addChild(menu); // ���˵���ӵ�����

    return true;
}

// ��������񡱰�ť�Ļص�����
void TaskBar::onCompleteTask() {
    if (!taskCompleted) { // �������δ���
        taskCompleted = true; // �������Ϊ���
        if (completeTaskCallback) {
            completeTaskCallback(); // ִ���������Ļص�����
        }
        descriptionLabel->setString("������ɣ�"); // ������������Ϊ��������ɣ���
    }
}

// ���رա���ť�Ļص�����
void TaskBar::onClose() {
    this->hide(); // ����������
}

// ��ʾ������
void TaskBar::show() {
    this->setVisible(true);
}

// ����������
void TaskBar::hide() {
    this->setVisible(false);
}